#include "../MinimapViewState.func.hpp"

#include "OpenSHC/Map/Enums/MapOrientation.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/LogicHelpers/MiscDisplay.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MiniMapDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    using namespace Map::LogicHelpers;

    // The channels' bits in an RGB555 and in an RGB565 colour.
    enum {
        RGB555_RED = 31744, // 0x7c00
        RGB555_GREEN = 992, // 0x03e0
        RGB565_RED = 63488, // 0xf800
        RGB565_GREEN = 2016, // 0x07e0
        RGB_BLUE = 31 // 0x001f
    };

    // Draws a strip of the screen tile rows into the second minimap buffer: what stands on each tile, in its light.
    // FUNCTION: STRONGHOLDCRUSADER 0x004B5330
    void MinimapViewState::renderMinimapTileStripWithLuminescence(
        uint flags, int widthFactor, int heightFactor, uint stripStart, int stripLength)
    {
        // These five in this order before the buffer and the strip rows (after them, the stack slots change).
        int firstRow = 0;
        BOOLEnum isRGB565 = FALSE;
        int rowBase = 8;
        int scale = 1;
        int columnDivisor = 2;
        // The assembly below takes the buffer's address from this local.
        ushort* const buffer = this->field_0x44;
        // the strip covers rows stripStart% .. stripStart + stripLength% of the 400 screen tile rows
        // (int): the original divides signed (stripStart is a uint in the header).
        int const firstStripRow = (int)(stripStart * 400) / 100;
        int const endStripRow = (int)((stripStart + stripLength) * 400) / 100;
        if (flags & 4) {
            // zoomed out: half the size
            scale = 2;
        }
        int const columns = 400 / widthFactor * scale;
        int const rowCount = scale * 200;
        if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_565) {
            isRGB565 = TRUE;
        }
        if (DAT_TileMapState::instance.mapSize <= 200) {
            firstRow = 100;
            columnDivisor = 1;
        }
        int const viewportHeight = DAT_ViewportRenderState::instance.viewportState.viewportHeight;
        // The global again (from the first local, viewportHeight + 1 is added up anew in every row).
        int const otherParity = DAT_ViewportRenderState::instance.viewportState.viewportHeight + 1;
        int rowParity = otherParity;
        // rowBase first holds the orientation's offset into the screen tile table (in a variable of its own, the row
        // base's sum has its operands the other way round).
        if (DAT_TileMapState::instance.mapOrientation != Map::Enums::MO_NORTH) {
            if (DAT_TileMapState::instance.mapOrientation == Map::Enums::MO_WEST) {
                rowBase = 80408;
            } else if (DAT_TileMapState::instance.mapOrientation == Map::Enums::MO_SOUTH) {
                rowBase = 160808;
            } else if (DAT_TileMapState::instance.mapOrientation == Map::Enums::MO_EAST) {
                rowBase = 241208;
            }
        }
        int const firstColumn = firstRow / 2;
        rowBase = firstColumn * 401 + rowBase + 1;
        int rowLength;
        // rowBase steps in the header, so that the continues below step it too.
        for (int row = firstRow; row < rowCount - firstRow; ++row, rowBase += rowLength) {
            // the screen tile rows are staggered: every other row starts half a tile in and has one entry less in
            // the screen tile table (200 against 201)
            int rowX;
            if (rowParity == otherParity) {
                rowParity = viewportHeight;
                rowX = widthFactor / 2;
                rowLength = 200;
            } else {
                rowParity = otherParity;
                rowX = 0;
                rowLength = 201;
            }
            if (row < firstStripRow) {
                continue;
            }
            if (row >= endStripRow) {
                return;
            }
            if (scale == 2 && (row * heightFactor & 1)) {
                continue;
            }
            // The bound in the loop's test (in a local in front of the loop, the first column comes after it).
            for (int column = firstColumn - 2; column < columns / columnDivisor - firstColumn; ++column) {
                // Both set before the tile's flags are read (the table loop's tests take their operands in the
                // order the variables are first set).
                int entry = 0;
                int entryBits = 0;
                // The tile before x and y (after them, the tile loop's set-up is in another order).
                int const tile = DAT_ViewportRenderState::instance.screenPointToTileNumber[column + rowBase];
                int const x = (column - firstColumn) * widthFactor + rowX;
                int const y = (row - firstRow) * heightFactor;
                int const logic = DAT_TileMapState::instance.LogicLayer[tile];
                int const random = DAT_TileMapState::instance.RandomLayer[tile];
                int const luminescence = DAT_TileMapState::instance.LuminesenceLayer[tile];
                // 16 bits wide (as a uint, the mix below extends each channel on its own).
                ushort color;
                if (logic & L_MOAT) {
                    color = DAT_MiniMapDefinedData::instance.field_0x74[isRGB565 + (random & 3) * 2];
                } else if (logic & (L_TREE | L_TREE_VARIATION)) {
                    color = DAT_MiniMapDefinedData::instance.field_0x144[isRGB565 + (random & 3) * 2];
                } else if (logic & L_PLAIN2_AND_PITCH) {
                    if (DAT_TileMapState::instance.MiscDisplayLayer[tile] & MD_RUBBLE_EDGEUnk) {
                        color = DAT_MiniMapDefinedData::instance.field_0x20[isRGB565];
                    } else {
                        color = 0;
                    }
                } else {
                    // The colour of the first table entry sharing a bit with the flags; a 0 entry ends it.
                    // First test on entryBits, the loop's on the table (swapped, both swap their operands).
                    bool hasEntry = true;
                    entryBits = DAT_MiniMapDefinedData::instance.MinimapColorByLogicBit[entry].integer;
                    if (!(entryBits & logic)) {
                        // A do-while (a while loop swaps the operands of one of the two tests; a for loop with a
                        // break at its end adds two instructions).
                        do {
                            if (!entryBits) {
                                hasEntry = false;
                                break;
                            }
                            ++entry;
                            entryBits = DAT_MiniMapDefinedData::instance.MinimapColorByLogicBit[entry].integer;
                        } while (!(DAT_MiniMapDefinedData::instance.MinimapColorByLogicBit[entry].integer & logic));
                    }
                    if (hasEntry) {
                        color = DAT_MiniMapDefinedData::instance.MinimapColorByLogicBit[entry]
                                    .colorModeSpecificValue[isRGB565];
                    } else {
                        color = 0;
                    }
                }
                // brightness entry 2 is 100%: the colour as it is
                if (luminescence != 2 && color != 0 && !(logic & L_STOCKPILEUnk)) {
                    int const brightness = DAT_MiniMapDefinedData::instance.LuminescenceBrightnessPercent[luminescence];
                    // Set in this order (the mix takes green and red in the order they are first set).
                    int blue = 0;
                    int green = 0;
                    int red = 0;
                    // Red's and green's masks right after their caps, blue's in the mix. Blue and the mix in
                    // both arms (written once behind them, the registers of the whole block change).
                    if (!isRGB565) {
                        red = (color & RGB555_RED) * brightness / 100;
                        if (red > RGB555_RED) {
                            red = RGB555_RED;
                        }
                        red &= RGB555_RED;
                        green = (color & RGB555_GREEN) * brightness / 100;
                        if (green > RGB555_GREEN) {
                            green = RGB555_GREEN;
                        }
                        green &= RGB555_GREEN;
                        blue = (color & RGB_BLUE) * brightness / 100;
                        if (blue > RGB_BLUE) {
                            blue = RGB_BLUE;
                        }
                        color = (ushort)(blue & RGB_BLUE | green | red);
                    } else {
                        red = (color & RGB565_RED) * brightness / 100;
                        if (red > RGB565_RED) {
                            red = RGB565_RED;
                        }
                        red &= RGB565_RED;
                        green = (color & RGB565_GREEN) * brightness / 100;
                        if (green > RGB565_GREEN) {
                            green = RGB565_GREEN;
                        }
                        green &= RGB565_GREEN;
                        blue = (color & RGB_BLUE) * brightness / 100;
                        if (blue > RGB_BLUE) {
                            blue = RGB_BLUE;
                        }
                        color = (ushort)(blue & RGB_BLUE | green | red);
                    }
                }
                // A tile without a colour takes the terrain picture's pixel, once, at the first pixel it draws.
                // The pixel stores are handwritten assembly in the original, transcribed from the binary.
                if (scale == 1) {
                    // A copy for the assembly (x named there is stored at the top of the tile loop).
                    int const pixelX = x;
                    for (int offsetX = 0; offsetX < widthFactor; ++offsetX) {
                        if (x + offsetX < 0 || x + offsetX >= columns * widthFactor) {
                            continue;
                        }
                        for (int offsetY = 0; offsetY < heightFactor; ++offsetY) {
                            if (color == 0) {
                                color = this->minimapPixelBuffer[(y + offsetY) * 400 / 2 + x + offsetX];
                            }
                            __asm {
                                mov edi, buffer
                                mov eax, pixelX
                                add eax, offsetX
                                add eax, eax
                                add edi, eax
                                mov eax, y
                                add eax, offsetY
                                mov edx, 400
                                mul edx
                                add edi, eax
                                mov ax, color
                                mov word ptr [edi], ax
                            }
                        }
                    }
                } else {
                    // Every other pixel at half the position (a plain loop skipping odd ones loses the match).
                    for (int offsetX = x & 1; offsetX < widthFactor; offsetX += 2) {
                        if (x + offsetX < 0 || x + offsetX >= columns * widthFactor) {
                            continue;
                        }
                        int const halfX = (x + offsetX) / scale;
                        for (int offsetY = 0; offsetY < heightFactor; ++offsetY) {
                            int const halfY = (y + offsetY) / scale;
                            if (color == 0) {
                                color = this->minimapPixelBuffer[halfY * 400 / 2 + halfX];
                            }
                            __asm {
                                mov edi, buffer
                                mov eax, halfX
                                add eax, eax
                                add edi, eax
                                mov eax, halfY
                                mov edx, 400
                                mul edx
                                add edi, eax
                                mov ax, color
                                mov word ptr [edi], ax
                            }
                        }
                    }
                }
            }
        }
    }

}
}
