#include "../../../Map.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_AttackInfoDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Game::GameMode2;
        using Map::MapType2;
        using Map::Units::SomeTribeBehaviorType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x005205A0
        void TroopValueState::executeAttackWaveTargetAssignment(int param_1)
        {
            int* piVar1;
            int iVar2;
            BOOLEnum BVar3;
            int iVar4;
            int iVar5;
            int local_8;
            int local_4;
            iVar5 = (int)(char)DAT_TroopValueState::instance.attackInfo.attackWavePlayerIDArray[param_1];
            local_8 = 0;
            local_4 = 0;
            if ((DAT_GameCore::instance.gameMode_2 == Game::GM_BUILDERUnk)
                && (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == Map::MT_SIEGE)) {
                iVar5 = 2;
                local_8 = 5;
                local_4 = -1;
            }
            piVar1 = DAT_TroopValueState::instance.attackInfo.attackWaveTicker + param_1;
            *piVar1 = *piVar1 + 1;
            iVar4 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            if (DAT_AttackInfoDefinedData::instance.AIAttackWaveTargetDelay[DAT_TroopValueState::instance.attackInfo.attacker]
                <= DAT_TroopValueState::instance.attackInfo.attackWaveTicker[param_1]) {
                DAT_TroopValueState::instance.attackInfo.attackWaveTicker[param_1] = 0;
                DAT_TroopValueState::instance.attackInfo.value10 = DAT_TroopValueState::instance.attackInfo.value10 + 1;
                BVar3 = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::canKeepReachSignpostZone,
                    DAT_GameState::ptr)(iVar4, iVar5, param_1);
                if ((BVar3) && (DAT_TroopValueState::instance.attackInfo.attacker != 8)) {
                    DAT_TroopValueState::instance.attackInfo.value3Array01[param_1] = 4;
                    DAT_TroopValueState::instance.attackInfo.attackWaveTicker[param_1] = 10000;
                    DAT_TroopValueState::instance.attackInfo.attackWaveAssignmentAttempts[param_1] = 0;
                }
                DAT_TroopValueState::instance.attackInfo.someCounter1 = DAT_TroopValueState::instance.attackInfo.someCounter1 + 1;
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::aiRecomputeAttacks2, this)(0, param_1);
                iVar4 = iVar5 * 0x177bc;
                if (*(int*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + iVar4 + -0x18)
                    < *(int*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + iVar4 + -0x1c)) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20f58 = DAT_TroopValueState::instance.attackInfo.field_0x20f58 + 1;
                }
                if (DAT_TroopValueState::instance.attackInfo.attacker == 8) {
                    if (9 < DAT_TroopValueState::instance.attackInfo.someCounter1) {
                        DAT_TroopValueState::instance.attackInfo.attackWaveTicker[param_1] = 0;
                        DAT_TroopValueState::instance.attackInfo.value3Array01[param_1] = 6;
                        MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::handleBattleEndMusicTransition,
                            DAT_SoundSystemState::ptr)();
                    }
                    BVar3 = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::canKeepReachSignpostZone,
                        DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, iVar5, param_1);
                    if ((BVar3)
                        && (*(int*)((int)DAT_TroopValueState::instance.attackInfo.gateValuesArray + iVar4 + -4) != 0)) {
                        MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn,
                            this)(param_1, 1000, 10000, Map::Units::STBT_0x3f6);
                        MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                            Map::Units::STBT_0x3f6, Map::Units::STBT_1, 0, 10);
                    }
                    iVar5 = *(int*)((int)DAT_TroopValueState::instance.attackInfo.townValuesArray + iVar4 + -4);
                    if (iVar5) {
                        MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn,
                            this)(param_1, 1000, iVar5, (SomeTribeBehaviorType)((int)(1013)));
                        MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                            Map::Units::STBT_0x3f5, Map::Units::STBT_1, 0, 0x14);
                    }
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn,
                        this)(param_1, 1000, *(int*)((int)DAT_TroopValueState::instance.attackInfo.hackValuesArray + iVar4 + -4),
                        Map::Units::STBT_0x3f2);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                        Map::Units::STBT_0x3f2, Map::Units::STBT_1, 0, 10);
                }
                DAT_TroopValueState::instance.attackInfo.reservedTroopBudget = 0;
                if (DAT_TroopValueState::instance.attackInfo.catapults) {
                    DAT_TroopValueState::instance.attackInfo.reservedTroopBudget
                        = DAT_AttackInfoDefinedData::instance.AIReservedTroopBudget[DAT_TroopValueState::instance.attackInfo.attacker];
                    if (DAT_TroopValueState::instance.attackInfo.zoneSize < 3000) {
                        DAT_TroopValueState::instance.attackInfo.reservedTroopBudget = DAT_TroopValueState::instance.attackInfo.reservedTroopBudget + 10;
                    }
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn,
                        this)(param_1, 1, 10000, Map::Units::STBT_0x401);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                        Map::Units::STBT_0x401, Map::Units::STBT_1, 0, 0x32);
                }
                if ((DAT_TroopValueState::instance.attackInfo.lord2)
                    && (2 < DAT_TroopValueState::instance.attackInfo.value10
                            - DAT_TroopValueState::instance.attackInfo.reservedTroopBudget)) {
                    if (DAT_TroopValueState::instance.attackInfo.attacker == 4) {
                        DAT_TroopValueState::instance.attackInfo.field_0x20f3c = DAT_TroopValueState::instance.attackInfo.field_0x20f3c * 2;
                    }
                    MACRO_CALL_MEMBER(
                        Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                        param_1, (int)((int)(DAT_TroopValueState::instance.attackInfo.field_0x20f3c)), 1000, Map::Units::STBT_0x3fd);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::assignBehaviorTypeToNearbyTribes,
                        this)(Map::Units::STBT_0x3fd, 1, 0, 1);
                }
                if (DAT_TroopValueState::instance.attackInfo.attacker == 3) {
                    *(int*)((int)DAT_TroopValueState::instance.attackInfo.townValuesArray + iVar4 + -4)
                        = *(int*)((int)DAT_TroopValueState::instance.attackInfo.townValuesArray + iVar4 + -4) * 2;
                }
                iVar2 = *(int*)((int)DAT_TroopValueState::instance.attackInfo.townValuesArray + iVar4 + -4);
                if ((iVar2)
                    && (2 < DAT_TroopValueState::instance.attackInfo.value10
                            - DAT_TroopValueState::instance.attackInfo.reservedTroopBudget)) {
                    MACRO_CALL_MEMBER(
                        Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                        param_1, (int)((int)(DAT_TroopValueState::instance.attackInfo.field_0x20f48)), iVar2, Map::Units::STBT_0x3f5);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                        Map::Units::STBT_0x3f5, Map::Units::STBT_1, 0, 0x14);
                }
                BVar3
                    = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::canKeepReachSignpostZoneViaPathfinder,
                        DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, iVar5, param_1);
                if (BVar3) {
                    MACRO_CALL_MEMBER(
                        Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                        param_1, (int)((int)(DAT_TroopValueState::instance.attackInfo.field_0x20f44)), 10000, Map::Units::STBT_0x3fa);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                        Map::Units::STBT_7, Map::Units::STBT_1, 10, 0x14);
                }
                if ((0 < *(int*)((int)DAT_TroopValueState::instance.attackInfo.moatValuesArray + iVar4 + -4))
                    && (2 < DAT_TroopValueState::instance.attackInfo.value10 - DAT_TroopValueState::instance.attackInfo.reservedTroopBudget)) {
                    if (DAT_TroopValueState::instance.attackInfo.attacker == 4) {
                        DAT_TroopValueState::instance.attackInfo.field_0x20f4c = (int)DAT_TroopValueState::instance.attackInfo.field_0x20f4c / 2;
                    }
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn,
                        this)(param_1, (int)((int)(DAT_TroopValueState::instance.attackInfo.field_0x20f4c)),
                        *(int*)((int)DAT_TroopValueState::instance.attackInfo.moatValuesArray + iVar4 + -4), Map::Units::STBT_0x3f7);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                        Map::Units::STBT_0x3f7, Map::Units::STBT_1, 10, 10);
                    DAT_TroopValueState::instance.attackInfo.tribesToSortCount
                        = DAT_TroopValueState::instance.attackInfo.unknownTribeCounterRelated;
                }
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                    param_1, 1000, 10000, Map::Units::STBT_0x418);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                    Map::Units::STBT_0x418, Map::Units::STBT_1, 0x14, 0x46);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                    param_1, 1000, 10000, Map::Units::STBT_0x419);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                    Map::Units::STBT_0x419, Map::Units::STBT_1, 0x14, 0x46);
                if (*(int*)((int)DAT_TroopValueState::instance.attackInfo.gateValuesArray + iVar4 + -4) != 0) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn,
                        this)(param_1, 2, 10000, Map::Units::STBT_0x41a);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                        Map::Units::STBT_0x41a, Map::Units::STBT_1, 10, 0x1e);
                }
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                    param_1, 1000, 10000, Map::Units::STBT_0x41b);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                    Map::Units::STBT_0x41b, Map::Units::STBT_1, 0x14, 0x14);
                if ((0 < DAT_TroopValueState::instance.attackInfo.archerPoints)
                    && (local_8 + 1 < DAT_TroopValueState::instance.attackInfo.value10 - DAT_TroopValueState::instance.attackInfo.reservedTroopBudget)) {
                    DAT_TroopValueState::instance.attackInfo.attackWaveRetargetCount = DAT_TroopValueState::instance.attackInfo.attackWaveRetargetCount + 1;
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn,
                        this)(param_1, DAT_TroopValueState::instance.attackInfo.archerPoints, 10000, Map::Units::STBT_0x3fc);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                        Map::Units::STBT_0x3fc, Map::Units::STBT_1, 0, 5);
                }
                if (DAT_TroopValueState::instance.attackInfo.people3) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn,
                        this)(param_1, (int)((int)(DAT_TroopValueState::instance.attackInfo.field_0x20f54)), DAT_TroopValueState::instance.attackInfo.people3,
                        Map::Units::STBT_0x3fb);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                        Map::Units::STBT_0x3fb, Map::Units::STBT_1, 5, 0x1e);
                }
                if ((*(int*)((int)DAT_TroopValueState::instance.attackInfo.gateValuesArray + iVar4 + -4) != 0)
                    && (3 < DAT_TroopValueState::instance.attackInfo.value10 - DAT_TroopValueState::instance.attackInfo.reservedTroopBudget)) {
                    MACRO_CALL_MEMBER(
                        Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                        param_1, (int)((int)(DAT_TroopValueState::instance.attackInfo.field_0x20f58)), 10000, Map::Units::STBT_0x3f6);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                        Map::Units::STBT_0x3f6, Map::Units::STBT_1, 0, 10);
                }
                iVar2 = *(int*)((int)DAT_TroopValueState::instance.attackInfo.wideValuesArray + iVar4 + -4);
                if ((iVar2)
                    && (3 < DAT_TroopValueState::instance.attackInfo.value10
                            - DAT_TroopValueState::instance.attackInfo.reservedTroopBudget)) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn,
                        this)(param_1, iVar2, 10000, Map::Units::STBT_0x413);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                        Map::Units::STBT_0x413, Map::Units::STBT_1, 0, 0x28);
                }
                iVar2 = *(int*)((int)DAT_TroopValueState::instance.attackInfo.wideValuesArray + iVar4 + -4);
                if (iVar2) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn,
                        this)(param_1, iVar2, 10000, Map::Units::STBT_0x414);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                        Map::Units::STBT_0x414, Map::Units::STBT_1, 0, 0x28);
                }
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                    param_1, 1000, 10000, Map::Units::STBT_0x411);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::assignBehaviorTypeAndLinkSupportTribe,
                    this)(param_1, iVar5, Map::Units::STBT_0x411, 0, 0x14);
                if ((5 < DAT_TroopValueState::instance.attackInfo.aiTribeSizesPerTribeType.aiTroops_L)
                    && (2 < DAT_TroopValueState::instance.attackInfo.value10 - DAT_TroopValueState::instance.attackInfo.reservedTroopBudget)) {
                    iVar5 = *(int*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + iVar4 + -4);
                    if (1 < iVar5) {
                        if (iVar5 < 3) {
                            iVar5 = 1;
                        } else if (iVar5 < 7) {
                            iVar5 = 2;
                        } else if (iVar5 < 0xd) {
                            iVar5 = 3;
                        } else {
                            iVar5 = 4;
                        }
                        MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn,
                            this)(param_1, iVar5, 10000, Map::Units::STBT_0x3f4);
                        MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                            Map::Units::STBT_0x3f4, Map::Units::STBT_5, 0, 0x19);
                    }
                    if (DAT_TroopValueState::instance.attackInfo.tribesToSortCount) {
                        MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                            param_1, DAT_TroopValueState::instance.attackInfo.tribesToSortCount, 10000,
                            Map::Units::STBT_0x3f4);
                        MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                            Map::Units::STBT_0x3fc, Map::Units::STBT_1, 0, 0x14);
                    }
                }
                if (local_4 + 4 < DAT_TroopValueState::instance.attackInfo.value10 - DAT_TroopValueState::instance.attackInfo.reservedTroopBudget) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn,
                        this)(param_1, 1000, *(int*)((int)DAT_TroopValueState::instance.attackInfo.hackValuesArray + iVar4 + -4),
                        Map::Units::STBT_0x3f2);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                        Map::Units::STBT_0x3f2, ((SomeTribeBehaviorType)0), 0, 10);
                }
                iVar5 = *(int*)((int)DAT_TroopValueState::instance.attackInfo.moatValuesArray + iVar4 + -4);
                if ((0 < iVar5) && (4 < DAT_TroopValueState::instance.attackInfo.value10 - DAT_TroopValueState::instance.attackInfo.reservedTroopBudget)) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn,
                        this)(param_1, 1000, iVar5, Map::Units::STBT_0x3f7);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                        Map::Units::STBT_0x3f7, Map::Units::STBT_1, 10, 5);
                }
                if (((DAT_TroopValueState::instance.attackInfo.knights)
                        && (*(int*)((int)DAT_TroopValueState::instance.attackInfo.gateValuesArray + iVar4 + -4) != 0))
                    && (3 < DAT_TroopValueState::instance.attackInfo.value10
                            - DAT_TroopValueState::instance.attackInfo.reservedTroopBudget)) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn,
                        this)(param_1, 1000, 10000, Map::Units::STBT_0x417);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                        Map::Units::STBT_0x3f6, Map::Units::STBT_1, 0, 10);
                }
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                    param_1, 1000, 10000, Map::Units::STBT_0x41e);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                    Map::Units::STBT_0x41e, Map::Units::STBT_1, 10, 0x28);
            }
        }

    }
}
}
