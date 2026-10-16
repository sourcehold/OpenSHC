#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using AI::Tribes::AITribeType;
        using Map::Units::UnitInstructionType;
        using Map::Units::UnitLogicState;
        using Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051BD10
        void TroopValueState::exitSiegeEquipmentForWave(int wave)
        {
            AITribeTypeShort AVar1;
            int _unitID;
            int _tribeID;
            Tribe* _tribe;
            int _tribeUnitIndex;
            _tribeID = 1;
            _tribe = &DAT_TribesState::instance.tribes[1];
            do {
                if ((((_tribe->tribeState) && (_tribe->attackWave == wave))
                        && ((AVar1 = _tribe->tribeType,
                            AVar1 == ((AITribeType)0x13)
                                || ((((AVar1 == ((AITribeType)0x14) || (AVar1 == ((AITribeType)0x15)))
                                         || (AVar1 == ((AITribeType)0x16)))
                                    || ((AVar1 == ((AITribeType)0x17) || (AVar1 == ((AITribeType)0x18)))))))))
                    && (_tribeUnitIndex = 0, 0 < _tribe->size)) {
                    do {
                        _unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe,
                            DAT_TribesState::ptr)(_tribeID, _tribeUnitIndex);
                        _tribeUnitIndex = _tribeUnitIndex + 1;
                        if ((DAT_UnitsState::instance.units[_unitID].logicalState == Map::Units::ULS_NORMAL)
                            && (DAT_UnitsState::instance.units[_unitID].dying == 0)) {
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeAnInstruction,
                                DAT_TribesState::ptr)(_tribeID, Map::Units::UIT_EXIT_SIEGE_EQUIPMENT, _unitID,
                                DAT_UnitsState::instance.units[_unitID].uid, 0);
                            DAT_UnitsState::instance.units[_unitID].state.generic
                                = Map::Units::States::US_DISAPPEAR;
                        }
                    } while (_tribeUnitIndex < _tribe->size);
                }
                _tribe = _tribe + 0x19a;
                _tribeID = _tribeID + 1;
            } while ((int)_tribe < 0x17623a2);
        }

    }
}
}
