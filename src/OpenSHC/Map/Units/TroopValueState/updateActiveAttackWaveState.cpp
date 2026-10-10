#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Game::GameMode2;
        using Map::MapType2;
        using Map::Units::SomeTribeBehaviorType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051D730
        void TroopValueState::updateActiveAttackWaveState(int attackWave)
        {
            int iVar1;
            int iVar2;
            int playerID;
            playerID = (int)(char)this->attackInfo.attackWavePlayerIDArray[attackWave];
            if ((DAT_GameCore::instance.gameMode_2 == Game::GM_BUILDERUnk)
                && (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == Map::MT_SIEGE)) {
                playerID = 2;
            }
            iVar2 = this->attackInfo.attackWaveTicker[attackWave];
            iVar1 = iVar2 + 1;
            this->attackInfo.attackWaveTicker[attackWave] = iVar1;
            if (iVar2 < 1) {
                this->attackInfo.someCounter1 = this->attackInfo.someCounter1 + 1;
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::removeSiegeBuildings,
                    DAT_BuildingsState::ptr)(attackWave, playerID);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::exitSiegeEquipmentForWave, this)(
                    attackWave);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                    attackWave, 1000, 10000, (SomeTribeBehaviorType)((int)(1023)));
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                    (Map::Units::SomeTribeBehaviorType)1023, Map::Units::STBT_1, 0, 10);
            } else {
                if (100 < iVar1) {
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::applyTribeBehaviorType,
                        DAT_TribesState::ptr)(attackWave, (SomeTribeBehaviorType)((int)(1024)));
                }
                if (1000 < this->attackInfo.attackWaveTicker[attackWave]) {
                    this->attackInfo.attackWaveTicker[attackWave] = 0;
                }
            }
        }

    }
}
}
