#include "../TroopValueState.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Map.func.hpp"
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
            BOOLEnum _hasTribe;
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::decrementTileMap1104, this)();
            if (DAT_GameCore::instance.gameMode_2 != Game::GM_EDITOR
                && DAT_GameCore::instance.gameMode_2 != Game::GM_SKIRMISH_AND_MULTIPLAYER
                && DAT_GameCore::instance.gameMode_2 != Game::GM_SIEGE_THAT) {
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .keep.id
                    <= 0) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::updateAttackInfoTick, this)();
                    return;
                }
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::recountAttackTroopValue, this)(0);
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::computeAttackWaveTroopComposition, this)();
                if (!DAT_TroopValueState::instance.attackInfo.aiTroops) {
                    DAT_TroopValueState::instance.attackInfo.attackVectorRecomputeThrottle = 0;
                }
                int _aiControlStatus
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .aiControlStatusRelated;
                if (_aiControlStatus != -1000) {
                    if (!_aiControlStatus) {
                        BOOLEnum anyWaveStillRunning = FALSE;
                        for (int _waveIndex = 0; _waveIndex < 0x32; _waveIndex = _waveIndex + 1) {
                            if ((DAT_TroopValueState::instance.attackInfo.nof_tribes[_waveIndex] != 0)
                                && (DAT_TroopValueState::instance.attackInfo.value3Array01[_waveIndex] != 6)) {
                                anyWaveStillRunning = TRUE;
                                break;
                            }
                        }
                        if (!anyWaveStillRunning) {
                            DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .aiControlStatusRelated = 600;
                        }
                    } else if (0 < _aiControlStatus) {
                        DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .aiControlStatusRelated = _aiControlStatus + -1;
                        if (_aiControlStatus + -1 == 0) {
                            DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .aiControlStatusRelated = -1000;
                        }
                    } else if (_aiControlStatus < 0) {
                        DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .aiControlStatusRelated = _aiControlStatus + 1;
                    }
                }
                DAT_TroopValueState::instance.attackInfo.value3Array01[0] = 0;
                DAT_TroopValueState::instance.attackInfo.attackWaveTicker[0] = 0;
                for (int _index = 1; _index < 50; _index++) {
                    DAT_TroopValueState::instance.attackInfo.attacker
                        = (int)(char)DAT_TroopValueState::instance.attackInfo.attackWavePlayerIDArray[_index];
                    if (DAT_TroopValueState::instance.attackInfo.attacker != 1
                        && (0 < DAT_TroopValueState::instance.attackInfo.attacker
                            || (_hasTribe = MACRO_CALL_MEMBER(
                                    Map::Units::TroopValueState_Func::searchTribeWithProperties, this)(_index),
                                _hasTribe))) {
                        int _nTribes = DAT_TroopValueState::instance.attackInfo.nof_tribes[_index];
                        DAT_GameState::instance.playerDataArray[DAT_TroopValueState::instance.attackInfo.attacker]
                            .attackedPlayerID = 1;
                        if (_nTribes) {
                            int _waveCounter = DAT_TroopValueState::instance.attackInfo.someIntArray2[_index + -1] + 1;
                            DAT_TroopValueState::instance.attackInfo.index = _index;
                            DAT_TroopValueState::instance.attackInfo.someIntArray2[_index + -1] = _waveCounter;
                            if (DAT_TroopValueState::instance.attackInfo.lowTroopValueRelated && 10 < _waveCounter
                                && DAT_TroopValueState::instance.attackInfo.value3Array01[_index] != 6) {
                                DAT_TroopValueState::instance.attackInfo.attackWaveTicker[_index] = 0;
                                DAT_TroopValueState::instance.attackInfo.value3Array01[_index] = 6;
                                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::handleBattleEndMusicTransition,
                                    DAT_SoundSystemState::ptr)();
                            }
                            int _wavePhase = DAT_TroopValueState::instance.attackInfo.value3Array01[_index];
                            if (!_wavePhase) {
                                MACRO_CALL_MEMBER(
                                    Map::Units::TroopValueState_Func::initializeOrAdvanceAttackWave, this)(_index);
                            } else if (_wavePhase == 1) {
                                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::advanceAttackWaveStaging, this)(
                                    _index);
                            } else if (_wavePhase == 2) {
                                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::updateInProgressAttackWave, this)(
                                    _index);
                            } else if (_wavePhase == 3) {
                                MACRO_CALL_MEMBER(
                                    Map::Units::TroopValueState_Func::executeAttackWaveTargetAssignment, this)(_index);
                            } else if (_wavePhase == 4) {
                                MACRO_CALL_MEMBER(
                                    Map::Units::TroopValueState_Func::executeDelayedAttackWaveTargetAssignment, this)(
                                    _index);
                            } else if ((_wavePhase != 5) && (_wavePhase == 6)) {
                                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::updateActiveAttackWaveState, this)(
                                    _index);
                            }
                        } else {
                            DAT_TroopValueState::instance.attackInfo.value3Array01[_index] = 0;
                        }
                        DAT_TroopValueState::instance.attackInfo.nof_tribes[_index] = 0;
                        DAT_TroopValueState::instance.attackInfo.unknownByteArray02[_index] = 0;
                    }
                }
                DAT_TroopValueState::instance.attackInfo.attackWaveSweepActive = 0;
            }
        }

    }
}
}
