#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // The statistics are recomputed over all selected units of playerID, not over the tribe members.
        // maxUnitCount (uint) is compared signed (jle at 0x522B28).
        // FUNCTION: STRONGHOLDCRUSADER 0x00522B00
        void TribesState::addUnitToTribeAndUpdateTribeMovementSpeed(int playerID, uint unitID, int tribeID)
        {
            int maxSpeed = 0;
            int healthSum = 0;
            int minSpeed = 100;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToTribe, this)(unitID, tribeID);
            for (int i = 1; i < (int)DAT_UnitsState::instance.maxUnitCount; ++i) {
                if (DAT_UnitsState::instance.units[i].logicalState == ULS_NORMAL
                    && DAT_UnitsState::instance.units[i].dying == 0
                    && DAT_UnitsState::instance.units[i].ifSelectedThenPlayerID == playerID) {
                    if (DAT_UnitsState::instance.units[i].movementSpeed < minSpeed) {
                        minSpeed = DAT_UnitsState::instance.units[i].movementSpeed;
                    }
                    if (DAT_UnitsState::instance.units[i].movementSpeed > maxSpeed) {
                        maxSpeed = DAT_UnitsState::instance.units[i].movementSpeed;
                    }
                    healthSum += DAT_UnitsState::instance.units[i].healthPercentage;
                }
            }
            this->tribes[tribeID].size2Unk = this->tribes[tribeID].size;
            if (this->tribes[tribeID].size > 0) {
                this->tribes[tribeID].minimumMovementSpeed = (short)minSpeed;
                this->tribes[tribeID].movementSpeed = (short)minSpeed;
                this->tribes[tribeID].maximumMovementSpeed = (short)maxSpeed;
                this->tribes[tribeID].unitsHealthPercentage = (short)(healthSum / this->tribes[tribeID].size);
            }
        }

    }
}
}
