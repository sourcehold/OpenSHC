#include "../../../Map.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AttackInfoDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

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
            _playerID = this->attackInfo.attackWavePlayerIDArray[attackID];
            BVar2 = MACRO_CALL_MEMBER(
                Map::Units::TroopValueState_Func::isLessThanPercentageOfTribesInAttackDying, this)(
                attackID, (int)((int)(50)));
            if (BVar2) {
                if (this->attackInfo.attackAlarmPlayed)
                    goto LAB_00520489;
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::playAttackAlarmSound, this)();
            }
            if (!this->attackInfo.attackAlarmPlayed) {}
        LAB_00520489:
            if (this->attackInfo.attackWaveTicker[attackID] == 0) {
                this->attackInfo.someCounter1 = this->attackInfo.someCounter1 + 1;
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::aiRecomputeAttacks2, this)(1, attackID);
                if (this->attackInfo.tentPoints < 1) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::placeSiegeTentsAndAssignEngineers,
                        this)(attackID, 0);
                } else {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::placeSiegeTentsAndAssignEngineers,
                        this)(attackID, 1);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::placeTunnelForEveryTunneler, this)(
                        attackID);
                }
                tribeSizeSumLimit = *(int*)((int)this->attackInfo.townValuesArray + (char)_playerID * 0x177bc + -4);
                if (tribeSizeSumLimit) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn,
                        this)(attackID, 2, tribeSizeSumLimit, Map::Units::STBT_0x3f5);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                        Map::Units::STBT_0x3f5, Map::Units::STBT_1, 0, 0x14);
                }
                if (this->attackInfo.people3) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn,
                        this)(attackID, 2, this->attackInfo.people3, Map::Units::STBT_0x3fb);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                        Map::Units::STBT_0x3fb, Map::Units::STBT_1, 5, 0x1e);
                }
            }
            piVar1 = this->attackInfo.attackWaveTicker + attackID;
            *piVar1 = *piVar1 + 1;
            if (DAT_AttackInfoDefinedData::instance.AttackWaveDurationPerAttacker[this->attackInfo.attacker]
                <= this->attackInfo.attackWaveTicker[attackID]) {
                bVar3 = DAT_GameCore::instance.missionNumber1to20 == 39;
                this->attackInfo.attackWaveTicker[attackID] = 10000;
                this->attackInfo.value3Array01[attackID] = 3;
                this->attackInfo.value10 = 0;
                if ((bVar3) && (this->attackInfo.attacker == 4)) {
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
