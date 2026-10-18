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
            AITribeTypeShort tribeType;
            int _unitID;
            int _tribeUnitIndex;
            for (int _tribeID = 1; _tribeID < 1250; _tribeID = _tribeID + 1) {
                if (DAT_TribesState::instance.tribes[_tribeID].tribeState
                    && DAT_TribesState::instance.tribes[_tribeID].attackWave == wave
                    && (tribeType = DAT_TribesState::instance.tribes[_tribeID].tribeType,
                        tribeType == ((AITribeType)0x13)
                            || ((((tribeType == ((AITribeType)0x14) || (tribeType == ((AITribeType)0x15)))
                                     || (tribeType == ((AITribeType)0x16)))
                                || ((tribeType == ((AITribeType)0x17) || (tribeType == ((AITribeType)0x18)))))))
                    && (_tribeUnitIndex = 0, 0 < DAT_TribesState::instance.tribes[_tribeID].size)) {
                    do {
                        _unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe,
                            DAT_TribesState::ptr)(_tribeID, _tribeUnitIndex);
                        _tribeUnitIndex = _tribeUnitIndex + 1;
                        if ((DAT_UnitsState::instance.units[_unitID].logicalState == Map::Units::ULS_NORMAL)
                            && (DAT_UnitsState::instance.units[_unitID].dying == 0)) {
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeAnInstruction,
                                DAT_TribesState::ptr)(_tribeID, Map::Units::UIT_EXIT_SIEGE_EQUIPMENT, _unitID,
                                DAT_UnitsState::instance.units[_unitID].uid, 0);
                            DAT_UnitsState::instance.units[_unitID].state.generic = Map::Units::States::US_DISAPPEAR;
                        }
                    } while (_tribeUnitIndex < DAT_TribesState::instance.tribes[_tribeID].size);
                }
            }
        }

    }
}
}
