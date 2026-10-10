#include "../../../Map.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Game::GameMode2;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00520F70
        void TroopValueState::aiControlNonSkirmishUnitMovement()
        {
            int* piVar1;
            BOOLEnum _canMove;
            int iVar2;
            BOOLEnum _hasTribe;
            int _index;
            int _pitchTile;
            byte _nTribes;
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::decrementTileMap1104, this)();
            if (((DAT_GameCore::instance.gameMode_2 != Game::GM_EDITOR)
                    && (DAT_GameCore::instance.gameMode_2 != Game::GM_SKIRMISH_AND_MULTIPLAYER))
                && (DAT_GameCore::instance.gameMode_2 != Game::GM_SIEGE_THAT)) {
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .keep.id
                    < 1) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::updateAttackInfoTick, this)();
                }
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::recountAttackTroopValue, this)(0);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::computeAttackWaveTroopComposition, this)();
                if (!DAT_TroopValueState::instance.attackInfo.aiTroops) {
                    DAT_TroopValueState::instance.attackInfo.attackVectorRecomputeThrottle = 0;
                }
                iVar2 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .aiControlStatusRelated;
                piVar1 = &DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .aiControlStatusRelated;
                if (iVar2 != -1000) {
                    if (!iVar2) {
                        iVar2 = 0;
                        do {
                            if ((DAT_TroopValueState::instance.attackInfo.nof_tribes[iVar2] != 0)
                                && (DAT_TroopValueState::instance.attackInfo.value3Array01[iVar2] != 6))
                                goto LAB_0052103d;
                            iVar2 = iVar2 + 1;
                        } while (iVar2 < 0x32);
                        *piVar1 = 600;
                    } else if (iVar2 < 1) {
                        if (iVar2 < 0) {
                            *piVar1 = iVar2 + 1;
                        }
                    } else {
                        *piVar1 = iVar2 + -1;
                        if (iVar2 + -1 == 0) {
                            *piVar1 = -1000;
                        }
                    }
                }
            LAB_0052103d:
                DAT_TroopValueState::instance.attackInfo.value3Array01[0] = 0;
                DAT_TroopValueState::instance.attackInfo.attackWaveTicker[0] = 0;
                for (_index = 1; _index < 50; _index++) {
                    DAT_TroopValueState::instance.attackInfo.attacker
                        = (int)(char)DAT_TroopValueState::instance.attackInfo.attackWavePlayerIDArray[_index];
                    if ((DAT_TroopValueState::instance.attackInfo.attacker != 1)
                        && ((0 < DAT_TroopValueState::instance.attackInfo.attacker
                            || (_hasTribe = MACRO_CALL_MEMBER(
                                    Map::Units::TroopValueState_Func::searchTribeWithProperties, this)(_index),
                                _hasTribe)))) {
                        _nTribes = DAT_TroopValueState::instance.attackInfo.nof_tribes[_index];
                        DAT_GameState::instance.playerDataArray[DAT_TroopValueState::instance.attackInfo.attacker]
                            .attackedPlayerID = 1;
                        if (!_nTribes) {
                            DAT_TroopValueState::instance.attackInfo.value3Array01[_index] = 0;
                        } else {
                            iVar2 = DAT_TroopValueState::instance.attackInfo.someIntArray2[_index + -1] + 1;
                            DAT_TroopValueState::instance.attackInfo.index = _index;
                            DAT_TroopValueState::instance.attackInfo.someIntArray2[_index + -1] = iVar2;
                            if (((DAT_TroopValueState::instance.attackInfo.lowTroopValueRelated) && (10 < iVar2))
                                && (DAT_TroopValueState::instance.attackInfo.value3Array01[_index] != 6)) {
                                DAT_TroopValueState::instance.attackInfo.attackWaveTicker[_index] = 0;
                                DAT_TroopValueState::instance.attackInfo.value3Array01[_index] = 6;
                                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::handleBattleEndMusicTransition,
                                    DAT_SoundSystemState::ptr)();
                            }
                            iVar2 = DAT_TroopValueState::instance.attackInfo.value3Array01[_index];
                            if (!iVar2) {
                                MACRO_CALL_MEMBER(
                                    Map::Units::TroopValueState_Func::initializeOrAdvanceAttackWave, this)(
                                    _index);
                            } else if (iVar2 == 1) {
                                MACRO_CALL_MEMBER(
                                    Map::Units::TroopValueState_Func::advanceAttackWaveStaging, this)(_index);
                            } else if (iVar2 == 2) {
                                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::updateInProgressAttackWave,
                                    this)(_index);
                            } else if (iVar2 == 3) {
                                MACRO_CALL_MEMBER(
                                    Map::Units::TroopValueState_Func::executeAttackWaveTargetAssignment, this)(
                                    _index);
                            } else if (iVar2 == 4) {
                                MACRO_CALL_MEMBER(
                                    Map::Units::TroopValueState_Func::executeDelayedAttackWaveTargetAssignment,
                                    this)(_index);
                            } else if ((iVar2 != 5) && (iVar2 == 6)) {
                                MACRO_CALL_MEMBER(
                                    Map::Units::TroopValueState_Func::updateActiveAttackWaveState, this)(
                                    _index);
                            }
                        }
                        DAT_TroopValueState::instance.attackInfo.nof_tribes[_index] = 0;
                        DAT_TroopValueState::instance.attackInfo.unknownByteArray02[_index] = 0;
                    }
                }
                DAT_TroopValueState::instance.attackInfo.field86986_0x20f98 = 0;
            }
        }

    }
}
}
