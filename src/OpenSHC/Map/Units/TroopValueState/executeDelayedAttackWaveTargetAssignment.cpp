#include "OpenSHC/Map.func.hpp"

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
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

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
            int _signpostIndex;
            int tribeSizeSumLimit;
            BOOLEnum _canReachSignpostZone;
            int _playerID;
            _playerID = (int)(char)DAT_TroopValueState::instance.attackInfo.attackWavePlayerIDArray[param_1];
            if ((DAT_GameCore::instance.gameMode_2 == Game::GM_BUILDERUnk)
                && (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == Map::MT_SIEGE)) {
                _playerID = 2;
            }
            DAT_TroopValueState::instance.attackInfo.delayedWaveAssignmentCount
                = DAT_TroopValueState::instance.attackInfo.delayedWaveAssignmentCount + 1;
            _canReachSignpostZone = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::canKeepReachSignpostZone,
                DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, _playerID, param_1);
            if (!_canReachSignpostZone) {
                DAT_TroopValueState::instance.attackInfo.value3Array01[param_1] = 3;
                DAT_TroopValueState::instance.attackInfo.attackWaveTicker[param_1] = 0;
                return;
            }
            DAT_TroopValueState::instance.attackInfo.attackWaveTicker[param_1]
                = DAT_TroopValueState::instance.attackInfo.attackWaveTicker[param_1] + 1;
            if (400 <= DAT_TroopValueState::instance.attackInfo.attackWaveTicker[param_1]) {
                DAT_TroopValueState::instance.attackInfo.attackWaveTicker[param_1] = 0;
                DAT_TroopValueState::instance.attackInfo.someCounter1
                    = DAT_TroopValueState::instance.attackInfo.someCounter1 + 1;
                _signpostIndex = DAT_TroopValueState::instance.attackInfo.attackWaveSignpostShorts[param_1];
                DAT_TroopValueState::instance.attackInfo.attackWaveSignpostShorts[param_1]
                    = (short)(_signpostIndex + 1);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::aiRecomputeAttacks, this)(
                    (int)_signpostIndex, param_1);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                    param_1, 1000, 10000, Map::Units::STBT_0x41b);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                    Map::Units::STBT_0x41b, Map::Units::STBT_1, 0x32, 0x32);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                    param_1, 1000, 10000, Map::Units::STBT_0x418);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                    Map::Units::STBT_0x418, Map::Units::STBT_1, 0x14, 0x46);
                if ((DAT_TroopValueState::instance.attackInfo.people3)
                    && (0xa <= DAT_TroopValueState::instance.attackInfo.attackTribeCount)) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                        param_1, 1, DAT_TroopValueState::instance.attackInfo.people3, Map::Units::STBT_0x3fb);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                        Map::Units::STBT_0x3fb, Map::Units::STBT_1, 5, 0xf);
                }
                if (DAT_TroopValueState::instance.attackInfo.lord2) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                        param_1, (int)(DAT_TroopValueState::instance.attackInfo.maxLordAttackTribes), 1000,
                        Map::Units::STBT_0x3fd);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::assignBehaviorTypeToNearbyTribes, this)(
                        Map::Units::STBT_0x3fd, 1, 0, 5);
                }
                if (DAT_TroopValueState::instance.attackInfo.high3) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                        param_1, DAT_TroopValueState::instance.attackInfo.high3, 10000, Map::Units::STBT_0x3f8);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                        Map::Units::STBT_0x3f8, Map::Units::STBT_1, 0x14, 10);
                }
                if (DAT_TroopValueState::instance.attackInfo.arch3) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                        param_1, DAT_TroopValueState::instance.attackInfo.arch3, 10000, Map::Units::STBT_0x3f9);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                        Map::Units::STBT_0x3f9, Map::Units::STBT_1, 0x14, 10);
                }
                if (DAT_TroopValueState::instance.attackInfo.people3) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                        param_1, 2, DAT_TroopValueState::instance.attackInfo.people3, Map::Units::STBT_0x3fb);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                        Map::Units::STBT_0x3fb, Map::Units::STBT_1, 0, 10);
                }
                tribeSizeSumLimit = DAT_TroopValueState::instance.attackInfo.playerInfo[_playerID - 1].town3;
                if (tribeSizeSumLimit) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                        param_1, 1, tribeSizeSumLimit, Map::Units::STBT_0x3f5);
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::applyTribeBehaviorTypes, this)(
                        Map::Units::STBT_0x3f5, Map::Units::STBT_1, 0x14, 10);
                }
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sortAttackInfoTribeIDArrayBasedOn, this)(
                    param_1, 1000, 10000, Map::Units::STBT_0x411);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::assignBehaviorTypeAndLinkSupportTribe, this)(
                    param_1, _playerID, Map::Units::STBT_0x411, 0, 10);
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
