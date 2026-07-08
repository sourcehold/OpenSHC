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
            undefined4 uVar1;
            undefined4 uVar2;
            int _offset;
            int _relative1;
            int _relative2;
            int iVar3;
            int iVar4;
            int* piVar5;
            int iVar6;
            int iVar7;
            char const* wav_filename;

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
            _offset = 0;
            do {
                uVar1 = *(undefined4*)((int)DAT_TotalUnitValueLossesEnemyHistory::instance + _offset + 0x20);
                *(undefined4*)((int)DAT_CurrentPlayerUnitLossesHistory::instance + _offset + 0x24)
                    = *(undefined4*)((int)DAT_CurrentPlayerUnitLossesHistory::instance + _offset + 0x20);
                uVar2 = *(undefined4*)((int)Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[0] + _offset + 0x20);
                *(undefined4*)((int)DAT_TotalUnitValueLossesEnemyHistory::instance + _offset + 0x24) = uVar1;
                uVar1 = *(undefined4*)((int)Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[1] + _offset + 0x20);
                *(undefined4*)((int)Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[0] + _offset + 0x24) = uVar2;
                uVar2 = *(undefined4*)((int)Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[2] + _offset + 0x20);
                *(undefined4*)((int)Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[1] + _offset + 0x24) = uVar1;
                uVar1 = *(undefined4*)((int)Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[3] + _offset + 0x20);
                *(undefined4*)((int)Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[2] + _offset + 0x24) = uVar2;
                uVar2 = *(undefined4*)((int)Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[4] + _offset + 0x20);
                *(undefined4*)((int)Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[3] + _offset + 0x24) = uVar1;
                uVar1 = *(undefined4*)((int)Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[5] + _offset + 0x20);
                *(undefined4*)((int)Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[4] + _offset + 0x24) = uVar2;
                uVar2 = *(undefined4*)((int)Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[6] + _offset + 0x20);
                *(undefined4*)((int)Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[5] + _offset + 0x24) = uVar1;
                uVar1 = *(undefined4*)((int)Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[7] + _offset + 0x20);
                *(undefined4*)((int)Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[6] + _offset + 0x24) = uVar2;
                uVar2 = *(undefined4*)((int)Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[8] + _offset + 0x20);
                *(undefined4*)((int)Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[7] + _offset + 0x24) = uVar1;
                *(undefined4*)((int)Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[8] + _offset + 0x24) = uVar2;
                iVar7 = DAT_TotalUnitValueLossesEnemyHistory::instance[2];
                iVar6 = DAT_TotalUnitValueLossesEnemyHistory::instance[1];
                iVar3 = DAT_CurrentPlayerUnitLossesHistory::instance[2];
                _offset = _offset + -4;
            } while (-33 < _offset);
            Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[6][0] = DAT_UnitValueLossesPerEnemyPlayer::instance[6];
            Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[7][0] = DAT_UnitValueLossesPerEnemyPlayer::instance[7];
            DAT_CurrentPlayerUnitLossesHistory::instance[0] = DAT_CurrentPlayerUnitLosses::instance;
            DAT_TotalUnitValueLossesEnemyHistory::instance[0] = DAT_UnitValueLossesPerEnemyPlayer::instance[7]
                + DAT_UnitValueLossesPerEnemyPlayer::instance[8] + DAT_UnitValueLossesPerEnemyPlayer::instance[6]
                + DAT_UnitValueLossesPerEnemyPlayer::instance[5] + DAT_UnitValueLossesPerEnemyPlayer::instance[4]
                + DAT_UnitValueLossesPerEnemyPlayer::instance[3] + DAT_UnitValueLossesPerEnemyPlayer::instance[2]
                + DAT_UnitValueLossesPerEnemyPlayer::instance[1];
            Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[1][0] = DAT_UnitValueLossesPerEnemyPlayer::instance[1];
            Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[2][0] = DAT_UnitValueLossesPerEnemyPlayer::instance[2];
            Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[3][0] = DAT_UnitValueLossesPerEnemyPlayer::instance[3];
            Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[4][0] = DAT_UnitValueLossesPerEnemyPlayer::instance[4];
            Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[5][0] = DAT_UnitValueLossesPerEnemyPlayer::instance[5];
            Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[8][0] = DAT_UnitValueLossesPerEnemyPlayer::instance[8];
            if (((DAT_GL_Counter::instance < 2)
                    || (49 < DAT_TotalUnitValueLossesEnemyHistory::instance[0] + DAT_CurrentPlayerUnitLosses::instance))
                || (DAT_TotalUnitValueLossesEnemyHistory::instance[2] + DAT_CurrentPlayerUnitLossesHistory::instance[2]
                        + DAT_TotalUnitValueLossesEnemyHistory::instance[1]
                        + DAT_CurrentPlayerUnitLossesHistory::instance[1]
                    < 151))
                goto LAB_0044bbf0;
            _relative1 = MACRO_CALL(Game_Func::RelativeValueForGenie)(
                DAT_CurrentPlayerUnitLossesHistory::instance[1] + DAT_CurrentPlayerUnitLossesHistory::instance[2],
                DAT_TotalUnitValueLossesEnemyHistory::instance[2] + DAT_TotalUnitValueLossesEnemyHistory::instance[1]);
            _relative2 = MACRO_CALL(Game_Func::RelativeValueForGenie)(DAT_CurrentPlayerUnitLossesHistory::instance[3]
                    + DAT_CurrentPlayerUnitLossesHistory::instance[4] + DAT_CurrentPlayerUnitLossesHistory::instance[5]
                    + DAT_CurrentPlayerUnitLossesHistory::instance[6] + DAT_CurrentPlayerUnitLossesHistory::instance[7]
                    + DAT_CurrentPlayerUnitLossesHistory::instance[8] + DAT_CurrentPlayerUnitLossesHistory::instance[9]
                    + iVar3 + DAT_CurrentPlayerUnitLossesHistory::instance[1],
                DAT_TotalUnitValueLossesEnemyHistory::instance[5] + DAT_TotalUnitValueLossesEnemyHistory::instance[4]
                    + DAT_TotalUnitValueLossesEnemyHistory::instance[6]
                    + DAT_TotalUnitValueLossesEnemyHistory::instance[7]
                    + DAT_TotalUnitValueLossesEnemyHistory::instance[8]
                    + DAT_TotalUnitValueLossesEnemyHistory::instance[9]
                    + DAT_TotalUnitValueLossesEnemyHistory::instance[3] + iVar7 + iVar6);
            if (_relative1 == 0) {
                if (_relative2 != 0)
                    goto LAB_0044bbf0;
                if (DAT_GameCore::instance.genieVoiceActive != FALSE) {
                    /* "A Valliant Effort" */
                    MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_Genie_29_wav_005a4ecc);
                }
                goto LAB_0044bbe6;
            }
            if ((0 < _relative1) && (0 < _relative2)) {
                _relative1 = (_relative2 + _relative1) / 2;
                if (DAT_GameCore::instance.genieVoiceActive != FALSE) {
                    if (_relative1 == 1) {
                        /* "Majestic" */
                        wav_filename = s_Genie_30_wav_005a4ebc;
                    } else if (_relative1 == 2) {
                        /* "Excellent" */
                        wav_filename = s_Genie_31_wav_005a4eac;
                    } else if (_relative1 == 3) {
                        /* "Impressive" */
                        wav_filename = s_Genie_32_wav_005a4e9c;
                    } else if (_relative1 == 4) {
                        /* "Glorious" */
                        wav_filename = s_Genie_34_wav_005a4e8c;
                    } else if (_relative1 == 5) {
                        /* "For the crown" */
                        wav_filename = s_Genie_37_wav_005a4e7c;
                    } else if (_relative1 == 6) {
                        /* "Heroic" */
                        wav_filename = s_Genie_38_wav_005a4e6c;
                    } else {
                        if (_relative1 < 7)
                            goto LAB_0044bb0d;
                        /* "It's a Rout" */
                        wav_filename = s_Genie_39_wav_005a4e5c;
                    }
                    MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(wav_filename);
                }
            LAB_0044bb0d:
                DAT_GL_Counter::instance = 0;
            }
            if ((-1 < _relative1) || (-1 < _relative2))
                goto LAB_0044bbf0;
            iVar3 = (_relative2 + _relative1) / 2;
            if (DAT_GameCore::instance.genieVoiceActive == FALSE) {
            LAB_0044bb68:
                if (iVar3 < -2) {
                    if (DAT_GameCore::instance.genieVoiceActive != FALSE) {
                        /* "Humiliated" */
                        MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_Genie_44_wav_005a4e2c);
                    }
                    iVar7 = -1;
                    iVar6 = 0;
                    iVar3 = 1;
                    piVar5 = Dat_UnitValueLossesHistoryPerEnemyPlayer::instance[1] + 8;
                    do {
                        iVar4 = piVar5[-7] + piVar5[-6] + piVar5[-5] + piVar5[-4] + piVar5[-3] + piVar5[-2] + piVar5[-1]
                            + piVar5[1] + *piVar5;
                        if (iVar6 < iVar4) {
                            iVar6 = iVar4;
                            iVar7 = iVar3;
                        }
                        piVar5 = piVar5 + 10;
                        iVar3 = iVar3 + 1;
                    } while ((int)piVar5 < 0xb98610);
                    if ((iVar7 != -1)
                        && (DAT_GameState::instance.mapAndTime.playerTeams[iVar7]
                            != DAT_GameState::instance.mapAndTime
                                .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID])) {
                        MACRO_CALL_MEMBER(AI::AICState_Func::playFriendlyVictoryBikFromPlayer, DAT_AICState::ptr)(
                            iVar7);
                    }
                }
            } else if (iVar3 == -1) {
                /* "Vanquished" */
                MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_Genie_42_wav_005a4e4c);
            } else {
                if (iVar3 != -2)
                    goto LAB_0044bb68;
                /* "Crest falling" */
                MACRO_CALL_MEMBER(SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_Genie_43_wav_005a4e3c);
            }
        LAB_0044bbe6:
            DAT_GL_Counter::instance = 0;
        LAB_0044bbf0:
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
