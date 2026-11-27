#include "../TroopValueState.func.hpp"

#include "OpenSHC/Audio/mss/SoundSystem.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/Map/Enums/AttackWaveStateInt.hpp"

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
            if (DAT_GameCore::instance.gameMode_2 == Game::GM_EDITOR
                || DAT_GameCore::instance.gameMode_2 == Game::GM_SKIRMISH_AND_MULTIPLAYER
                || DAT_GameCore::instance.gameMode_2 == Game::GM_SIEGE_THAT) {
                return;
            }
            if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .buildingEntryInfos[Game::Player::Enums::BEIE_KEEP]
                    .id
                <= 0) {
                MACRO_CALL_MEMBER(TroopValueState_Func::updateAttackInfoTick, this)();
                return;
            }
            MACRO_CALL_MEMBER(TroopValueState_Func::recountAttackTroopValue, this)(FALSE);
            MACRO_CALL_MEMBER(TroopValueState_Func::computeAttackWaveTroopComposition, this)();
            if (DAT_TroopValueState::instance.attackInfo.aiTroops == 0) {
                DAT_TroopValueState::instance.attackInfo.attackVectorRecomputeThrottle = 0;
            }
            int const status
                = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .aiControlStatusRelated;
            if (status != -1000) {
                if (status == 0) {
                    BOOLEnum waveComplete = TRUE;
                    for (int wave = 0; wave < countof(DAT_TroopValueState::instance.attackInfo.nof_tribes); ++wave) {
                        if (DAT_TroopValueState::instance.attackInfo.nof_tribes[wave] != 0
                            && DAT_TroopValueState::instance.attackInfo.value3Array01[wave] != Map::Enums::AWS_ENDED) {
                            waveComplete = FALSE;
                            break;
                        }
                    }
                    if (waveComplete) {
                        DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .aiControlStatusRelated = 600;
                    }
                } else if (status > 0) {
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .aiControlStatusRelated = status - 1;
                    if (status - 1 == 0) {
                        DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .aiControlStatusRelated = -1000;
                    }
                } else if (status < 0) {
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .aiControlStatusRelated = status + 1;
                }
            }
            DAT_TroopValueState::instance.attackInfo.value3Array01[0] = Map::Enums::AWS_GATHERING;
            DAT_TroopValueState::instance.attackInfo.attackWaveTicker[0] = 0;
            for (int wave = 1; wave < countof(DAT_TroopValueState::instance.attackInfo.nof_tribes); ++wave) {
                DAT_TroopValueState::instance.attackInfo.attacker
                    = DAT_TroopValueState::instance.attackInfo.attackWavePlayerIDArray[wave];
                if (DAT_TroopValueState::instance.attackInfo.attacker == 1) {
                    continue;
                }
                if (DAT_TroopValueState::instance.attackInfo.attacker <= 0
                    && !MACRO_CALL_MEMBER(TroopValueState_Func::searchTribeWithProperties, this)(wave)) {
                    continue;
                }
                DAT_GameState::instance.playerDataArray[DAT_TroopValueState::instance.attackInfo.attacker]
                    .attackedPlayerID = 1;
                if (DAT_TroopValueState::instance.attackInfo.nof_tribes[wave] != 0) {
                    DAT_TroopValueState::instance.attackInfo.index = wave;
                    int const waveAge = ++DAT_TroopValueState::instance.attackInfo.someIntArray2[wave - 1];
                    if (DAT_TroopValueState::instance.attackInfo.lowTroopValueRelated && waveAge > 10
                        && DAT_TroopValueState::instance.attackInfo.value3Array01[wave] != Map::Enums::AWS_ENDED) {
                        DAT_TroopValueState::instance.attackInfo.attackWaveTicker[wave] = 0;
                        DAT_TroopValueState::instance.attackInfo.value3Array01[wave] = Map::Enums::AWS_ENDED;
                        MACRO_CALL_MEMBER(
                            Audio::MSS::SoundSystem_Func::handleBattleEndMusicTransition, DAT_SoundSystemState::ptr)();
                    }
                    Map::Enums::AttackWaveStateInt const waveState
                        = DAT_TroopValueState::instance.attackInfo.value3Array01[wave];
                    if (waveState == Map::Enums::AWS_GATHERING) {
                        MACRO_CALL_MEMBER(TroopValueState_Func::initializeOrAdvanceAttackWave, this)(wave);
                    } else if (waveState == Map::Enums::AWS_ADVANCING) {
                        MACRO_CALL_MEMBER(TroopValueState_Func::advanceAttackWaveStaging, this)(wave);
                    } else if (waveState == Map::Enums::AWS_PREPARING_SIEGE) {
                        MACRO_CALL_MEMBER(TroopValueState_Func::updateInProgressAttackWave, this)(wave);
                    } else if (waveState == Map::Enums::AWS_ASSIGNING_TARGETS) {
                        MACRO_CALL_MEMBER(TroopValueState_Func::executeAttackWaveTargetAssignment, this)(wave);
                    } else if (waveState == Map::Enums::AWS_DELAYED_TARGET_ASSIGNMENT) {
                        MACRO_CALL_MEMBER(TroopValueState_Func::executeDelayedAttackWaveTargetAssignment, this)(wave);
                    } else if (waveState == Map::Enums::AWS_5Unk) {
                    } else if (waveState == Map::Enums::AWS_ENDED) {
                        MACRO_CALL_MEMBER(TroopValueState_Func::updateActiveAttackWaveState, this)(wave);
                    }
                } else {
                    DAT_TroopValueState::instance.attackInfo.value3Array01[wave] = Map::Enums::AWS_GATHERING;
                }
                DAT_TroopValueState::instance.attackInfo.nof_tribes[wave] = 0;
                DAT_TroopValueState::instance.attackInfo.unknownByteArray02[wave] = 0;
            }
            DAT_TroopValueState::instance.attackInfo.attackWaveSweepActive = 0;
        }

    }
}
}
