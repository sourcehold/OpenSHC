#include "../SFXState.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio.func.hpp"
#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Audio/SFX.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/UI/GreatestLord.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_00b9869c.hpp"
#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_CurrentPlayerRanking.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_IsKeepEnclosed.hpp"
#include "OpenSHC/Globals/DAT_KeepEnclosementCooldown.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DWORD_LatestPLayerStatusMessageTime.hpp"
#include "OpenSHC/Globals/INT_00b98664.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044C410
        void SFXState::playSFXVoices()
        {
            if (DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_BUILD_MENU
                || DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .playerDeathRelated
                || DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .lordKilledByPlayerID
                || DAT_GameCore::instance.gameMode_2 == Game::GM_CAMPAIGN_MISSION) {

                if (DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_BUILD_MENU
                    && DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU) {
                    return;
                }
                DAT_00b9869c::instance = 0;
                return;
            }

            if (!DAT_00b9869c::instance) {
                DAT_00b9869c::instance = 1;
                MACRO_CALL(Audio_Func::ResetGreatestLordGenieSpeechState)();
            }

            if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                return;
            }

            DWORD _currentTime = timeGetTime();
            if (MACRO_CALL_MEMBER(MSS::SoundSystem_Func::shouldSoundXNotBePlaying, DAT_SoundSystemState::ptr)()) {
                return;
            }

            if (1000 < _currentTime - DAT_KeepEnclosementCooldown::instance) {
                if (MACRO_CALL_MEMBER(Game::GameStateStructures_Func::checkKeepEnclosed, DAT_GameState::ptr)(
                        DAT_GameSynchronyState::instance.currentPlayerSlotID)) {
                    if (!DAT_IsKeepEnclosed::instance) {
                        if (DAT_GameCore::instance.genieVoiceActive) {
                            MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_Genie_45_wav_005a4f94);
                        }
                        DAT_IsKeepEnclosed::instance = 1;
                        DAT_KeepEnclosementCooldown::instance = _currentTime;
                        return;
                    }
                } else if (DAT_IsKeepEnclosed::instance) {
                    DAT_IsKeepEnclosed::instance = 0;
                }
                DAT_KeepEnclosementCooldown::instance = _currentTime;
            }

            if (_currentTime - DWORD_LatestPLayerStatusMessageTime::instance < 300000) {
                return;
            }

            if (DAT_GameCore::instance.gamePausedLogical) {
                return;
            }

            int _ranking = MACRO_CALL(SFX_Func::ComputeCurrentPlayerRanking)();

            // NOTE: Structure produced fitting bytecode, unlike early returns. Variable name is guessed.
            bool detailedRanking = false;
            if (DAT_CurrentPlayerRanking::instance == -1) {
                DAT_CurrentPlayerRanking::instance = _ranking;
                detailedRanking = true;
            } else if (_ranking == DAT_CurrentPlayerRanking::instance && _ranking == 1) {
                if (DAT_GameCore::instance.genieVoiceActive) {
                    MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(SFX_FeelThePower);
                }
                detailedRanking = true;
            } else if (_ranking <= 0) {
                detailedRanking = true;
            } else if (_ranking < DAT_CurrentPlayerRanking::instance - 2) {
                if (DAT_GameCore::instance.genieVoiceActive) {
                    MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_Genie_25_wav_005a4f74);
                }
                detailedRanking = true;
            }

            if (!detailedRanking) {
                if (DAT_GameCore::instance.genieVoiceActive) {
                    if (_ranking == 1) {
                        MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(SFX_YouAreTheGreatestLord);
                    } else if (_ranking == 2) {
                        MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_Genie_16_wav_005a4f54);
                    } else if (_ranking == 3) {
                        MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_Genie_17_wav_005a4f44);
                    } else if (_ranking == 4) {
                        MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_Genie_18_wav_005a4f34);
                    } else if (_ranking == 5) {
                        MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_Genie_19_wav_005a4f24);
                    } else if (_ranking == 6) {
                        MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_Genie_20_wav_005a4f14);
                    } else if (_ranking == 7) {
                        MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_Genie_21_wav_005a4f04);
                    } else if (_ranking == 8) {
                        MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_Genie_22_wav_005a4ef4);
                    }
                }
                DAT_CurrentPlayerRanking::instance = _ranking;

                int iVar2 = 1;

                int currentPlayer;
                int playerAtRankOne;
                int lowestRankedAlivePlayer;

                currentPlayer = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                playerAtRankOne = MACRO_CALL(UI::GreatestLord_Func::GetPlayerAtRank)(1);
                if (DAT_GameState::instance.mapAndTime.playerTeams[playerAtRankOne]
                    == DAT_GameState::instance.mapAndTime.playerTeams[currentPlayer]) {

                    currentPlayer = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                    lowestRankedAlivePlayer = MACRO_CALL(UI::GreatestLord_Func::GetLowestRankedAlivePlayer)();
                    if (DAT_GameState::instance.mapAndTime.playerTeams[lowestRankedAlivePlayer]
                        != DAT_GameState::instance.mapAndTime.playerTeams[currentPlayer]) {

                        int const _teamMate = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::findAITeamMate,
                            DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
                        if (_teamMate
                            && MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(_teamMate)) {
                            if (INT_00b98664::instance) {
                                MACRO_CALL_MEMBER(AI::AICState_Func::playTeamWinningBikFromPlayer, DAT_AICState::ptr)(
                                    _teamMate);
                            }
                            iVar2 = 0;
                        }
                    }
                }

                currentPlayer = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                lowestRankedAlivePlayer = MACRO_CALL(UI::GreatestLord_Func::GetLowestRankedAlivePlayer)();
                if (DAT_GameState::instance.mapAndTime.playerTeams[lowestRankedAlivePlayer]
                    == DAT_GameState::instance.mapAndTime.playerTeams[currentPlayer]) {

                    currentPlayer = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                    playerAtRankOne = MACRO_CALL(UI::GreatestLord_Func::GetPlayerAtRank)(1);
                    if (DAT_GameState::instance.mapAndTime.playerTeams[playerAtRankOne]
                        == DAT_GameState::instance.mapAndTime.playerTeams[currentPlayer]) {

                        int const _teamMate = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::findAITeamMate,
                            DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
                        if (_teamMate
                            && MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(_teamMate)) {
                            iVar2 = 2;
                            if (INT_00b98664::instance != 2) {
                                MACRO_CALL_MEMBER(AI::AICState_Func::playNoHelpBikFromPlayer, DAT_AICState::ptr)(
                                    _teamMate);
                            }
                        }
                    }
                }

                INT_00b98664::instance = iVar2;
            }
            DWORD_LatestPLayerStatusMessageTime::instance = _currentTime;
        }

    }
}
}
