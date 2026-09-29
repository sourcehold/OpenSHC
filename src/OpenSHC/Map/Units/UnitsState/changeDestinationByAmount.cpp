#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00533B30
        void UnitsState::changeDestinationByAmount(int unitID, int leftover)
        {
            if (this->units[unitID].climbDataID != 0) {
                this->units[unitID].leftover = (short)leftover;
                return;
            }
            this->units[unitID].leftover = 0;
            if (leftover >= this->units[unitID].totalSizeOfPathPlan) {
                this->units[unitID].destinationTilePosition = this->units[unitID].previousTilePosition;
                this->units[unitID].totalSizeOfPathPlan = 0;
                this->units[unitID].destinationXPosition = this->units[unitID].ladderExitXPosition;
                this->units[unitID].destinationYPosition = this->units[unitID].ladderExitYPosition;
                this->units[unitID].destinationX_2Unk = this->units[unitID].ladderExitXPosition;
                this->units[unitID].destinationY_2Unk = this->units[unitID].ladderExitYPosition;
                return;
            }
            int _destinationX = this->units[unitID].ladderExitXPosition;
            int _destinationY = this->units[unitID].ladderExitYPosition;
            this->units[unitID].totalSizeOfPathPlan = this->units[unitID].totalSizeOfPathPlan - (short)leftover;
            for (int _stepIndex = 0; _stepIndex < this->units[unitID].totalSizeOfPathPlan; ++_stepIndex) {
                uint _packedDirections = (char)this->units[unitID].pathPlanStart[_stepIndex / 2];
                uint _direction;
                if ((_stepIndex & 1) == 0) {
                    _direction = _packedDirections & 0xf;
                } else {
                    _direction = (int)_packedDirections >> 4;
                }
                _destinationX = _destinationX
                    + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].int_.xOffset;
                _destinationY = _destinationY
                    + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].int_.yOffset;
            }
            this->units[unitID].destinationXPosition = (short)_destinationX;
            this->units[unitID].destinationYPosition = (short)_destinationY;
            this->units[unitID].destinationX_2Unk = (short)_destinationX;
            this->units[unitID].destinationY_2Unk = (short)_destinationY;
            this->units[unitID].destinationTilePosition = (short)_destinationX
                + DAT_ViewportRenderState::instance.translationMatrix[(short)_destinationY].addXgetTile;
        }

    }
}
}
