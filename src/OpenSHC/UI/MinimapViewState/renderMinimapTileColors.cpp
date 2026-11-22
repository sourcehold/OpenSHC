#include "../MinimapViewState.func.hpp"

#include "OpenSHC/Map/Enums/MapOrientation.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic2.hpp"
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

    // Draws a strip of the screen tile rows into the minimap pixel buffer, each tile in its terrain's colour and light.
    // FUNCTION: STRONGHOLDCRUSADER 0x004B58D0
    void MinimapViewState::renderMinimapTileColors(
        uint flags, int widthFactor, int heightFactor, int stripStart, uint stripLength)
    {
        // The assembly below takes the buffer's address from this local.
        ushort* const buffer = this->minimapPixelBuffer;
        // These five in this order before the strip rows (after them, isRGB565 takes stripLength's stack slot).
        int firstRow = 0;
        BOOLEnum isRGB565 = FALSE;
        int rowBase = 8;
        int scale = 1;
        int columnDivisor = 2;
        // the strip covers rows stripStart% .. stripStart + stripLength% of the 400 screen tile rows
        int const firstStripRow = stripStart * 400 / 100;
        // (int) for a signed division (divided unsigned, the match is lost).
        int const endStripRow = (int)(stripStart + stripLength) * 400 / 100;
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
        // The global again (viewportHeight + 1 is added up anew in every row).
        int const otherParity = DAT_ViewportRenderState::instance.viewportState.viewportHeight + 1;
        int rowParity = otherParity;
        // rowBase first holds the orientation's offset into the screen tile table (a variable of its own for the
        // offset takes another stack slot); north writes the 8 again (left out, the match is lost).
        if (DAT_TileMapState::instance.mapOrientation == Map::Enums::MO_NORTH) {
            rowBase = 8;
        } else if (DAT_TileMapState::instance.mapOrientation == Map::Enums::MO_WEST) {
            rowBase = 80408;
        } else if (DAT_TileMapState::instance.mapOrientation == Map::Enums::MO_SOUTH) {
            rowBase = 160808;
        } else if (DAT_TileMapState::instance.mapOrientation == Map::Enums::MO_EAST) {
            rowBase = 241208;
        }
        int const firstColumn = firstRow / 2;
        rowBase = firstColumn * 401 + rowBase + 1;
        int rowLength;
        // rowBase steps in the header (as the body's last statement it is stepped before the row's own values).
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
            int const lastColumn = columns / columnDivisor - firstColumn;
            // firstRow / 2 written out (starting at firstColumn, x's first value is folded to rowX).
            for (int column = firstRow / 2; column < lastColumn; ++column) {
                // The tile before x (after x, the two stepping values are set up and advanced in the other
                // order); y in here (declared per row, the match is lost).
                int const tile = DAT_ViewportRenderState::instance.screenPointToTileNumber[column + rowBase];
                int const x = (column - firstColumn) * widthFactor + rowX;
                int const y = (row - firstRow) * heightFactor;
                int const logic = DAT_TileMapState::instance.LogicLayer[tile];
                int const logic2 = DAT_TileMapState::instance.Logic2Layer[tile];
                int const random = DAT_TileMapState::instance.RandomLayer[tile];
                int const groundHeight = DAT_TileMapState::instance.HeightLayer[tile];
                int const luminescence = DAT_TileMapState::instance.LuminesenceLayer[tile];
                // 16 bits wide (as a uint, the two colour modes below end in one shared block).
                ushort color;
                if (logic & (L_BORDER | L_BORDER_EDGE)) {
                    color = 0;
                } else if (logic & L_SEA) {
                    color = DAT_MiniMapDefinedData::instance.SeaMinimapColors[isRGB565 + (random & 7) * 2];
                } else if (logic & L_FORD) {
                    // & 7 on an 8-entry table, as in the original (its entries run on into field_0x64).
                    color = DAT_MiniMapDefinedData::instance.FordMinimapColors[isRGB565 + (random & 7) * 2];
                } else if (logic & L_RIVER) {
                    color = DAT_MiniMapDefinedData::instance.RiverMinimapColors[isRGB565 + (random & 3) * 2];
                } else if (logic & L_BOULDERS) {
                    color = DAT_MiniMapDefinedData::instance.BouldersMinimapColors[isRGB565 + (random & 7) * 2];
                } else if (logic & L_ROCKY) {
                    color = DAT_MiniMapDefinedData::instance.MinimapColorArray[isRGB565 + (random & 3) * 2];
                } else if (logic & L_PEBBLES) {
                    color = DAT_MiniMapDefinedData::instance.PebblesMinimapColors[isRGB565 + (random & 3) * 2];
                } else if (logic2 & L2_STONES_OR_DRIVEN_SANDUnk) {
                    color
                        = DAT_MiniMapDefinedData::instance.StonesOrDrivenSandMinimapColors[isRGB565 + (random & 3) * 2];
                } else if (logic2 & L2_BEACH) {
                    color = DAT_MiniMapDefinedData::instance.BeachMinimapColors[isRGB565 + (random & 3) * 2];
                } else if ((logic2 & L2_OASIS_GRASS) && (logic & L_DEFAULT_EARTH_OR_TEXTURE)) {
                    color = DAT_MiniMapDefinedData::instance.OasisGrassMinimapColors[isRGB565 + (random & 3) * 2];
                } else if ((logic2 & L2_THICK_SCRUB) && (logic & L_DEFAULT_EARTH_OR_TEXTURE)) {
                    color = DAT_MiniMapDefinedData::instance.ThickScrubMinimapColors[isRGB565 + (random & 3) * 2];
                } else if ((logic2 & L2_SCRUB) && (logic & L_DEFAULT_EARTH_OR_TEXTURE)) {
                    color = DAT_MiniMapDefinedData::instance.ScrubMinimapColors[isRGB565 + (random & 3) * 2];
                } else if (logic & L_IRON) {
                    color = DAT_MiniMapDefinedData::instance.IronMinimapColors[isRGB565 + (random & 3) * 2];
                } else if (logic & (L_MARSH | L_OIL)) {
                    color = DAT_MiniMapDefinedData::instance.MarshOrOilMinimapColors[isRGB565 + (random & 3) * 2];
                } else if (groundHeight > 16) {
                    color
                        = DAT_MiniMapDefinedData::instance.StonesOrDrivenSandMinimapColors[isRGB565 + (random & 3) * 2];
                } else if (!(logic2 & L2_EARTH_AND_STONES) && !(logic & L_PLAIN2_AND_PITCH)) {
                    color = DAT_MiniMapDefinedData::instance.EarthMinimapColors[isRGB565 + (random & 7) * 2];
                } else {
                    color = DAT_MiniMapDefinedData::instance.EarthAndStonesMinimapColors[isRGB565 + (random & 7) * 2];
                }
                // entry 2 is 100%: the colour as it is
                if (luminescence != 2) {
                    int const brightness = DAT_MiniMapDefinedData::instance.LuminescenceBrightnessPercent[luminescence];
                    // Set in this order (the mix takes green and red in the order they are first set).
                    int blue = 0;
                    int green = 0;
                    int red = 0;
                    // Red's and green's masks right after their caps (inside the mix, they move to the end). Blue's
                    // stays in the mix, where the original masks it last.
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
                // The pixel stores are handwritten assembly in the original, transcribed from the binary.
                if (scale == 1) {
                    // A copy for the assembly (x named there is stored at the top of the tile loop).
                    int const pixelX = x;
                    for (int offsetX = 0; offsetX < widthFactor; ++offsetX) {
                        if (x + offsetX < 0 || x + offsetX >= columns * widthFactor) {
                            continue;
                        }
                        for (int offsetY = 0; offsetY < heightFactor; ++offsetY) {
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
