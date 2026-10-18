#include "../TroopValueState.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AttackInfoDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

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
            int _tribeSizeSumLimit;
            int _playerID = (int)(char)DAT_TroopValueState::instance.attackInfo.attackWavePlayerIDArray[param_1];
            int _siegeArcherBudget = 0;
            int _siegeHackBudget = 0;
            if ((DAT_GameCore::instance.gameMode_2 == Game::GM_BUILDERUnk)
                && (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == Map::MT_SIEGE)) {
                _playerID = 2;
                _siegeArcherBudget = 5;
                _siegeHackBudget = -1;
            }
            DAT_TroopValueState::instance.attackInfo.attackWaveTicker[param_1]
                = DAT_TroopValueState::instance.attackInfo.attackWaveTicker[param_1] + 1;
            if (DAT_TroopValueState::instance.attackInfo.attackWaveTicker[param_1] < DAT_AttackInfoDefinedData::instance
                    .AIAttackWaveTargetDelay[DAT_TroopValueState::instance.attackInfo.attacker]) {
                return;
            }
            int _currentPlayerSlotID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            DAT_TroopValueState::instance.attackInfo.attackWaveTicker[param_1] = 0;
            DAT_TroopValueState::instance.attackInfo.value10 = DAT_TroopValueState::instance.attackInfo.value10 + 1;
            BOOLEnum _canReachSignpostZone = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::canKeepReachSignpostZone,
                DAT_GameState::ptr)(_currentPlayerSlotID, _playerID, param_1);
            if ((_canReachSignpostZone) && (DAT_TroopValueState::instance.attackInfo.attacker != 8)) {
                DAT_TroopValueState::instance.attackInfo.value3Array01[param_1] = 4;
                DAT_TroopValueState::instance.attackInfo.attackWaveTicker[param_1] = 10000;
                DAT_TroopValueState::instance.attackInfo.attackWaveSignpostShorts[param_1] = 0;
                return;
            }
            DAT_TroopValueState::instance.attackInfo.someCounter1
                = DAT_TroopValueState::instance.attackInfo.someCounter1 + 1;
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::aiRecomputeAttacks2, this)(0, param_1);
            int _playerInfoOffset = _playerID * 0x177bc;
            if (*(int*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + _playerInfoOffset + -0x18)
                < *(int*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + _playerInfoOffset + -0x1c)) {
                DAT_TroopValueState::instance.attackInfo.maxGateAttackTribes
                    = DAT_TroopValueState::instance.attackInfo.maxGateAttackTribes + 1;
            }
            if (DAT_TroopValueState::instance.attackInfo.attacker == 8) {
                if (10 <= DAT_TroopValueState::instance.attackInfo.someCounter1) {
                    DAT_TroopValueState::instance.attackInfo.attackWaveTicker[param_1] = 0;
                    DAT_TroopValueState::instance.attackInfo.value3Array01[param_1] = 6;
                    MACRO_CALL_MEMBER(
                        Audio::MSS::SoundSystem_Func::handleBattleEndMusicTransition, DAT_SoundSystemState::ptr)();
                    return;
                }
                _canReachSignpostZone = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::canKeepReachSignpostZone,
                    DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, _playerID, param_1);
                if (_canReachSignpostZone
                    && *(int*)((int)DAT_TroopValueState::instance.attackInfo.gateValuesArray + _playerInfoOffset + -4)
                        != 0) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                        param_1, 1000, 10000, Map::Units::STBT_0x3f6);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                        Map::Units::STBT_0x3f6, Map::Units::STBT_1, 0, 10);
                }
                _tribeSizeSumLimit
                    = *(int*)((int)DAT_TroopValueState::instance.attackInfo.townValuesArray + _playerInfoOffset + -4);
                if (_tribeSizeSumLimit) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                        param_1, 1000, _tribeSizeSumLimit, (SomeTribeBehaviorType)((int)(1013)));
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                        Map::Units::STBT_0x3f5, Map::Units::STBT_1, 0, 0x14);
                }
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(param_1,
                    1000,
                    *(int*)((int)DAT_TroopValueState::instance.attackInfo.hackValuesArray + _playerInfoOffset + -4),
                    Map::Units::STBT_0x3f2);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                    Map::Units::STBT_0x3f2, Map::Units::STBT_1, 0, 10);
            }
            DAT_TroopValueState::instance.attackInfo.reservedTroopBudget = 0;
            if (DAT_TroopValueState::instance.attackInfo.catapults) {
                DAT_TroopValueState::instance.attackInfo.reservedTroopBudget
                    = DAT_AttackInfoDefinedData::instance
                          .AIReservedTroopBudget[DAT_TroopValueState::instance.attackInfo.attacker];
                if (DAT_TroopValueState::instance.attackInfo.zoneSize < 3000) {
                    DAT_TroopValueState::instance.attackInfo.reservedTroopBudget
                        = DAT_TroopValueState::instance.attackInfo.reservedTroopBudget + 10;
                }
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                    param_1, 1, 10000, Map::Units::STBT_0x401);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                    Map::Units::STBT_0x401, Map::Units::STBT_1, 0, 0x32);
            }
            if ((DAT_TroopValueState::instance.attackInfo.lord2)
                && (2 < DAT_TroopValueState::instance.attackInfo.value10
                        - DAT_TroopValueState::instance.attackInfo.reservedTroopBudget)) {
                if (DAT_TroopValueState::instance.attackInfo.attacker == 4) {
                    DAT_TroopValueState::instance.attackInfo.maxLordAttackTribes
                        = DAT_TroopValueState::instance.attackInfo.maxLordAttackTribes * 2;
                }
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(param_1,
                    (int)(DAT_TroopValueState::instance.attackInfo.maxLordAttackTribes), 1000, Map::Units::STBT_0x3fd);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::assignBehaviorTypeToNearbyTribes, this)(
                    Map::Units::STBT_0x3fd, 1, 0, 1);
            }
            if (DAT_TroopValueState::instance.attackInfo.attacker == 3) {
                *(int*)((int)DAT_TroopValueState::instance.attackInfo.townValuesArray + _playerInfoOffset + -4)
                    = *(int*)((int)DAT_TroopValueState::instance.attackInfo.townValuesArray + _playerInfoOffset + -4)
                    * 2;
            }
            int _limit
                = *(int*)((int)DAT_TroopValueState::instance.attackInfo.townValuesArray + _playerInfoOffset + -4);
            if ((_limit)
                && (2 < DAT_TroopValueState::instance.attackInfo.value10
                        - DAT_TroopValueState::instance.attackInfo.reservedTroopBudget)) {
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(param_1,
                    (int)(DAT_TroopValueState::instance.attackInfo.maxTownAttackTribes), _limit,
                    Map::Units::STBT_0x3f5);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                    Map::Units::STBT_0x3f5, Map::Units::STBT_1, 0, 0x14);
            }
            _canReachSignpostZone
                = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::canKeepReachSignpostZoneViaPathfinder,
                    DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, _playerID, param_1);
            if (_canReachSignpostZone) {
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(param_1,
                    (int)(DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes), 10000, Map::Units::STBT_0x3fa);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                    Map::Units::STBT_7, Map::Units::STBT_1, 10, 0x14);
            }
            if (0 < *(int*)((int)DAT_TroopValueState::instance.attackInfo.moatValuesArray + _playerInfoOffset + -4)
                && 2 < DAT_TroopValueState::instance.attackInfo.value10
                        - DAT_TroopValueState::instance.attackInfo.reservedTroopBudget) {
                if (DAT_TroopValueState::instance.attackInfo.attacker == 4) {
                    DAT_TroopValueState::instance.attackInfo.maxMoatAttackTribes
                        = (int)DAT_TroopValueState::instance.attackInfo.maxMoatAttackTribes / 2;
                }
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(param_1,
                    (int)(DAT_TroopValueState::instance.attackInfo.maxMoatAttackTribes),
                    *(int*)((int)DAT_TroopValueState::instance.attackInfo.moatValuesArray + _playerInfoOffset + -4),
                    Map::Units::STBT_0x3f7);
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
            if (*(int*)((int)DAT_TroopValueState::instance.attackInfo.gateValuesArray + _playerInfoOffset + -4) != 0) {
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                    param_1, 2, 10000, Map::Units::STBT_0x41a);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                    Map::Units::STBT_0x41a, Map::Units::STBT_1, 10, 0x1e);
            }
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                param_1, 1000, 10000, Map::Units::STBT_0x41b);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                Map::Units::STBT_0x41b, Map::Units::STBT_1, 0x14, 0x14);
            if ((0 < DAT_TroopValueState::instance.attackInfo.archerPoints)
                && (DAT_TroopValueState::instance.attackInfo.value10
                        - DAT_TroopValueState::instance.attackInfo.reservedTroopBudget
                    > _siegeArcherBudget + 1)) {
                DAT_TroopValueState::instance.attackInfo.attackWaveRetargetCount
                    = DAT_TroopValueState::instance.attackInfo.attackWaveRetargetCount + 1;
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                    param_1, DAT_TroopValueState::instance.attackInfo.archerPoints, 10000, Map::Units::STBT_0x3fc);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                    Map::Units::STBT_0x3fc, Map::Units::STBT_1, 0, 5);
            }
            if (DAT_TroopValueState::instance.attackInfo.people3) {
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(param_1,
                    (int)(DAT_TroopValueState::instance.attackInfo.maxPeopleAttackTribes),
                    DAT_TroopValueState::instance.attackInfo.people3, Map::Units::STBT_0x3fb);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                    Map::Units::STBT_0x3fb, Map::Units::STBT_1, 5, 0x1e);
            }
            if (*(int*)((int)DAT_TroopValueState::instance.attackInfo.gateValuesArray + _playerInfoOffset + -4) != 0
                && 3 < DAT_TroopValueState::instance.attackInfo.value10
                        - DAT_TroopValueState::instance.attackInfo.reservedTroopBudget) {
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(param_1,
                    (int)(DAT_TroopValueState::instance.attackInfo.maxGateAttackTribes), 10000, Map::Units::STBT_0x3f6);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                    Map::Units::STBT_0x3f6, Map::Units::STBT_1, 0, 10);
            }
            _limit = *(int*)((int)DAT_TroopValueState::instance.attackInfo.wideValuesArray + _playerInfoOffset + -4);
            if ((_limit)
                && (3 < DAT_TroopValueState::instance.attackInfo.value10
                        - DAT_TroopValueState::instance.attackInfo.reservedTroopBudget)) {
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                    param_1, _limit, 10000, Map::Units::STBT_0x413);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                    Map::Units::STBT_0x413, Map::Units::STBT_1, 0, 0x28);
            }
            _limit = *(int*)((int)DAT_TroopValueState::instance.attackInfo.wideValuesArray + _playerInfoOffset + -4);
            if (_limit) {
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                    param_1, _limit, 10000, Map::Units::STBT_0x414);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                    Map::Units::STBT_0x414, Map::Units::STBT_1, 0, 0x28);
            }
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                param_1, 1000, 10000, Map::Units::STBT_0x411);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::assignBehaviorTypeAndLinkSupportTribe, this)(
                param_1, _playerID, Map::Units::STBT_0x411, 0, 0x14);
            if ((5 < DAT_TroopValueState::instance.attackInfo.aiTribeSizesPerTribeType.aiTroops_L)
                && (2 < DAT_TroopValueState::instance.attackInfo.value10
                        - DAT_TroopValueState::instance.attackInfo.reservedTroopBudget)) {
                _tribeSizeSumLimit
                    = *(int*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + _playerInfoOffset + -4);
                if (1 < _tribeSizeSumLimit) {
                    if (_tribeSizeSumLimit <= 2) {
                        _tribeSizeSumLimit = 1;
                    } else if (_tribeSizeSumLimit <= 6) {
                        _tribeSizeSumLimit = 2;
                    } else if (_tribeSizeSumLimit <= 0xc) {
                        _tribeSizeSumLimit = 3;
                    } else {
                        _tribeSizeSumLimit = 4;
                    }
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                        param_1, _tribeSizeSumLimit, 10000, Map::Units::STBT_0x3f4);
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
            if (_siegeHackBudget + 4 < DAT_TroopValueState::instance.attackInfo.value10
                    - DAT_TroopValueState::instance.attackInfo.reservedTroopBudget) {
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(param_1,
                    1000,
                    *(int*)((int)DAT_TroopValueState::instance.attackInfo.hackValuesArray + _playerInfoOffset + -4),
                    Map::Units::STBT_0x3f2);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                    Map::Units::STBT_0x3f2, ((SomeTribeBehaviorType)0), 0, 10);
            }
            _tribeSizeSumLimit
                = *(int*)((int)DAT_TroopValueState::instance.attackInfo.moatValuesArray + _playerInfoOffset + -4);
            if ((0 < _tribeSizeSumLimit)
                && (4 < DAT_TroopValueState::instance.attackInfo.value10
                        - DAT_TroopValueState::instance.attackInfo.reservedTroopBudget)) {
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                    param_1, 1000, _tribeSizeSumLimit, Map::Units::STBT_0x3f7);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                    Map::Units::STBT_0x3f7, Map::Units::STBT_1, 10, 5);
            }
            if (DAT_TroopValueState::instance.attackInfo.knights
                && *(int*)((int)DAT_TroopValueState::instance.attackInfo.gateValuesArray + _playerInfoOffset + -4) != 0
                && 3 < DAT_TroopValueState::instance.attackInfo.value10
                        - DAT_TroopValueState::instance.attackInfo.reservedTroopBudget) {
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                    param_1, 1000, 10000, Map::Units::STBT_0x417);
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
