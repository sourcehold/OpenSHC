#include "OpenSHC/Map/Units/UnitsState.func.hpp"

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
                uint _packedDirections = (char)this->units[unitID].pathPlanStart[_stepIndex / 2];
                uint _direction;
                if ((_stepIndex & 1) == 0) {
                    _direction = _packedDirections & 0xf;
                } else {
                    _direction = (int)_packedDirections >> 4;
                }
                _exitY = _exitY
                    + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].int_.yOffset;
                _exitX = _exitX
                    + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].int_.xOffset;
                _tile = DAT_ViewportRenderState::instance.translationMatrix[_exitY].addXgetTile + _exitX;
                if ((DAT_TileMapState::instance.LogicLayer[_tile] & 0x800U) != 0) {
                    break;
                }
            }
            this->units[unitID].totalSizeOfPathPlan = (short)_stepIndex + 1;
            this->units[unitID].destinationYPosition = (short)_exitY;
            this->units[unitID].destinationXPosition = (short)_exitX;
            this->units[unitID].destinationTilePosition = _tile;
        }

    }
}
}
