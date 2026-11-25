#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051D730
        void TroopValueState::updateActiveAttackWaveState(int attackWave)
        {
            int playerID = (char)DAT_TroopValueState::instance.attackInfo.attackWavePlayerIDArray[attackWave];
            if (DAT_GameCore::instance.gameMode_2 == Game::GM_BUILDERUnk
                && DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == Map::MT_SIEGE) {
                playerID = 2;
            }
            int const ticker = DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackWave];
            int const nextTicker = ticker + 1;
            DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackWave] = nextTicker;
            if (0 < ticker) {
                if (100 < nextTicker) {
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::applyTribeBehaviorType, DAT_TribesState::ptr)(
                        attackWave, Map::Units::STBT_0x400);
                }
                if (1000 < DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackWave]) {
                    DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackWave] = 0;
                }
                return;
            }
            ++DAT_TroopValueState::instance.attackInfo.someCounter1;
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::removeSiegeBuildings, DAT_BuildingsState::ptr)(
                attackWave, playerID);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::exitSiegeEquipmentForWave, this)(attackWave);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                attackWave, 1000, 10000, Map::Units::STBT_0x3ff);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                Map::Units::STBT_0x3ff, Map::Units::STBT_1, 0, 10);
        }

    }
}
}
