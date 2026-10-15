#include "../PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00497690
        void PathFindingState::findPositionForGivenClimbArea(int area, uint x, uint y)
        {
            if (x > 399 || y > 399) {
                return;
            }
            if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
                return;
            }
            int _rowTile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            for (int _directionIndex = 0; _directionIndex < 8; _directionIndex = _directionIndex + 1) {
                int _direction = (int)(char)DAT_ClimbLogicDefinedData::instance.DirectionArray[_directionIndex];
                if ((short)DAT_TileMapState::instance
                        .PathConnectionLayer[DAT_TileMapState::instance.directionTranslationMatrix[y][_direction]
                            + _rowTile]
                    == area) {
                    this->climbX
                        = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].int_.xOffset
                        + x;
                    this->climbY
                        = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].int_.yOffset
                        + y;
                    return;
                }
            }
            return;
        }

    }
}
}
