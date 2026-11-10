#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/MapConstants.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0049CD60
        BOOLEnum PathFindingState::findDirectNeighbourWalkableTile(uint ySpace, uint y)
        {
            if (ySpace > MC_MAP_XY_LIMIT_MIN_1 || y > MC_MAP_XY_LIMIT_MIN_1) {
                return FALSE;
            }
            if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * MC_MAP_XY_LIMIT + ySpace] == '\0') {
                return FALSE;
            }
            int _rowTile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + ySpace;
            for (int _directionIndex = 0; _directionIndex < 8; _directionIndex++) {
                uint _x
                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_directionIndex].int_.xOffset
                    + ySpace;
                uint _y
                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_directionIndex].int_.yOffset
                    + y;
                if (_x <= MC_MAP_XY_LIMIT_MIN_1 && _y <= MC_MAP_XY_LIMIT_MIN_1
                    && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[_y * MC_MAP_XY_LIMIT + _x] != '\0') {
                    int _tile = DAT_TileMapState::instance.directionTranslationMatrix[y][_directionIndex] + _rowTile;
                    uint _logic = DAT_TileMapState::instance.LogicLayer[_tile];
                    if ((_logic
                            & (LogicHelpers::L_SEA | LogicHelpers::L_BORDER | LogicHelpers::L_BORDER_EDGE
                                | LogicHelpers::L_ROCKY))
                            == 0
                        && (_logic
                               & (LogicHelpers::L_BUILDING | LogicHelpers::L_TREE | LogicHelpers::L_RIVER
                                   | LogicHelpers::L_KEEP_NON_MANOR_HOUSE | LogicHelpers::L_MOAT))
                            == 0) {
                        /*
                          No sea, borders, rocky, building, tree, river, keep, moat
                         */
                        this->ALG_ResultY = _y;
                        this->ALG_ResultTile = _tile;
                        this->ALG_ResultX = _x;
                        return TRUE;
                    }
                }
            }
            return FALSE;
        }

    }
}
}
