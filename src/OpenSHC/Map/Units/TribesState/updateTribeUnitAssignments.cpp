#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_CurrentTribeID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00527330
        void TribesState::updateTribeUnitAssignments()
        {
            uint _unitID;
            this->clans = 0;
            this->field2_0x8 = 1;
            DAT_CurrentTribeID::instance = 1;
            do {
                int _state = this->tribes[DAT_CurrentTribeID::instance].tribeState;
                int _tribeUnitIndex = 0;
                if (_state) {
                    int _tribeID = DAT_CurrentTribeID::instance;
                    if (_state != 3) {
                        int _tribeSize = this->tribes[DAT_CurrentTribeID::instance].size;
                        if (_tribeSize <= 0) {
                            int _tribeTime = this->tribes[DAT_CurrentTribeID::instance].time;
                            if (_tribeTime && (int)DAT_GameCore::instance.mapTimeInTicks <= (int)_tribeTime
                                && _tribeTime)
                                goto LAB_00527425;
                        } else {
                            int local_4 = 0;
                            if (0 < _tribeSize) {
                                do {
                                    _unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getSpecificUnitFromTribe,
                                        this)(_tribeID, _tribeUnitIndex);
                                    int _unitLogicalState = DAT_UnitsState::instance.units[_unitID].logicalState;
                                    _tribeUnitIndex = _tribeUnitIndex + 1;
                                    if ((short)_unitLogicalState < 1
                                        || (2 < (short)_unitLogicalState
                                            && (_unitLogicalState != Map::Units::ULS_TRANSITIONING))
                                        || DAT_UnitsState::instance.units[_unitID].dying != 0
                                        || DAT_UnitsState::instance.units[_unitID].tribeID != _tribeID) {
                                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::removeUnitFromTribe, this)(
                                            _unitID, _tribeID);
                                        _tribeID = DAT_CurrentTribeID::instance;
                                    } else {
                                        local_4 = local_4 + 1;
                                    }
                                } while (_tribeUnitIndex < _tribeSize);
                                if (local_4) {
                                    this->clans = this->clans + 1;
                                    this->field2_0x8 = DAT_CurrentTribeID::instance;
                                    goto LAB_00527425;
                                }
                            }
                        }
                    }
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::clearTribe, this)(_tribeID);
                }
            LAB_00527425:
                DAT_CurrentTribeID::instance = DAT_CurrentTribeID::instance + 1;
                if (0x4e1 < DAT_CurrentTribeID::instance) {}
            } while (true);
        }

    }
}
}
