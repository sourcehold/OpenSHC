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
            int _unitTribeID;
            int _tribeCountdown;
            int _tribeID_chosen;
            Unit* _pUnit;
            int _unitIDCountdown;
            int _stanceCount[3];
            int _countDefensive;
            int _countStandground;
            int _tribeID_1;
            bool _atLeastTwoTribes;
            _atLeastTwoTribes = false;
            this->tribeCopiedToSlot0 = 0;
            int _index = 0;
            _stanceCount[0] = 0;
            _stanceCount[1] = 0;
            _stanceCount[2] = 0;
            int _countAggressive = _index;
            _countDefensive = 0;
            _countStandground = 0;
            if (1 < DAT_UnitsState::instance.maxUnitCount) {
                _pUnit = &DAT_UnitsState::instance.units[1];
                _unitIDCountdown = DAT_UnitsState::instance.maxUnitCount - 1;
                _tribeID_1 = -1;
                do {
                    _tribeID_chosen = _tribeID_1;
                    if (_pUnit->logicalState == Map::Units::ULS_NORMAL && !_pUnit->dying
                        && _pUnit->ifSelectedThenPlayerID == playerID
                        && (_unitTribeID = (int)_pUnit->tribeID,
                            0 < _unitTribeID
                                && (_stanceCount[(short)this->tribes[_unitTribeID].unitStance]
                                    = _stanceCount[(short)this->tribes[_unitTribeID].unitStance] + 1,
                                    _tribeID_chosen = _unitTribeID, _tribeID_1 != -1))
                        && _unitTribeID != _tribeID_1) {
                        /*
                          if unit is in a tribe, count its tribes stance   and if
                         */
                        _atLeastTwoTribes = true;
                    }
                    _pUnit = _pUnit + 0x248;
                    _unitIDCountdown = _unitIDCountdown + -1;
                    _tribeID_1 = _tribeID_chosen;
                } while (_unitIDCountdown);
                _countAggressive = _stanceCount[2];
                _countDefensive = _stanceCount[1];
                _countStandground = _stanceCount[0];
                if ((_tribeID_chosen != -1) && (!_atLeastTwoTribes)) {
                    /*
                      this is an int-by-int sized copy function
                     */
                    int const* _src = (int const*)&this->tribes[_tribeID_chosen];
                    int* _dst = (int*)&this->tribes[0];
                    for (_tribeCountdown = 0; _tribeCountdown < 205; ++_tribeCountdown) {
                        _dst[_tribeCountdown] = _src[_tribeCountdown];
                    }
                    this->tribeCopiedToSlot0 = 1;
                }
            }
            if (_countAggressive + _countDefensive + _countStandground == 0) {
                this->tribes[0].unitStance = Map::Units::Behavior::USE_STAND_GROUND;
            }
            if ((_countDefensive <= _countAggressive) && (_countStandground <= _countAggressive)) {
                this->tribes[0].unitStance = Map::Units::Behavior::USE_AGGRESSIVE;
            }
            this->tribes[0].unitStance = (ushort)(_countStandground <= _countDefensive);
        }

    }
}
}
