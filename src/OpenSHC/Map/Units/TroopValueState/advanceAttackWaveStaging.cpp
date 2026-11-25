#include "../TroopValueState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"

#include "OpenSHC/Globals/DAT_AttackInfoDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051D690
        void TroopValueState::advanceAttackWaveStaging(int param_1)
        {
            DAT_TroopValueState::instance.attackInfo.attackAlarmPlayed = FALSE;
            DAT_TroopValueState::instance.attackInfo.value3Array01[param_1] = 2;
            DAT_TroopValueState::instance.attackInfo.attackWaveTicker[param_1] = 0;
            MACRO_CALL_MEMBER(Game::GameStateStructures_Func::nof_fpoints_locationFinder, DAT_GameState::ptr)();
            ++DAT_TroopValueState::instance.attackInfo.someCounter1;
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                param_1, 2, 100000, Map::Units::STBT_0x3fb);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                Map::Units::STBT_0x3fe, Map::Units::STBT_5, 0, 50);
            if (DAT_TroopValueState::instance.attackInfo.casDis >= DAT_AttackInfoDefinedData::instance
                    .AICasDisThreshold[DAT_TroopValueState::instance.attackInfo.attacker]) {
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                    param_1, 1000, 10000, Map::Units::STBT_5);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                    Map::Units::STBT_5, Map::Units::STBT_1, 0, 40);
            }
        }

    }
}
}
