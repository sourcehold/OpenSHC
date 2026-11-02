#include "../../../Map.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00522090
        void TribesState::playAttackCommandFeedback(int param_1)
        {
            UnitType unitType;
            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::selectionContainsCombatUnit, DAT_UnitsState::ptr)(1);
            int iVar1 = param_1;
            unitType
                = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getMajoritySelectedUnitType, this)(param_1, &param_1);
            if (unitType == Map::Units::UT_S_BATTERINGRAM || unitType == Map::Units::UT_S_CATAPULT
                || unitType == Map::Units::UT_S_TREBUCHET || unitType == Map::Units::UT_S_MANGONEL
                || unitType == Map::Units::UT_S_BALLISTA || unitType == Map::Units::UT_S_FBALLISTA) {
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::playUnitMoveSpeech, this)(
                    DAT_TribesState::instance.DAT_CurrentTribeID);
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::playUnitSelectionSound, this)(iVar1);
            } else {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(unitType, 0x15);
                if (unitType != Map::Units::UT_E_ENGINEER) {
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::playUnitSelectionSound, this)(iVar1);
                }
            }
        }

    }
}
}
