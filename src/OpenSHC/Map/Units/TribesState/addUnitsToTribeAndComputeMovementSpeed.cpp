#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;

        /*
          Its `short` tribe-size local stays narrow: widening it costs 17.6 points
          (64.1% -> 46.5%), the largest such loss in the namespace.
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x005229C0
        void TribesState::addUnitsToTribeAndComputeMovementSpeed(int playerID, int tribeID)
        {
            Unit* _pUnit;
            uint _unitID;
            /*
              The three speeds are `int`, as in the sibling
              addUnitToTribeAndUpdateTribeMovementSpeed, where the same change gained 9.9
              points: the original reads one with a single `movsx` and compares and copies
              it 32 bits wide, where `short` locals give a `movzx` plus 16-bit compares.
              The size and the target unit stay narrow.
             */
            int local_8;
            int _movementSpeed;
            int _maximumSpeed;
            short _targetUnit;
            local_8 = 0;
            int _minimumSpeed = 100;
            _maximumSpeed = 0;
            if (1 < DAT_UnitsState::instance.maxUnitCount) {
                _pUnit = &DAT_UnitsState::instance.units[1];
                _unitID = 1;
                do {
                    if (_pUnit->logicalState == Map::Units::ULS_NORMAL && !_pUnit->dying
                        && _pUnit->ifSelectedThenPlayerID == playerID) {
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, this)(_unitID, tribeID);
                        _movementSpeed = _pUnit->movementSpeed;
                        if (_movementSpeed < _minimumSpeed) {
                            _minimumSpeed = _movementSpeed;
                        }
                        if (_movementSpeed > _maximumSpeed) {
                            _maximumSpeed = _movementSpeed;
                        }
                        local_8 = local_8 + _pUnit->healthPercentage;
                    }
                    _unitID = _unitID + 1;
                    _pUnit = _pUnit + 1;
                } while ((int)_unitID < DAT_UnitsState::instance.maxUnitCount);
            }
            short sVar1 = this->tribes[tribeID].size;
            this->tribes[tribeID].size2Unk = sVar1;
            if (0 < sVar1) {
                _targetUnit = this->tribes[tribeID].selectionTargetUnitID;
                this->tribes[tribeID].facingDirection_1 = DAT_UnitsState::instance.units[_targetUnit].facingDirection;
                this->tribes[tribeID].facingDirection_2 = DAT_UnitsState::instance.units[_targetUnit].facingDirection;
                this->tribes[tribeID].facingDirection_3 = DAT_UnitsState::instance.units[_targetUnit].facingDirection;
                this->tribes[tribeID].movementRunUpTime = DAT_UnitsState::instance.units[_targetUnit].movementRunUpTime;
                this->tribes[tribeID].maximumMovementSpeed = _maximumSpeed;
                this->tribes[tribeID].minimumMovementSpeed = _minimumSpeed;
                this->tribes[tribeID].movementSpeed = _minimumSpeed;
                this->tribes[tribeID].field61_0x200 = 0;
                this->tribes[tribeID].field62_0x202 = 0;
                this->tribes[tribeID].initialMoveOrderGiven = 0;
                this->tribes[tribeID].field65_0x208 = 0;
                this->tribes[tribeID].field67_0x20c = 0;
                this->tribes[tribeID].unitsHealthPercentage = (short)(local_8 / (int)sVar1);
            }
        }

    }
}
}
