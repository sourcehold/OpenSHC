#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Audio/mss/SoundSystem.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00520F70
        void TroopValueState::aiControlNonSkirmishUnitMovement()
        {
            MACRO_CALL_MEMBER(TroopValueState_Func::decrementTileMap1104, this)();
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER
                || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                return;
            }
            if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].keep.id
                <= 0) {
                MACRO_CALL_MEMBER(TroopValueState_Func::updateAttackInfoTick, this)();
                return;
            }
            MACRO_CALL_MEMBER(TroopValueState_Func::recountAttackTroopValue, this)(0);
            MACRO_CALL_MEMBER(TroopValueState_Func::computeAttackWaveTroopComposition, this)();
            if (DAT_TroopValueState::instance.attackInfo.aiTroops == 0) {
                DAT_TroopValueState::instance.attackInfo.attackVectorRecomputeThrottle = 0;
            }
            int const status = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                   .aiControlStatusRelated;
            if (status != -1000) {
                if (status == 0) {
                    BOOLEnum waveComplete = TRUE;
                    for (int wave = 0; wave < 50; ++wave) {
                        if (DAT_TroopValueState::instance.attackInfo.nof_tribes[wave] != 0
                            && DAT_TroopValueState::instance.attackInfo.value3Array01[wave] != 6) {
                            waveComplete = FALSE;
                            break;
                        }
                    }
                    if (waveComplete != FALSE) {
                        DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].aiControlStatusRelated = 600;
                    }
                } else if (status > 0) {
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].aiControlStatusRelated = status - 1;
                    if (status - 1 == 0) {
                        DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].aiControlStatusRelated = -1000;
                    }
                } else if (status < 0) {
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].aiControlStatusRelated = status + 1;
                }
            }
            DAT_TroopValueState::instance.attackInfo.value3Array01[0] = 0;
            DAT_TroopValueState::instance.attackInfo.attackWaveTicker[0] = 0;
            for (int wave = 1; wave < 50; ++wave) {
                DAT_TroopValueState::instance.attackInfo.attacker
                    = (char)DAT_TroopValueState::instance.attackInfo.attackWavePlayerIDArray[wave];
                if (DAT_TroopValueState::instance.attackInfo.attacker == 1) {
                    continue;
                }
                if (DAT_TroopValueState::instance.attackInfo.attacker <= 0
                    && MACRO_CALL_MEMBER(TroopValueState_Func::searchTribeWithProperties, this)(wave) == FALSE) {
                    continue;
                }
                DAT_GameState::instance.playerDataArray[DAT_TroopValueState::instance.attackInfo.attacker].attackedPlayerID
                    = 1;
                if (DAT_TroopValueState::instance.attackInfo.nof_tribes[wave] != 0) {
                    DAT_TroopValueState::instance.attackInfo.index = wave;
                    int const waveAge = ++DAT_TroopValueState::instance.attackInfo.someIntArray2[wave - 1];
                    if (DAT_TroopValueState::instance.attackInfo.lowTroopValueRelated != 0 && waveAge > 10
                        && DAT_TroopValueState::instance.attackInfo.value3Array01[wave] != 6) {
                        DAT_TroopValueState::instance.attackInfo.attackWaveTicker[wave] = 0;
                        DAT_TroopValueState::instance.attackInfo.value3Array01[wave] = 6;
                        MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::handleBattleEndMusicTransition,
                            DAT_SoundSystemState::ptr)();
                    }
                    int const waveState = DAT_TroopValueState::instance.attackInfo.value3Array01[wave];
                    if (waveState == 0) {
                        MACRO_CALL_MEMBER(TroopValueState_Func::initializeOrAdvanceAttackWave, this)(wave);
                    } else if (waveState == 1) {
                        MACRO_CALL_MEMBER(TroopValueState_Func::advanceAttackWaveStaging, this)(wave);
                    } else if (waveState == 2) {
                        MACRO_CALL_MEMBER(TroopValueState_Func::updateInProgressAttackWave, this)(wave);
                    } else if (waveState == 3) {
                        MACRO_CALL_MEMBER(TroopValueState_Func::executeAttackWaveTargetAssignment, this)(wave);
                    } else if (waveState == 4) {
                        MACRO_CALL_MEMBER(TroopValueState_Func::executeDelayedAttackWaveTargetAssignment, this)(wave);
                    } else if (waveState == 5) {
                    } else if (waveState == 6) {
                        MACRO_CALL_MEMBER(TroopValueState_Func::updateActiveAttackWaveState, this)(wave);
                    }
                } else {
                    DAT_TroopValueState::instance.attackInfo.value3Array01[wave] = 0;
                }
                DAT_TroopValueState::instance.attackInfo.nof_tribes[wave] = 0;
                DAT_TroopValueState::instance.attackInfo.unknownByteArray02[wave] = 0;
            }
            DAT_TroopValueState::instance.attackInfo.attackWaveSweepActive = 0;
        }

    }
}
}
