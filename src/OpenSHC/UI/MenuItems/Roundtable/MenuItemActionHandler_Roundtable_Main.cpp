#include "../Roundtable.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/AI/AITypeA.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
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

        // FUNCTION: STRONGHOLDCRUSADER 0x004AEA50
        void Roundtable::MenuItemActionHandler_Roundtable_Main(int button, ...)
        {
            if (!DAT_GameSynchronyState::instance.isHost) {
                return;
            }
            // a lord's seat picks the lord; with one picked, the seats count as targets 11..18
            if (button <= 8) {
                if (DAT_00df423c::instance != 0) {
                    button += 10;
                }
                if (button <= 8) {
                    DAT_00df423c::instance = button;
                    INT_00df4244::instance = 0;
                }
            }
            if (button >= 11 && button <= 18 && DAT_00df423c::instance != 0) {
                int const chosen = DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[DAT_00df423c::instance];
                int const target = DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[button - 10];
                if (chosen > 0 && target > 0 && target != chosen
                    && (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[chosen] != -1
                        || MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer,
                            DAT_GameSynchronyState::ptr)(chosen))
                    && (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[target] != -1
                        || MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer,
                            DAT_GameSynchronyState::ptr)(target))) {
                    int players = 0;
                    for (int playerID = 1;
                        playerID < countof(DAT_GameSynchronyState::instance.currentPlayerFullIDArray); ++playerID) {
                        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1
                            || MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer,
                                DAT_GameSynchronyState::ptr)(playerID)) {
                            ++players;
                        }
                    }
                    if (players > 2) {
                        if (DAT_GameSynchronyState::instance.currentAIArray[chosen] == OpenSHC::AI::AITA_RAT
                            && DAT_00df4240::instance == 0) {
                            if (DAT_GameCore::instance.genieVoiceActive) {
                                // "Genie_13.wav": "Not the rodent"
                                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                    s_Genie_13_wav_005a7710);
                            }
                            DAT_00df4240::instance = 1;
                        }
                        if (DAT_GameSynchronyState::instance.currentAIArray[chosen] == OpenSHC::AI::AITA_SULTAN
                            && DAT_00df4298::instance == 0) {
                            if (DAT_GameCore::instance.genieVoiceActive) {
                                // "Genie_14.wav": "Oh no"
                                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                    s_Genie_14_wav_005a7700);
                            }
                            DAT_00df4298::instance = 1;
                        }
                    }
                    int const chosenGroup = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[chosen];
                    int const targetGroup = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[target];
                    if (chosenGroup != targetGroup || chosenGroup == 0) {
                        if (targetGroup == 0) {
                            // both get a new group, one above the highest in use
                            int highest = 0;
                            for (int playerID = 1;
                                playerID < countof(DAT_GameSynchronyState::instance.DAT_PlayerGroupArray); ++playerID) {
                                if (DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[playerID] > 0
                                    && DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[playerID] > highest) {
                                    highest = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[playerID];
                                }
                            }
                            int const newGroup = highest + 1;
                            DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[DAT_GameSynchronyState::instance
                                    .DAT_RoundTableOrderArray[DAT_00df423c::instance]] = newGroup;
                            DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[DAT_GameSynchronyState::instance
                                    .DAT_RoundTableOrderArray[button - 10]] = newGroup;
                            MACRO_CALL_MEMBER(
                                OpenSHC::Audio::SFX::SFXState_Func::scheduleSFXVariation, DAT_SFXState::ptr)(7, 1);
                            if (!MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::shouldSoundXNotBePlaying,
                                    DAT_SoundSystemState::ptr)()
                                && players > 2 && DAT_GameCore::instance.genieVoiceActive) {
                                MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                                switch (SEC_RNG::instance.currentNumber1 % 7) {
                                case 0:
                                    // "genie_05.wav": "We will be invincible"
                                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX,
                                        DAT_SFXState::ptr)(s_genie_05_wav_005a76f0);
                                    break;
                                case 1:
                                    // "genie_06.wav": "A worthy ally"
                                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX,
                                        DAT_SFXState::ptr)(s_genie_06_wav_005a76e0);
                                    break;
                                case 2:
                                    // "genie_07.wav": "Watch my back"
                                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX,
                                        DAT_SFXState::ptr)(s_genie_07_wav_005a76d0);
                                    break;
                                case 3:
                                    // "genie_08.wav": "Yeeees"
                                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX,
                                        DAT_SFXState::ptr)(s_genie_08_wav_005a76c0);
                                    break;
                                case 4:
                                    // "genie_09.wav": "On my honour"
                                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX,
                                        DAT_SFXState::ptr)(s_genie_09_wav_005a76b0);
                                    break;
                                case 5:
                                    // "genie_10.wav": "We rule"
                                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX,
                                        DAT_SFXState::ptr)(s_genie_10_wav_005a76a0);
                                    break;
                                case 6:
                                    // "genie_04.wav": "I pledge allegiance"
                                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX,
                                        DAT_SFXState::ptr)(s_genie_04_wav_005a7690);
                                    break;
                                }
                            }
                        } else {
                            // the chosen lord joins the target's group
                            DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[chosen] = targetGroup;
                            MACRO_CALL_MEMBER(
                                OpenSHC::Audio::SFX::SFXState_Func::scheduleSFXVariation, DAT_SFXState::ptr)(7, 1);
                        }
                    }
                }
                if (button - 10 == DAT_00df423c::instance && INT_00df4244::instance == 0) {
                    INT_00df4244::instance = 1;
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions,
                        DAT_GameSynchronyState::ptr)();
                    DAT_00df423c::instance = 0;
                }
            }
            if (button == 21) {
                // the chosen lord leaves its group
                if (DAT_00df423c::instance != 0
                    && DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[DAT_00df423c::instance] != 0) {
                    DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[DAT_GameSynchronyState::instance
                            .DAT_RoundTableOrderArray[DAT_00df423c::instance]] = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions,
                        DAT_GameSynchronyState::ptr)();
                    DAT_00df423c::instance = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::scheduleSFXVariation, DAT_SFXState::ptr)(
                        7, 0);
                }
                return;
            }
            if (button == 100) {
                DAT_MenuModalComposition1::instance.activeModalDialogID = OpenSHC::UI::Enums::MMT_NONE;
                MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions,
                    DAT_GameSynchronyState::ptr)();
                int grouped = 0;
                for (int playerID = 1; playerID < countof(DAT_GameSynchronyState::instance.DAT_PlayerGroupArray);
                    ++playerID) {
                    if (DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[playerID] > 0) {
                        ++grouped;
                    }
                }
                if (grouped != 0) {
                    // "Genie_02.wav": "The sides are drawn"
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                        s_Genie_02_wav_005a7680);
                }
                return;
            }
            if (button == 101) {
                memcpy(DAT_GameSynchronyState::instance.DAT_PlayerGroupArray,
                    DAT_GameSynchronyState::instance.playerGroupArray2Unk,
                    sizeof(DAT_GameSynchronyState::instance.DAT_PlayerGroupArray));
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions,
                    DAT_GameSynchronyState::ptr)();
                DAT_MenuModalComposition1::instance.activeModalDialogID = OpenSHC::UI::Enums::MMT_NONE;
                MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions,
                    DAT_GameSynchronyState::ptr)();
                return;
            }
            if (button == 200) {
                if (DAT_00df423c::instance != 0) {
                    DAT_00df423c::instance = 0;
                }
                return;
            }
            if ((button == 201 || button == 202) && DAT_00df423c::instance != 0
                && (INT_00df4244::instance != 1 || button == 201)) {
                DAT_00df423c::instance = 0;
            }
        }

    }
}
}
