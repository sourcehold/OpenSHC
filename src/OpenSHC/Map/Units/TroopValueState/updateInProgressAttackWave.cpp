#include "../../../Map.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AttackInfoDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::SomeTribeBehaviorType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00520450
        void TroopValueState::updateInProgressAttackWave(int attackID)
        {
            int* piVar1;
            int tribeSizeSumLimit;
            BOOLEnum BVar2;
            bool bVar3;
            byte _playerID;
            _playerID = DAT_TroopValueState::instance.attackInfo.attackWavePlayerIDArray[attackID];
            BVar2 = MACRO_CALL_MEMBER(
                Map::Units::TroopValueState_Func::isLessThanPercentageOfTribesInAttackDying, this)(attackID, (int)(50));
            if (BVar2) {
                if (DAT_TroopValueState::instance.attackInfo.attackAlarmPlayed)
                    goto LAB_00520489;
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::playAttackAlarmSound, this)();
            }
            if (!DAT_TroopValueState::instance.attackInfo.attackAlarmPlayed) {}
        LAB_00520489:
            if (DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackID] == 0) {
                DAT_TroopValueState::instance.attackInfo.someCounter1
                    = DAT_TroopValueState::instance.attackInfo.someCounter1 + 1;
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::aiRecomputeAttacks2, this)(1, attackID);
                if (DAT_TroopValueState::instance.attackInfo.tentPoints < 1) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::placeSiegeTentsAndAssignEngineers, this)(
                        attackID, 0);
                } else {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::placeSiegeTentsAndAssignEngineers, this)(
                        attackID, 1);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::placeTunnelForEveryTunneler, this)(attackID);
                }
                tribeSizeSumLimit = *(int*)((int)DAT_TroopValueState::instance.attackInfo.townValuesArray
                    + (char)_playerID * 0x177bc + -4);
                if (tribeSizeSumLimit) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                        attackID, 2, tribeSizeSumLimit, Map::Units::STBT_0x3f5);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                        Map::Units::STBT_0x3f5, Map::Units::STBT_1, 0, 0x14);
                }
                if (DAT_TroopValueState::instance.attackInfo.people3) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                        attackID, 2, DAT_TroopValueState::instance.attackInfo.people3, Map::Units::STBT_0x3fb);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                        Map::Units::STBT_0x3fb, Map::Units::STBT_1, 5, 0x1e);
                }
            }
            piVar1 = DAT_TroopValueState::instance.attackInfo.attackWaveTicker + attackID;
            *piVar1 = *piVar1 + 1;
            if (DAT_AttackInfoDefinedData::instance
                    .AttackWaveDurationPerAttacker[DAT_TroopValueState::instance.attackInfo.attacker]
                <= DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackID]) {
                bVar3 = DAT_GameCore::instance.missionNumber1to20 == 39;
                DAT_TroopValueState::instance.attackInfo.attackWaveTicker[attackID] = 10000;
                DAT_TroopValueState::instance.attackInfo.value3Array01[attackID] = 3;
                DAT_TroopValueState::instance.attackInfo.value10 = 0;
                if ((bVar3) && (DAT_TroopValueState::instance.attackInfo.attacker == 4)) {
                    /*
                      "we are the macemen"
                     */
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)("Mace_s4.wav");
                }
            }
        }

    }
}
}
