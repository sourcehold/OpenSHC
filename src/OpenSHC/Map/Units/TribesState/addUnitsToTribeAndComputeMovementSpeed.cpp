#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // maxUnitCount (uint) is compared signed (jle at 0x5229E7, jl at 0x522A46).
        // FUNCTION: STRONGHOLDCRUSADER 0x005229C0
        void TribesState::addUnitsToTribeAndComputeMovementSpeed(int playerID, int tribeID)
        {
            int healthSum = 0;
            int minSpeed = 100;
            int maxSpeed = 0;
            for (int unitID = 1; unitID < (int)DAT_UnitsState::instance.maxUnitCount; ++unitID) {
                if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                    && DAT_UnitsState::instance.units[unitID].dying == 0
                    && DAT_UnitsState::instance.units[unitID].ifSelectedThenPlayerID == playerID) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToTribe, this)(unitID, tribeID);
                    if (DAT_UnitsState::instance.units[unitID].movementSpeed < minSpeed) {
                        minSpeed = DAT_UnitsState::instance.units[unitID].movementSpeed;
                    }
                    if (DAT_UnitsState::instance.units[unitID].movementSpeed > maxSpeed) {
                        maxSpeed = DAT_UnitsState::instance.units[unitID].movementSpeed;
                    }
                    healthSum += DAT_UnitsState::instance.units[unitID].healthPercentage;
                }
            }
            short const size = this->tribes[tribeID].size;
            this->tribes[tribeID].size2Unk = size;
            if (size > 0) {
                int const selectionTargetUnitID = this->tribes[tribeID].selectionTargetUnitID;
                this->tribes[tribeID].facingDirection_1
                    = DAT_UnitsState::instance.units[selectionTargetUnitID].facingDirection;
                this->tribes[tribeID].facingDirection_2
                    = DAT_UnitsState::instance.units[selectionTargetUnitID].facingDirection;
                this->tribes[tribeID].facingDirection_3
                    = DAT_UnitsState::instance.units[selectionTargetUnitID].facingDirection;
                this->tribes[tribeID].movementRunUpTime
                    = DAT_UnitsState::instance.units[selectionTargetUnitID].movementRunUpTime;
                this->tribes[tribeID].maximumMovementSpeed = (short)maxSpeed;
                this->tribes[tribeID].minimumMovementSpeed = (short)minSpeed;
                this->tribes[tribeID].movementSpeed = (short)minSpeed;
                this->tribes[tribeID].field_0x200 = 0;
                this->tribes[tribeID].field_0x202 = 0;
                this->tribes[tribeID].initialMoveOrderGiven = 0;
                this->tribes[tribeID].field_0x208 = 0;
                this->tribes[tribeID].unitsHealthPercentage = (short)(healthSum / size);
                this->tribes[tribeID].field_0x20c = 0;
            }
        }

    } // namespace Units
} // namespace Map
} // namespace OpenSHC
