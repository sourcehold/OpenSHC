#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;
        using Map::Units::Behavior::UnitStanceEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00522CA0
        void TribesState::snapshotSelectionTribeAndComputeStance(int playerID)
        {
            BOOLEnum _atLeastTwoTribes = FALSE;
            this->tribeCopiedToSlot0 = 0;
            int _stanceCount[3];
            _stanceCount[0] = 0;
            _stanceCount[1] = 0;
            _stanceCount[2] = 0;
            int _lastTribeID = -1;
            if (1 < DAT_UnitsState::instance.maxUnitCount) {
                Unit* _pUnit = &DAT_UnitsState::instance.units[1];
                int _unitIDCountdown = DAT_UnitsState::instance.maxUnitCount - 1;
                do {
                    if (_pUnit->logicalState == Map::Units::ULS_NORMAL && !_pUnit->dying
                        && _pUnit->ifSelectedThenPlayerID == playerID) {
                        int const _unitTribeID = (int)_pUnit->tribeID;
                        if (0 < _unitTribeID) {
                            /*
                              count the stance of every tribe the selection touches, and
                              notice as soon as it touches two different ones
                             */
                            int const _stance = (short)this->tribes[_unitTribeID].unitStance;
                            _stanceCount[_stance] = _stanceCount[_stance] + 1;
                            if (_lastTribeID != -1 && _unitTribeID != _lastTribeID) {
                                _atLeastTwoTribes = TRUE;
                            }
                            _lastTribeID = _unitTribeID;
                        }
                    }
                    _pUnit = _pUnit + 1;
                    _unitIDCountdown = _unitIDCountdown + -1;
                } while (_unitIDCountdown);
                if (_lastTribeID != -1 && !_atLeastTwoTribes) {
                    /*
                      A whole-struct assignment, which is the `rep movsd` of 0xcd dwords the
                      original has; a hand-written int-by-int copy compiles to a loop.

                      And then it returns: the block at 0x522d42 ends in its own `ret 4`, so
                      a selection that is all one tribe keeps the stance it just copied
                      instead of having the majority written over it. That is also why the
                      three counts are only loaded out of the array at 0x522d6a, on the path
                      where the copy did not happen.
                     */
                    this->tribes[0] = this->tribes[_lastTribeID];
                    this->tribeCopiedToSlot0 = 1;
                    return;
                }
            }
            /*
              The three counts are read straight out of the array, which is where the
              original's own three slots are: it loads [esp+0x18], [esp+0x14] and
              [esp+0x10] into registers at 0x522d6a and nowhere else, and diff_slots.py
              shows our extra fourth slot is a spill of a redundant copy.
             */
            if (_stanceCount[2] + _stanceCount[1] + _stanceCount[0] == 0) {
                this->tribes[0].unitStance = Map::Units::Behavior::USE_STAND_GROUND;
                return;
            }
            if (_stanceCount[2] < _stanceCount[1] || _stanceCount[2] < _stanceCount[0]) {
                this->tribes[0].unitStance = (ushort)(_stanceCount[0] <= _stanceCount[1]);
                return;
            }
            this->tribes[0].unitStance = Map::Units::Behavior::USE_AGGRESSIVE;
        }

    }
}
}
