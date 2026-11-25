#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00533CA0
        void UnitsState::tracePathFromLadderExitSetDestination(int unitID)
        {
            int _exitX = this->units[unitID].ladderExitXPosition;
            int _exitY = this->units[unitID].ladderExitYPosition;
            int _tile = this->units[unitID].previousTilePosition;
            int _stepIndex = 0;
            for (; _stepIndex < this->units[unitID].totalSizeOfPathPlan; ++_stepIndex) {
                int const _packedDirections = (char)this->units[unitID].pathPlanStart[_stepIndex / 2];
                int _direction;
                if ((_stepIndex & 1) != 0) {
                    _direction = _packedDirections >> 4;
                } else {
                    _direction = _packedDirections & 15;
                }
                _exitY = _exitY
                    + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].int_.yOffset;
                _exitX = _exitX
                    + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].int_.xOffset;
                _tile = DAT_ViewportRenderState::instance.translationMatrix[_exitY].addXgetTile + _exitX;
                if ((DAT_TileMapState::instance.LogicLayer[_tile] & LogicHelpers::L_STAIRS) != 0) {
                    break;
                }
            }
            this->units[unitID].totalSizeOfPathPlan = _stepIndex + 1;
            this->units[unitID].destinationYPosition = _exitY;
            this->units[unitID].destinationXPosition = _exitX;
            this->units[unitID].destinationTilePosition = _tile;
        }

    }
}
}
