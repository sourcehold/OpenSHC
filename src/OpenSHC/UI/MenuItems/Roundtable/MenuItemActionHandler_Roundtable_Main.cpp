#include "../Roundtable.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/AI/AITypeA.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_00df423c.hpp"
#include "OpenSHC/Globals/DAT_00df4240.hpp"
#include "OpenSHC/Globals/DAT_00df4298.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/INT_00df4244.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004AEA50
        void Roundtable::MenuItemActionHandler_Roundtable_Main(int param_1, ...)
        {
            BOOLEnum BVar3;
            int playerID_01;
            if (!DAT_GameSynchronyState::instance.isHost) {
                return;
            }
            if (param_1 < 9) {
                if (DAT_00df423c::instance != 0) {
                    param_1 += 10;
                }
                if (param_1 < 9) {
                    DAT_00df423c::instance = param_1;
                    INT_00df4244::instance = 0;
                }
            }
            if ((param_1 - 0xbU < 8) && (DAT_00df423c::instance != 0)) {
                int playerID
                    = (int)*(char*)((int)DAT_GameSynchronyState::instance.mapSendRequestStatePerPlayer + param_1 + 26);
                playerID_01
                    = (int)(char)DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[DAT_00df423c::instance];
                if (0 < playerID_01 && 0 < playerID && playerID != playerID_01
                    && (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID_01] != -1
                        || (BVar3 = MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer,
                                DAT_GameSynchronyState::ptr)(playerID_01),
                            BVar3))
                    && (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1
                        || (BVar3 = MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer,
                                DAT_GameSynchronyState::ptr)(playerID),
                            BVar3))) {
                    int iVar4 = 0;
                    for (int playerID_00 = 1;
                        playerID_00 < countof(DAT_GameSynchronyState::instance.currentPlayerFullIDArray);
                        ++playerID_00) {
                        if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID_00] != -1)
                            || (BVar3 = MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer,
                                    DAT_GameSynchronyState::ptr)(playerID_00),
                                BVar3)) {
                            ++iVar4;
                        }
                    }
                    if (2 < iVar4) {
                        if ((DAT_GameSynchronyState::instance.currentAIArray[playerID_01] == OpenSHC::AI::AITA_RAT)
                            && (DAT_00df4240::instance == 0)) {
                            if (DAT_GameCore::instance.genieVoiceActive) {
                                // "Not the rodent"
                                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                    // "Genie_13.wav"
                                    s_Genie_13_wav_005a7710);
                            }
                            DAT_00df4240::instance = 1;
                        }
                        if ((DAT_GameSynchronyState::instance.currentAIArray[playerID_01] == OpenSHC::AI::AITA_SULTAN)
                            && (DAT_00df4298::instance == 0)) {
                            if (DAT_GameCore::instance.genieVoiceActive) {
                                // "Oh no"
                                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                    // "Genie_14.wav"
                                    s_Genie_14_wav_005a7700);
                            }
                            DAT_00df4298::instance = 1;
                        }
                    }
                    int bVar1 = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[playerID];
                    if ((DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[playerID_01] != bVar1)
                        || (DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[playerID_01] == 0)) {
                        if (bVar1 == 0) {
                            bVar1 = 0;
                            for (int i = 1; i < countof(DAT_GameSynchronyState::instance.DAT_PlayerGroupArray); ++i) {
                                if ('\0' < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[i]
                                    && (char)bVar1 < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[i]) {
                                    bVar1 = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[i];
                                }
                            }
                            DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[(
                                char)DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[DAT_00df423c::instance]]
                                = bVar1 + 1;
                            DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[*(
                                char*)((int)DAT_GameSynchronyState::instance.mapSendRequestStatePerPlayer + param_1
                                + 26)] = bVar1 + 1;
                            MACRO_CALL_MEMBER(
                                OpenSHC::Audio::SFX::SFXState_Func::scheduleSFXVariation, DAT_SFXState::ptr)(7, 1);
                            BVar3 = MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::shouldSoundXNotBePlaying,
                                DAT_SoundSystemState::ptr)();
                            if (!BVar3 && 2 < iVar4 && DAT_GameCore::instance.genieVoiceActive) {
                                MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                                switch ((int)SEC_RNG::instance.currentNumber1 % 7) {
                                case 0:
                                    // "We will be invincible"
                                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX,
                                        // "genie_05.wav"
                                        DAT_SFXState::ptr)(s_genie_05_wav_005a76f0);
                                    break;
                                case 1:
                                    // "A worthy ally"
                                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX,
                                        // "genie_06.wav"
                                        DAT_SFXState::ptr)(s_genie_06_wav_005a76e0);
                                    break;
                                case 2:
                                    // "Watch my back"
                                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX,
                                        // "genie_07.wav"
                                        DAT_SFXState::ptr)(s_genie_07_wav_005a76d0);
                                    break;
                                case 3:
                                    // "Yeeees"
                                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX,
                                        // "genie_08.wav"
                                        DAT_SFXState::ptr)(s_genie_08_wav_005a76c0);
                                    break;
                                case 4:
                                    // "On my honour"
                                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX,
                                        // "genie_09.wav"
                                        DAT_SFXState::ptr)(s_genie_09_wav_005a76b0);
                                    break;
                                case 5:
                                    // "We rule"
                                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX,
                                        // "genie_10.wav"
                                        DAT_SFXState::ptr)(s_genie_10_wav_005a76a0);
                                    break;
                                case 6:
                                    // "I pledge allegiance"
                                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX,
                                        // "genie_04.wav"
                                        DAT_SFXState::ptr)(s_genie_04_wav_005a7690);
                                }
                            }
                        } else {
                            DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[playerID_01] = bVar1;
                            MACRO_CALL_MEMBER(
                                OpenSHC::Audio::SFX::SFXState_Func::scheduleSFXVariation, DAT_SFXState::ptr)(7, 1);
                        }
                    }
                }
                if ((param_1 - 10 == DAT_00df423c::instance) && (INT_00df4244::instance == 0)) {
                    INT_00df4244::instance = 1;
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions,
                        DAT_GameSynchronyState::ptr)();
                    DAT_00df423c::instance = 0;
                }
            }
            if (param_1 == 21) {
                if ((DAT_00df423c::instance != 0)
                    && (DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[DAT_00df423c::instance] != 0)) {
                    DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[(
                        char)DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[DAT_00df423c::instance]] = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions,
                        DAT_GameSynchronyState::ptr)();
                    DAT_00df423c::instance = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::scheduleSFXVariation, DAT_SFXState::ptr)(
                        7, 0);
                }
            } else if (param_1 == 100) {
                DAT_MenuModalComposition1::instance.activeModalDialogID = OpenSHC::UI::Enums::MMT_NONE;
                MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions,
                    DAT_GameSynchronyState::ptr)();
                int cVar2 = 0;
                for (int i = 1; i < countof(DAT_GameSynchronyState::instance.DAT_PlayerGroupArray); ++i) {
                    if ('\0' < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[i]) {
                        cVar2 += '\x01';
                    }
                }
                if (cVar2 != '\0') {
                    // "The sides are drawn"
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                        // "Genie_02.wav"
                        s_Genie_02_wav_005a7680);
                }
            } else {
                if (param_1 == 101) {
                    memcpy(DAT_GameSynchronyState::instance.DAT_PlayerGroupArray,
                        DAT_GameSynchronyState::instance.playerGroupArray2Unk,
                        sizeof(DAT_GameSynchronyState::instance.DAT_PlayerGroupArray));
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions,
                        DAT_GameSynchronyState::ptr)();
                    DAT_MenuModalComposition1::instance.activeModalDialogID = OpenSHC::UI::Enums::MMT_NONE;
                    MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions,
                        DAT_GameSynchronyState::ptr)();
                }
                if (param_1 == 200) {
                    if (DAT_00df423c::instance != 0) {
                        DAT_00df423c::instance = 0;
                    }
                } else if (((param_1 == 201) || (param_1 == 202)) && DAT_00df423c::instance != 0
                    && (INT_00df4244::instance != 1 || (param_1 == 201))) {
                    DAT_00df423c::instance = 0;
                }
            }
        }

    }
}
}
