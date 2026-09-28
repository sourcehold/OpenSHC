#include "../PathFindingState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0049CD60
        BOOLEnum PathFindingState::findDirectNeighbourWalkableTile(uint x, uint y)
        {
            if (x < 400 && y < 400 && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] != '\0') {
                int _directionIndex = 0;
                do {
                    uint _x = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_directionIndex]
                                  .int_.xOffset
                        + x;
                    uint _y = *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix
                                  + _directionIndex * 8 + 4)
                        + y;
                    if (_x < 400 && _y < 400 && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[_y * 400 + _x] != '\0') {
                        int _tile = DAT_TileMapState::instance.directionTranslationMatrix[y][_directionIndex]
                            + DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
                        if ((DAT_TileMapState::instance.LogicLayer[_tile] & 0xb1U) == 0
                            && (DAT_TileMapState::instance.LogicLayer[_tile] & 0x50101400U) == 0) {
                            /*
                              No sea, borders, rocky, building, tree, river, keep, moat
                             */
                            this->ALG_ResultY = _y;
                            this->ALG_ResultTile = _tile;
                            this->ALG_ResultX = _x;
                            return TRUE;
                        }
                    }
                    _directionIndex = _directionIndex + 1;
                    if (7 < _directionIndex) {
                        return FALSE;
                    }
                } while (true);
            }
            return FALSE;
        }

    }
}
}
