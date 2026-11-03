#include "../MinimapViewState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B5F70
    void MinimapViewState::locatePlayerKeepPositionsOnMinimap(uint flags, int widthFactor, int heightFactor)
    {
        int scale = 1;
        int firstRow = 0;
        int orientationOffset = 8;
        int divisor = 2;
        for (int player = 0; player < 8; player++) {
            this->DAT_MapU4B64.keepPositions[player].x = -1;
            this->DAT_MapU4B64.keepPositions[player].y = -1;
        }
        if ((flags & 4) != 0) {
            scale = 2;
        }
        int const columns = 400 / widthFactor * scale;
        int const lastRow = scale * 200;
        if (DAT_TileMapState::instance.mapSize <= 200) {
            firstRow = 100;
            divisor = 1;
        }
        int const viewportHeight = DAT_ViewportRenderState::instance.viewportState.viewportHeight;
        int rowParity = viewportHeight + 1;
        if (DAT_TileMapState::instance.mapOrientation != 0) {
            if (DAT_TileMapState::instance.mapOrientation == 6) {
                orientationOffset = 0x13a18;
            } else if (DAT_TileMapState::instance.mapOrientation == 4) {
                orientationOffset = 0x27428;
            } else if (DAT_TileMapState::instance.mapOrientation == 2) {
                orientationOffset = 0x3ae38;
            }
        }
        int const firstColumn = firstRow / 2;
        int rowBase = firstColumn * 0x191 + orientationOffset + 1;
        for (int row = firstRow; row < lastRow - firstRow; row++) {
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
            if (0 <= row) {
                if (400 <= row) {
                    return;
                }
                if (scale != 2 || (row * heightFactor & 1) == 0) {
                    int const lastColumn = columns / divisor - firstColumn;
                    for (int column = firstColumn; column < lastColumn; column++) {
                        int const x = (column - firstColumn) * widthFactor + rowX;
                        int const buildingID
                            = DAT_TileMapState::instance.BuildingLayer[DAT_ViewportRenderState::instance
                                    .screenPointToTileNumber[column + rowBase - 8]];
                        if (buildingID != 0
                            && OpenSHC::Map::Buildings::BT_MANORHOUSE
                                <= DAT_BuildingsState::instance.buildings[buildingID].buildingType
                            && DAT_BuildingsState::instance.buildings[buildingID].buildingType
                                <= OpenSHC::Map::Buildings::BT_KEEPFIVE) {
                            int const owner = DAT_BuildingsState::instance.buildings[buildingID].owner;
                            if (this->DAT_MapU4B64.keepPositions[owner - 1].x == -1) {
                                int const y = (row - firstRow) * heightFactor;
                                if (scale == 1) {
                                    this->DAT_MapU4B64.keepPositions[owner - 1].x = x;
                                    this->DAT_MapU4B64.keepPositions[owner - 1].y = y;
                                } else {
                                    this->DAT_MapU4B64.keepPositions[owner - 1].x = x / scale;
                                    this->DAT_MapU4B64.keepPositions[owner - 1].y = y / scale;
                                }
                            }
                        }
                    }
                }
            }
            rowBase = rowBase + rowLength;
        }
    }

}
}
