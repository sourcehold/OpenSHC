#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00522B00
        void TribesState::addUnitToTribeAndUpdateTribeMovementSpeed(int param_1, uint unitID, int tribeID)
        {
            /*
              The three speeds are `int`: the original reads one with
              `movsx ecx, word ptr [eax]` and compares and copies it 32 bits wide
              (`cmp ecx, esi`, `mov esi, ecx`), where `short` locals give a `movzx` and
              16-bit `cmp cx, si` / `movzx esi, cx`. The tribe size stays narrow - that one
              really is `movzx` plus `test ax, ax`.
             */
            Unit* _ptrUnit;
            int _maximumSpeed;
            int _minimumSpeed;
            int _totalHealth;
            short _tribeSize;
            int _movementSpeed;
            int _tribeID;
            _tribeID = tribeID;
            _maximumSpeed = 0;
            _totalHealth = 0;
            _minimumSpeed = 100;
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, this)(unitID, tribeID);
            if (1 < DAT_UnitsState::instance.maxUnitCount) {
                tribeID = DAT_UnitsState::instance.maxUnitCount - 1;
                _ptrUnit = &DAT_UnitsState::instance.units[1];
                do {
                    if (_ptrUnit->logicalState == Map::Units::ULS_NORMAL && !_ptrUnit->dying
                        && _ptrUnit->ifSelectedThenPlayerID == param_1) {
                        _movementSpeed = _ptrUnit->movementSpeed;
                        if (_movementSpeed < _minimumSpeed) {
                            _minimumSpeed = _movementSpeed;
                        }
                        if (_movementSpeed > _maximumSpeed) {
                            _maximumSpeed = _movementSpeed;
                        }
                        _totalHealth = _totalHealth + _ptrUnit->healthPercentage;
                    }
                    _ptrUnit = _ptrUnit + 1;
                    tribeID = tribeID + -1;
                } while (tribeID);
            }
            _tribeSize = this->tribes[_tribeID].size;
            this->tribes[_tribeID].size2Unk = _tribeSize;
            if (0 < _tribeSize) {
                this->tribes[_tribeID].minimumMovementSpeed = _minimumSpeed;
                this->tribes[_tribeID].movementSpeed = _minimumSpeed;
                this->tribes[_tribeID].maximumMovementSpeed = _maximumSpeed;
                this->tribes[_tribeID].unitsHealthPercentage = (short)(_totalHealth / (int)_tribeSize);
            }
        }

    }
}
}
