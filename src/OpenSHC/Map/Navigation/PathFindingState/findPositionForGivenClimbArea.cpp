#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/MapConstants.hpp"

#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x00497690
        void PathFindingState::findPositionForGivenClimbArea(int area, uint ySpace, uint y)
        {
            if (ySpace > MC_MAP_XY_LIMIT_MIN_1 || y > MC_MAP_XY_LIMIT_MIN_1
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * MC_MAP_XY_LIMIT + ySpace] == 0) {
                return;
            }
            int _baseTile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + ySpace;
            for (int _directionIndex = 0; _directionIndex < 8; _directionIndex++) {
                // DirectionArray holds signed offsets and the original loads it with movsx,
                // but the generated header declares it byte
                int _direction = (char)DAT_ClimbLogicDefinedData::instance.DirectionArray[_directionIndex];
                if ((short)DAT_TileMapState::instance
                        .PathConnectionLayer[DAT_TileMapState::instance.directionTranslationMatrix[y][_direction]
                            + _baseTile]
                    == area) {
                    this->climbX
                        = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].int_.xOffset
                        + ySpace;
                    this->climbY
                        = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].int_.yOffset
                        + y;
                    return;
                }
            }
        }

    }
}
}
