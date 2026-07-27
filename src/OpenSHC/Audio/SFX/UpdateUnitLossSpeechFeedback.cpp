#include "../SFX.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_CurrentPlayerUnitLosses.hpp"
#include "OpenSHC/Globals/DAT_CurrentPlayerUnitLossesHistory.hpp"
#include "OpenSHC/Globals/DAT_DestroyedBuildingsCount.hpp"
#include "OpenSHC/Globals/DAT_DestroyedBuildingsCountHistory.hpp"
#include "OpenSHC/Globals/DAT_GL_Counter.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TotalUnitValueLossesEnemyHistory.hpp"
#include "OpenSHC/Globals/DAT_UnitValueLossesPerEnemyPlayer.hpp"
#include "OpenSHC/Globals/Dat_UnitValueLossesHistoryPerEnemyPlayer.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044B840
        void __stdcall UpdateUnitLossSpeechFeedback()
        {
            if (DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_BUILD_MENU) {
                return;
            }
            if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .playerDeathRelated) {
                return;
            }
            if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .lordKilledByPlayerID) {
                return;
            }
            if (DAT_GameCore::instance.gameMode_2 == Game::GM_CAMPAIGN_MISSION) {
                return;
            }
            ++DAT_GL_Counter::instance;
            for (int _offset = 8; _offset >= 0; --_offset) {
                DAT_CurrentPlayerUnitLossesHistory::instance[_offset + 1]
                    = DAT_CurrentPlayerUnitLossesHistory::instance[_offset];
                DAT_TotalUnitValueLossesEnemyHistory::instance[_offset + 1]
                    = DAT_TotalUnitValueLossesEnemyHistory::instance[_offset];
                for (int i = 0; i < 9; ++i) {
                    Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[i][_offset + 1]
                        = Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[i][_offset];
                }
            }
            DAT_CurrentPlayerUnitLossesHistory::instance[0] = DAT_CurrentPlayerUnitLosses::instance;
            DAT_TotalUnitValueLossesEnemyHistory::instance[0] = 0;
            for (int i = 1; i < 9; ++i) {
                DAT_TotalUnitValueLossesEnemyHistory::instance[0] += DAT_UnitValueLossesPerEnemyPlayer::instance[i];
                Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[i][0]
                    = DAT_UnitValueLossesPerEnemyPlayer::instance[i];
            }
            int iVar1
                = DAT_CurrentPlayerUnitLossesHistory::instance[0] + DAT_TotalUnitValueLossesEnemyHistory::instance[0];
            int iVar2 = DAT_CurrentPlayerUnitLossesHistory::instance[1]
                + DAT_TotalUnitValueLossesEnemyHistory::instance[1] + DAT_CurrentPlayerUnitLossesHistory::instance[2]
                + DAT_TotalUnitValueLossesEnemyHistory::instance[2];
            if (DAT_GL_Counter::instance >= 2 && 50 > iVar1 && iVar2 > 150) {

                int smallPlayerUnitLossesSum
                    = DAT_CurrentPlayerUnitLossesHistory::instance[1] + DAT_CurrentPlayerUnitLossesHistory::instance[2];
                int smallTotalEnemyUnitLossesSum = DAT_TotalUnitValueLossesEnemyHistory::instance[1]
                    + DAT_TotalUnitValueLossesEnemyHistory::instance[2];
                int _relative1 = MACRO_CALL(SFX_Func::UpdateUnitLossSpeechFeedback_RelativeValueForGenie)(
                    smallPlayerUnitLossesSum, smallTotalEnemyUnitLossesSum);

                int playerUnitLossesSum = 0;
                int totalEnemyUnitLossesSum = 0;
                for (int i = 1; i < 10; ++i) {
                    playerUnitLossesSum += DAT_CurrentPlayerUnitLossesHistory::instance[i];
                    totalEnemyUnitLossesSum += DAT_TotalUnitValueLossesEnemyHistory::instance[i];
                }
                int _relative2 = MACRO_CALL(SFX_Func::UpdateUnitLossSpeechFeedback_RelativeValueForGenie)(
                    playerUnitLossesSum, totalEnemyUnitLossesSum);

                if (_relative1 == 0 && _relative2 == 0) {
                    if (DAT_GameCore::instance.genieVoiceActive) {
                        /* "A Valliant Effort" */
                        MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_Genie_29_wav_005a4ecc);
                    }
                    DAT_GL_Counter::instance = 0;
                }
                if (_relative1 > 0 && _relative2 > 0) {
                    _relative1 = (_relative2 + _relative1) / 2;
                    if (DAT_GameCore::instance.genieVoiceActive) {
                        if (_relative1 == 1) {
                            /* "Majestic" */
                            MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_Genie_30_wav_005a4ebc);
                        } else if (_relative1 == 2) {
                            /* "Excellent" */
                            MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_Genie_31_wav_005a4eac);
                        } else if (_relative1 == 3) {
                            /* "Impressive" */
                            MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_Genie_32_wav_005a4e9c);
                        } else if (_relative1 == 4) {
                            /* "Glorious" */
                            MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_Genie_34_wav_005a4e8c);
                        } else if (_relative1 == 5) {
                            /* "For the crown" */
                            MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_Genie_37_wav_005a4e7c);
                        } else if (_relative1 == 6) {
                            /* "Heroic" */
                            MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_Genie_38_wav_005a4e6c);
                        } else if (_relative1 >= 7) {
                            /* "It's a Rout" */
                            MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_Genie_39_wav_005a4e5c);
                        }
                    }
                    DAT_GL_Counter::instance = 0;
                }
                if (_relative1 < 0 && _relative2 < 0) {
                    int iVar3 = (_relative2 + _relative1) / 2;
                    if (DAT_GameCore::instance.genieVoiceActive) {
                        if (iVar3 == -1) {
                            /* "Vanquished" */
                            MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_Genie_42_wav_005a4e4c);
                        } else if (iVar3 == -2) {
                            /* "Crest falling" */
                            MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_Genie_43_wav_005a4e3c);
                        }
                    }
                    if (iVar3 <= -3) {
                        if (DAT_GameCore::instance.genieVoiceActive) {
                            /* "Humiliated" */
                            MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_Genie_44_wav_005a4e2c);
                        }
                        int playerId = -1;
                        int maxLossesOfEnemy = 0;
                        for (int i = 1; i < 9; ++i) {
                            int summaryEnemyUnitLosses = 0;
                            for (int j = 1; j < 10; ++j) {
                                summaryEnemyUnitLosses += Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[i][j];
                            }
                            if (summaryEnemyUnitLosses > maxLossesOfEnemy) {
                                maxLossesOfEnemy = summaryEnemyUnitLosses;
                                playerId = i;
                            }
                        }
                        if (playerId != -1
                            && DAT_GameState::instance.mapAndTime.playerTeams[playerId]
                                != DAT_GameState::instance.mapAndTime
                                    .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]) {
                            MACRO_CALL_MEMBER(AI::AICState_Func::playFriendlyVictoryBikFromPlayer, DAT_AICState::ptr)(
                                playerId);
                        }
                    }
                    DAT_GL_Counter::instance = 0;
                }
            }
            DAT_CurrentPlayerUnitLosses::instance = 0;
            for (int i = 0; i < 9; ++i) {
                DAT_UnitValueLossesPerEnemyPlayer::instance[i] = 0;
            }
            if (DAT_DestroyedBuildingsCount::instance > 1
                && DAT_DestroyedBuildingsCountHistory::instance[3] + DAT_DestroyedBuildingsCountHistory::instance[2]
                        + DAT_DestroyedBuildingsCountHistory::instance[1]
                        + DAT_DestroyedBuildingsCountHistory::instance[0] + DAT_DestroyedBuildingsCount::instance
                    > 5) {
                if (DAT_GameCore::instance.genieVoiceActive) {
                    /* "Where is your Castle" */
                    MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_Genie_41_wav_005a4e1c);
                }
                DAT_DestroyedBuildingsCount::instance = 0;
                DAT_DestroyedBuildingsCountHistory::instance[0] = 0;
                DAT_DestroyedBuildingsCountHistory::instance[1] = 0;
                DAT_DestroyedBuildingsCountHistory::instance[2] = 0;
            }
            DAT_DestroyedBuildingsCountHistory::instance[3] = DAT_DestroyedBuildingsCountHistory::instance[2];
            DAT_DestroyedBuildingsCountHistory::instance[2] = DAT_DestroyedBuildingsCountHistory::instance[1];
            DAT_DestroyedBuildingsCountHistory::instance[1] = DAT_DestroyedBuildingsCountHistory::instance[0];
            DAT_DestroyedBuildingsCountHistory::instance[0] = DAT_DestroyedBuildingsCount::instance;
            DAT_DestroyedBuildingsCount::instance = 0;
        }

        // FUNCTION: STRONGHOLDCRUSADER 0x0044AAB0
        int __cdecl UpdateUnitLossSpeechFeedback_RelativeValueForGenie(int larger, int smaller)
        {
            if (larger < 1) {
                larger = 1;
            }
            if (smaller < 1) {
                smaller = 1;
            }
            if (larger > smaller) {
                int iVar1 = (larger * 100) / smaller;
                if (iVar1 < 150) {
                    return 0;
                }
                if (iVar1 < 170) {
                    return 1;
                }
                if (iVar1 < 190) {
                    return 2;
                }
                if (iVar1 < 210) {
                    return 3;
                }
                if (iVar1 < 230) {
                    return 4;
                }
                if (iVar1 < 250) {
                    return 5;
                }
                if (iVar1 < 270) {
                    return 6;
                }
                return 7;
            } else {
                int iVar1 = (smaller * 100) / larger;
                if (iVar1 < 150) {
                    return 0;
                }
                if (iVar1 < 190) {
                    return -1;
                }
                if (iVar1 < 240) {
                    return -2;
                }
                return -3;
            }
        }

    }
}
}
