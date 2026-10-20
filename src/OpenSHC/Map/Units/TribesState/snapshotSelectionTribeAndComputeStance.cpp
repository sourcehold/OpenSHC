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
            /*
              Three locals rather than reading _stanceCount[] again at the end: the extra
              stack slot costs nothing and reading the array directly measures worse
              (quick_diff 0.5806 -> 0.4725, and it moves `this` out of ebx).
             */
            int _countAggressive = 0;
            int _countDefensive = 0;
            int _countStandground = 0;
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
                _countAggressive = _stanceCount[2];
                _countDefensive = _stanceCount[1];
                _countStandground = _stanceCount[0];
                if (_lastTribeID != -1 && !_atLeastTwoTribes) {
                    /*
                      A whole-struct assignment, which is the `rep movsd` of 0xcd dwords the
                      original has; a hand-written int-by-int copy compiles to a loop.
                     */
                    this->tribes[0] = this->tribes[_lastTribeID];
                    this->tribeCopiedToSlot0 = 1;
                }
            }
            if (_countAggressive + _countDefensive + _countStandground == 0) {
                this->tribes[0].unitStance = Map::Units::Behavior::USE_STAND_GROUND;
                return;
            }
            if (_countAggressive < _countDefensive || _countAggressive < _countStandground) {
                this->tribes[0].unitStance = (ushort)(_countStandground <= _countDefensive);
                return;
            }
            this->tribes[0].unitStance = Map::Units::Behavior::USE_AGGRESSIVE;
        }

    }
}
}
