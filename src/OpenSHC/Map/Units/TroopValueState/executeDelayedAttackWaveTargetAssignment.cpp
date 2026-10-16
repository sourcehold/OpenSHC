#include "../../../Map.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Game::GameMode2;
        using Map::MapType2;
        using Map::Units::SomeTribeBehaviorType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00520CD0
        void TroopValueState::executeDelayedAttackWaveTargetAssignment(int param_1)
        {
            int* piVar1;
            short sVar2;
            int tribeSizeSumLimit;
            BOOLEnum BVar3;
            int iVar4;
            iVar4 = (int)(char)this->attackInfo.attackWavePlayerIDArray[param_1];
            if ((DAT_GameCore::instance.gameMode_2 == Game::GM_BUILDERUnk)
                && (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == Map::MT_SIEGE)) {
                iVar4 = 2;
            }
            this->attackInfo.field128057_0x469d8 = this->attackInfo.field128057_0x469d8 + 1;
            BVar3 = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::canKeepReachSignpostZone,
                DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, iVar4, param_1);
            if (!BVar3) {
                this->attackInfo.value3Array01[param_1] = 3;
                this->attackInfo.attackWaveTicker[param_1] = 0;
            }
            piVar1 = this->attackInfo.attackWaveTicker + param_1;
            *piVar1 = *piVar1 + 1;
            if (399 < this->attackInfo.attackWaveTicker[param_1]) {
                this->attackInfo.attackWaveTicker[param_1] = 0;
                this->attackInfo.someCounter1 = this->attackInfo.someCounter1 + 1;
                sVar2 = this->attackInfo.attackWaveAssignmentAttempts[param_1];
                this->attackInfo.attackWaveAssignmentAttempts[param_1] = sVar2 + 1;
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::aiRecomputeAttacks, this)(
                    (int)sVar2, param_1);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                    param_1, 1000, 10000, Map::Units::STBT_0x41b);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                    Map::Units::STBT_0x41b, Map::Units::STBT_1, 0x32, 0x32);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                    param_1, 1000, 10000, Map::Units::STBT_0x418);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                    Map::Units::STBT_0x418, Map::Units::STBT_1, 0x14, 0x46);
                if ((this->attackInfo.people3) && (9 < this->attackInfo.field86974_0x20f74)) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn,
                        this)(param_1, 1, this->attackInfo.people3, Map::Units::STBT_0x3fb);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                        Map::Units::STBT_0x3fb, Map::Units::STBT_1, 5, 0xf);
                }
                if (this->attackInfo.lord2) {
                    MACRO_CALL_MEMBER(
                        Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(param_1,
                        (int)((int)(this->attackInfo.field_0x20f3c)),
                        1000, Map::Units::STBT_0x3fd);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::assignBehaviorTypeToNearbyTribes,
                        this)(Map::Units::STBT_0x3fd, 1, 0, 5);
                }
                if (this->attackInfo.high3) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn,
                        this)(param_1, this->attackInfo.high3, 10000, Map::Units::STBT_0x3f8);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                        Map::Units::STBT_0x3f8, Map::Units::STBT_1, 0x14, 10);
                }
                if (this->attackInfo.arch3) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn,
                        this)(param_1, this->attackInfo.arch3, 10000, Map::Units::STBT_0x3f9);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                        Map::Units::STBT_0x3f9, Map::Units::STBT_1, 0x14, 10);
                }
                if (this->attackInfo.people3) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn,
                        this)(param_1, 2, this->attackInfo.people3, Map::Units::STBT_0x3fb);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                        Map::Units::STBT_0x3fb, Map::Units::STBT_1, 0, 10);
                }
                tribeSizeSumLimit = *(int*)((int)this->attackInfo.townValuesArray + iVar4 * 0x177bc + -4);
                if (tribeSizeSumLimit) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn,
                        this)(param_1, 1, tribeSizeSumLimit, Map::Units::STBT_0x3f5);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                        Map::Units::STBT_0x3f5, Map::Units::STBT_1, 0x14, 10);
                }
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                    param_1, 1000, 10000, Map::Units::STBT_0x411);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::assignBehaviorTypeAndLinkSupportTribe,
                    this)(param_1, iVar4, Map::Units::STBT_0x411, 0, 10);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                    param_1, 1000, 10000, Map::Units::STBT_7);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                    Map::Units::STBT_7, Map::Units::STBT_1, 0, 5);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                    param_1, 1000, 10000, Map::Units::STBT_0x416);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                    Map::Units::STBT_0x416, Map::Units::STBT_1, 0, 5);
            }
        }

    }
}
}
