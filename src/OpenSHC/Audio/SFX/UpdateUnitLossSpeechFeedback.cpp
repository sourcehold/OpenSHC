#include "../SFX.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game.func.hpp"
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
            int _relative1;
            int _relative2;
            int iVar3;
            int iVar4;
            int iVar6;
            int iVar7;

            if (DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_BUILD_MENU) {
                return;
            }
            if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .playerDeathRelated
                != 0) {
                return;
            }
            if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .lordKilledByPlayerID
                != 0) {
                return;
            }
            if (DAT_GameCore::instance.gameMode_2 == Game::GM_CAMPAIGN_MISSION) {
                return;
            }
            ++DAT_GL_Counter::instance;
            for (int _offset = 8; _offset >= 0; --_offset) {
                DAT_TotalUnitValueLossesEnemyHistory::instance[_offset + 1]
                    = DAT_TotalUnitValueLossesEnemyHistory::instance[_offset];
                DAT_CurrentPlayerUnitLossesHistory::instance[_offset + 1]
                    = DAT_CurrentPlayerUnitLossesHistory::instance[_offset];
                for (int i = 0; i < 9; ++i) {
                    Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[i][_offset + 1]
                        = Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[i][_offset];
                }
            }
            DAT_CurrentPlayerUnitLossesHistory::instance[0] = DAT_CurrentPlayerUnitLosses::instance;
            DAT_TotalUnitValueLossesEnemyHistory::instance[0] = 0;
            for (int i = 1; i < 9; ++i) {
                Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[i][0]
                    = DAT_UnitValueLossesPerEnemyPlayer::instance[i];
                DAT_TotalUnitValueLossesEnemyHistory::instance[0] += DAT_UnitValueLossesPerEnemyPlayer::instance[i];
            }
            if (!(((DAT_GL_Counter::instance < 2)
                      || (49
                          < DAT_TotalUnitValueLossesEnemyHistory::instance[0] + DAT_CurrentPlayerUnitLosses::instance))
                    || (DAT_TotalUnitValueLossesEnemyHistory::instance[2]
                            + DAT_CurrentPlayerUnitLossesHistory::instance[2]
                            + DAT_TotalUnitValueLossesEnemyHistory::instance[1]
                            + DAT_CurrentPlayerUnitLossesHistory::instance[1]
                        < 151))) {
                _relative1 = MACRO_CALL(Game_Func::RelativeValueForGenie)(
                    DAT_CurrentPlayerUnitLossesHistory::instance[1] + DAT_CurrentPlayerUnitLossesHistory::instance[2],
                    DAT_TotalUnitValueLossesEnemyHistory::instance[2]
                        + DAT_TotalUnitValueLossesEnemyHistory::instance[1]);
                _relative2 = MACRO_CALL(Game_Func::RelativeValueForGenie)(
                    DAT_CurrentPlayerUnitLossesHistory::instance[3] + DAT_CurrentPlayerUnitLossesHistory::instance[4]
                        + DAT_CurrentPlayerUnitLossesHistory::instance[5]
                        + DAT_CurrentPlayerUnitLossesHistory::instance[6]
                        + DAT_CurrentPlayerUnitLossesHistory::instance[7]
                        + DAT_CurrentPlayerUnitLossesHistory::instance[8]
                        + DAT_CurrentPlayerUnitLossesHistory::instance[9]
                        + DAT_CurrentPlayerUnitLossesHistory::instance[2]
                        + DAT_CurrentPlayerUnitLossesHistory::instance[1],
                    DAT_TotalUnitValueLossesEnemyHistory::instance[5]
                        + DAT_TotalUnitValueLossesEnemyHistory::instance[4]
                        + DAT_TotalUnitValueLossesEnemyHistory::instance[6]
                        + DAT_TotalUnitValueLossesEnemyHistory::instance[7]
                        + DAT_TotalUnitValueLossesEnemyHistory::instance[8]
                        + DAT_TotalUnitValueLossesEnemyHistory::instance[9]
                        + DAT_TotalUnitValueLossesEnemyHistory::instance[3]
                        + DAT_TotalUnitValueLossesEnemyHistory::instance[2]
                        + DAT_TotalUnitValueLossesEnemyHistory::instance[1]);
                if (_relative1 == 0) {
                    if (_relative2 == 0) {
                        if (DAT_GameCore::instance.genieVoiceActive != FALSE) {
                            /* "A Valliant Effort" */
                            MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_Genie_29_wav_005a4ecc);
                        }
                        DAT_GL_Counter::instance = 0;
                    }
                } else {
                    if ((0 < _relative1) && (0 < _relative2)) {
                        _relative1 = (_relative2 + _relative1) / 2;
                        if (DAT_GameCore::instance.genieVoiceActive) {
                            if (_relative1 == 1) {
                                /* "Majestic" */
                                MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                    s_Genie_30_wav_005a4ebc);
                            } else if (_relative1 == 2) {
                                /* "Excellent" */
                                MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                    s_Genie_31_wav_005a4eac);
                            } else if (_relative1 == 3) {
                                /* "Impressive" */
                                MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                    s_Genie_32_wav_005a4e9c);
                            } else if (_relative1 == 4) {
                                /* "Glorious" */
                                MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                    s_Genie_34_wav_005a4e8c);
                            } else if (_relative1 == 5) {
                                /* "For the crown" */
                                MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                    s_Genie_37_wav_005a4e7c);
                            } else if (_relative1 == 6) {
                                /* "Heroic" */
                                MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                    s_Genie_38_wav_005a4e6c);
                            } else if (_relative1 >= 7) {
                                /* "It's a Rout" */
                                MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                    s_Genie_39_wav_005a4e5c);
                            }
                        }
                        DAT_GL_Counter::instance = 0;
                    }

                    if (!((-1 < _relative1) || (-1 < _relative2))) {
                        iVar3 = (_relative2 + _relative1) / 2;
                        if (DAT_GameCore::instance.genieVoiceActive && iVar3 == -1) {
                            /* "Vanquished" */
                            MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_Genie_42_wav_005a4e4c);
                        } else if (DAT_GameCore::instance.genieVoiceActive && iVar3 == -2) {
                            /* "Crest falling" */
                            MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_Genie_43_wav_005a4e3c);
                        } else if (!DAT_GameCore::instance.genieVoiceActive || iVar3 != -2) {
                            if (iVar3 <= -3) {
                                if (DAT_GameCore::instance.genieVoiceActive != FALSE) {
                                    /* "Humiliated" */
                                    MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                        s_Genie_44_wav_005a4e2c);
                                }
                                iVar7 = -1;
                                iVar6 = 0;
                                for (int i = 1; i < 10; ++i) {
                                    iVar4 = 0;
                                    for (int j = 1; j < 10; ++j) {
                                        iVar4 += Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[i][j];
                                    }
                                    if (iVar4 > iVar6) {
                                        iVar6 = iVar4;
                                        iVar7 = i;
                                    }
                                }
                                if ((iVar7 != -1)
                                    && (DAT_GameState::instance.mapAndTime.playerTeams[iVar7]
                                        != DAT_GameState::instance.mapAndTime
                                            .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID])) {
                                    MACRO_CALL_MEMBER(
                                        AI::AICState_Func::playFriendlyVictoryBikFromPlayer, DAT_AICState::ptr)(iVar7);
                                }
                            }
                        }
                        DAT_GL_Counter::instance = 0;
                    }
                }
            }
            DAT_CurrentPlayerUnitLosses::instance = 0;
            DAT_UnitValueLossesPerEnemyPlayer::instance[0] = 0;
            DAT_UnitValueLossesPerEnemyPlayer::instance[1] = 0;
            DAT_UnitValueLossesPerEnemyPlayer::instance[2] = 0;
            DAT_UnitValueLossesPerEnemyPlayer::instance[3] = 0;
            DAT_UnitValueLossesPerEnemyPlayer::instance[4] = 0;
            DAT_UnitValueLossesPerEnemyPlayer::instance[5] = 0;
            DAT_UnitValueLossesPerEnemyPlayer::instance[6] = 0;
            DAT_UnitValueLossesPerEnemyPlayer::instance[7] = 0;
            DAT_UnitValueLossesPerEnemyPlayer::instance[8] = 0;
            if ((1 < DAT_DestroyedBuildingsCount::instance)
                && (5 < DAT_DestroyedBuildingsCountHistory::instance[0]
                        + DAT_DestroyedBuildingsCountHistory::instance[1]
                        + DAT_DestroyedBuildingsCountHistory::instance[2]
                        + DAT_DestroyedBuildingsCountHistory::instance[3] + DAT_DestroyedBuildingsCount::instance)) {
                if (DAT_GameCore::instance.genieVoiceActive != FALSE) {
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
            return;
        }

    }
}
}
