#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

#include <stdlib.h>

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitType;

        // The path plan byte is read signed (movsx at 0x52169E) although pathPlanStart is declared byte.
        // FUNCTION: STRONGHOLDCRUSADER 0x00521500
        void TribesState::predictUnitInterceptPosition(
            int targetUnitID, int unitID, int* unitCurrentX, int* unitCurrentY)
        {
            *unitCurrentX = DAT_UnitsState::instance.units[unitID].x;
            *unitCurrentY = DAT_UnitsState::instance.units[unitID].y;
            if (DAT_UnitsState::instance.units[unitID].tunnelerFinishedDigging != 2) {
                return;
            }
            short speed = this->tribes[DAT_UnitsState::instance.units[targetUnitID].tribeID].minimumMovementSpeed;
            int targetFactor = speed;
            if (speed <= 1) {
                targetFactor = 1;
            }
            targetFactor *= 4;
            speed = this->tribes[DAT_UnitsState::instance.units[unitID].tribeID].minimumMovementSpeed;
            int unitStep = speed;
            if (speed <= 1) {
                unitStep = 1;
            }
            unitStep *= 4;
            int const targetX = DAT_UnitsState::instance.units[targetUnitID].x;
            int const targetY = DAT_UnitsState::instance.units[targetUnitID].y;
            if (DAT_UnitsState::instance.units[targetUnitID].stateBasedSpeed > 0) {
                targetFactor /= 2;
            } else if (DAT_UnitsState::instance.units[targetUnitID].unitType == UT_E_KNIGHT
                && !DAT_UnitsState::instance.units[targetUnitID].isMatchingSpeed) {
                targetFactor /= 3;
            } else if (DAT_UnitsState::instance.units[targetUnitID].unitType == UT_E_SWORD) {
                targetFactor /= 2;
            }
            if (DAT_UnitsState::instance.units[unitID].stateBasedSpeed > 0) {
                targetFactor /= 2;
            } else if (DAT_UnitsState::instance.units[unitID].unitType == UT_E_KNIGHT
                && !DAT_UnitsState::instance.units[unitID].isMatchingSpeed) {
                targetFactor /= 3;
            } else if (DAT_UnitsState::instance.units[unitID].unitType == UT_E_SWORD) {
                targetFactor /= 2;
            }
            int distanceX = abs(*unitCurrentX - targetX);
            int distance = abs(*unitCurrentY - targetY);
            if (distanceX > distance) {
                distance = distanceX;
            }
            if ((distance - 2) * targetFactor < 0) {
                return;
            }
            int pathIndex = DAT_UnitsState::instance.units[unitID].currentIndexInPathPlan;
            if (pathIndex >= DAT_UnitsState::instance.units[unitID].totalSizeOfPathPlan) {
                return;
            }
            int cost = unitStep;
            do {
                int direction = (char)DAT_UnitsState::instance.units[unitID].pathPlanStart[pathIndex / 2];
                if (pathIndex & 1) {
                    direction >>= 4;
                } else {
                    direction &= 0xf;
                }
                *unitCurrentX = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.xOffset
                    + *unitCurrentX;
                *unitCurrentY += DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.yOffset;
                distanceX = abs(*unitCurrentX - targetX);
                distance = abs(*unitCurrentY - targetY);
                if (distanceX > distance) {
                    distance = distanceX;
                }
                if ((distance - 2) * targetFactor < cost) {
                    return;
                }
                cost += unitStep;
                ++pathIndex;
            } while (pathIndex < DAT_UnitsState::instance.units[unitID].totalSizeOfPathPlan);
        }

    }
}
}
