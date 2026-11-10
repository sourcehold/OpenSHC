#include "../MinimapViewState.func.hpp"

#include "OpenSHC/Globals/DAT_MiniMapDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    // Draws a strip of minimap rows (stripStart% to stripStart + stripLength% of the screen tile rows) into the minimap
    // pixel buffer: each tile's colour comes from its LogicLayer flags and MiniMapDefinedData's tables, scaled by its
    // luminescence (RGB555 or RGB565); zoomed out, every other pixel at half the position.
    // FUNCTION: STRONGHOLDCRUSADER 0x004B5330
    void MinimapViewState::renderMinimapTileStripWithLuminescence(
        uint flags, int widthFactor, int heightFactor, uint stripStart, int stripLength)
    {
        // the strip covers rows stripStart% .. stripStart + stripLength% of the 400 screen tile rows
        int const firstStripRow = (int)(stripStart * 400) / 100;
        int const endStripRow = (stripStart + stripLength) * 400 / 100;
        int isRGB565 = 0;
        int scale = 1;
        int firstRow = 0;
        int orientationOffset = 8;
        int divisor = 2;
        if ((flags & 4) != 0) {
            scale = 2;
        }
        int const columns = 400 / widthFactor * scale;
        int const lastRow = scale * 200;
        if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_565) {
            isRGB565 = 1;
        }
        if (DAT_TileMapState::instance.mapSize <= 200) {
            firstRow = 100;
            divisor = 1;
        }
        int const viewportHeight = DAT_ViewportRenderState::instance.viewportState.viewportHeight;
        int rowParity = viewportHeight + 1;
        if (DAT_TileMapState::instance.mapOrientation != 0) {
            if (DAT_TileMapState::instance.mapOrientation == 6) {
                orientationOffset = 80408;
            } else if (DAT_TileMapState::instance.mapOrientation == 4) {
                orientationOffset = 160808;
            } else if (DAT_TileMapState::instance.mapOrientation == 2) {
                orientationOffset = 241208;
            }
        }
        int const firstColumn = firstRow / 2;
        int rowBase = firstColumn * 401 + orientationOffset + 1;
        for (int row = firstRow; row < lastRow - firstRow; ++row) {
            // the screen tile rows are staggered: every other row is half a tile in and one tile longer
            int rowX;
            int rowLength;
            if (rowParity == viewportHeight + 1) {
                rowParity = viewportHeight;
                rowX = widthFactor / 2;
                rowLength = 200;
            } else {
                rowParity = viewportHeight + 1;
                rowX = 0;
                rowLength = 201;
            }
            if (firstStripRow <= row) {
                if (endStripRow <= row) {
                    return;
                }
                if (scale != 2 || (row * heightFactor & 1) == 0) {
                    int const y = (row - firstRow) * heightFactor;
                    int const lastColumn = columns / divisor - firstColumn;
                    for (int column = firstColumn - 2; column < lastColumn; ++column) {
                        int const x = (column - firstColumn) * widthFactor + rowX;
                        int const tile
                            = DAT_ViewportRenderState::instance.screenPointToTileNumber[column + rowBase];
                        uint const logic = DAT_TileMapState::instance.LogicLayer[tile];
                        int const random = DAT_TileMapState::instance.RandomLayer[tile];
                        int const luminescence = DAT_TileMapState::instance.LuminesenceLayer[tile];
                        uint color = 0;
                        if ((logic & 0x40000000) != 0) {
                            color = DAT_MiniMapDefinedData::instance.field_0x74[isRGB565 + (random & 3) * 2];
                        } else if ((logic & 0x3000) != 0) {
                            color = DAT_MiniMapDefinedData::instance.field_0x144[isRGB565 + (random & 3) * 2];
                        } else if ((logic & 8) != 0) {
                            if ((DAT_TileMapState::instance.MiscDisplayLayer[tile] & 0x2000) != 0) {
                                color = DAT_MiniMapDefinedData::instance.field_0x20[isRGB565];
                            } else {
                                color = 0;
                            }
                        } else {
                            // the colour of the first logic bit that has one
                            int bit = 0;
                            while (
                                (DAT_MiniMapDefinedData::instance.MinimapColorByLogicBit[bit].integer & logic) == 0) {
                                if (DAT_MiniMapDefinedData::instance.MinimapColorByLogicBit[bit].integer == 0) {
                                    break;
                                }
                                ++bit;
                            }
                            if (DAT_MiniMapDefinedData::instance.MinimapColorByLogicBit[bit].integer != 0) {
                                color = DAT_MiniMapDefinedData::instance.MinimapColorByLogicBit[bit]
                                            .colorModeSpecificValue[isRGB565];
                            } else {
                                color = 0;
                            }
                        }
                        if (luminescence != 2 && (short)color != 0 && (logic & 2) == 0) {
                            int const brightness
                                = DAT_MiniMapDefinedData::instance.LuminescenceBrightnessPercent[luminescence];
                            int red;
                            int green;
                            if (isRGB565 == 0) {
                                red = (int)(((ushort)color & 0x7c00) * brightness) / 100;
                                if (31744 < red) {
                                    red = 31744;
                                }
                                green = (int)(((ushort)color & 0x3e0) * brightness) / 100;
                                red &= 0x7c00;
                                if (992 < green) {
                                    green = 992;
                                }
                                green &= 0x3e0;
                            } else {
                                red = (int)(((ushort)color & 0xf800) * brightness) / 100;
                                if (63488 < red) {
                                    red = 63488;
                                }
                                green = (int)(((ushort)color & 0x7e0) * brightness) / 100;
                                red &= 0xf800;
                                if (2016 < green) {
                                    green = 2016;
                                }
                                green &= 0x7e0;
                            }
                            int blue = (int)(((ushort)color & 0x1f) * brightness) / 100;
                            if (31 < blue) {
                                blue = 31;
                            }
                            color = (ushort)(blue & 0x1f | green | red);
                        }
                        if (scale == 1) {
                            for (int dx = 0; dx < widthFactor; ++dx) {
                                if (0 <= x + dx && x + dx < columns * widthFactor) {
                                    for (int dy = 0; dy < heightFactor; ++dy) {
                                        if ((short)color == 0) {
                                            color = this->minimapPixelBuffer[(y + dy) * 400 / 2 + x + dx];
                                        }
                                        this->field_0x44[(y + dy) * 200 + x + dx] = (ushort)color;
                                    }
                                }
                            }
                        } else {
                            // zoomed out: every other pixel, at half the position
                            for (int dx = x & 1; dx < widthFactor; dx += 2) {
                                if (0 <= x + dx && x + dx < columns * widthFactor) {
                                    int const pixelX = (x + dx) / scale;
                                    for (int dy = 0; dy < heightFactor; ++dy) {
                                        int const pixelY = (y + dy) / scale;
                                        if ((short)color == 0) {
                                            color = this->minimapPixelBuffer[pixelY * 400 / 2 + pixelX];
                                        }
                                        this->field_0x44[pixelY * 200 + pixelX] = (ushort)color;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            rowBase += rowLength;
        }
    }

}
}
