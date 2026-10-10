#include "../Roundtable.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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

        using UI::Enums::MenuModalType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004AEA50
        void Roundtable::MenuItemActionHandler_Roundtable_Main(int param_1, ...)
        {
            BOOLEnum BVar3;
            int playerID_00;
            int playerID_01;
            if (DAT_GameSynchronyState::instance.isHost) {
                if (param_1 < 9) {
                    if (DAT_00df423c::instance) {
                        param_1 = param_1 + 10;
                    }
                    if (param_1 < 9) {
                        INT_00df4244::instance = 0;
                        DAT_00df423c::instance = param_1;
                    }
                }
                if ((param_1 - 0xbU < 8) && (DAT_00df423c::instance)) {
                    int playerID = (int)DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[param_1 - 10];
                    playerID_01
                        = (int)(char)DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[DAT_00df423c::instance];
                    if (0 < playerID_01 && 0 < playerID && playerID != playerID_01
                        && (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID_01] != -1
                            || (BVar3 = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::isAIPlayer,
                                    DAT_GameSynchronyState::ptr)(playerID_01),
                                BVar3))
                        && (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1
                            || (BVar3 = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::isAIPlayer,
                                    DAT_GameSynchronyState::ptr)(playerID),
                                BVar3))) {
                        int iVar4 = 0;
                        for (playerID_00 = 1; playerID_00 < 9; playerID_00++) {
                            if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID_00] != -1)
                                || (BVar3 = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::isAIPlayer,
                                        DAT_GameSynchronyState::ptr)(playerID_00),
                                    BVar3)) {
                                iVar4 = iVar4 + 1;
                            }
                        }
                        if (2 < iVar4) {
                            if ((DAT_GameSynchronyState::instance.currentAIArray[playerID_01] == 1)
                                && (!DAT_00df4240::instance)) {
                                if (DAT_GameCore::instance.genieVoiceActive) {
                                    /*
                                      "Not the rodent"
                                     */
                                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                        "Genie_13.wav");
                                }
                                DAT_00df4240::instance = 1;
                            }
                            if ((DAT_GameSynchronyState::instance.currentAIArray[playerID_01] == 7)
                                && (!DAT_00df4298::instance)) {
                                if (DAT_GameCore::instance.genieVoiceActive) {
                                    /*
                                      "Oh no"
                                     */
                                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                        "Genie_14.wav");
                                }
                                DAT_00df4298::instance = 1;
                            }
                        }
                        byte bVar1 = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[playerID];
                        if ((DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[playerID_01] != bVar1)
                            || (DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[playerID_01] == 0)) {
                            if (!bVar1) {
                                bVar1 = 0;
                                if (('\0' < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[1])
                                    && ('\0' < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[1])) {
                                    bVar1 = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[1];
                                }
                                if ('\0' < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[2]
                                    && (char)bVar1 < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[2]) {
                                    bVar1 = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[2];
                                }
                                if ('\0' < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[3]
                                    && (char)bVar1 < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[3]) {
                                    bVar1 = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[3];
                                }
                                if ('\0' < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[4]
                                    && (char)bVar1 < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[4]) {
                                    bVar1 = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[4];
                                }
                                if ('\0' < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[5]
                                    && (char)bVar1 < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[5]) {
                                    bVar1 = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[5];
                                }
                                if ('\0' < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[6]
                                    && (char)bVar1 < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[6]) {
                                    bVar1 = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[6];
                                }
                                if ('\0' < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[7]
                                    && (char)bVar1 < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[7]) {
                                    bVar1 = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[7];
                                }
                                if ('\0' < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[8]
                                    && (char)bVar1 < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[8]) {
                                    bVar1 = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[8];
                                }
                                DAT_GameSynchronyState::instance
                                    .DAT_PlayerGroupArray[(char)DAT_GameSynchronyState::instance
                                            .DAT_RoundTableOrderArray[DAT_00df423c::instance]] = bVar1 + 1;
                                DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[DAT_GameSynchronyState::instance
                                        .DAT_RoundTableOrderArray[param_1 - 10]] = bVar1 + 1;
                                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::scheduleSFXVariation, DAT_SFXState::ptr)(
                                    7, 1);
                                BVar3 = MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::shouldSoundXNotBePlaying,
                                    DAT_SoundSystemState::ptr)();
                                if (!BVar3 && 2 < iVar4 && DAT_GameCore::instance.genieVoiceActive) {
                                    MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                                    switch ((int)SEC_RNG::instance.currentNumber1 % 7) {
                                    case 0:
                                        /*
                                          "We will be invincible"
                                         */
                                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                            "genie_05.wav");
                                        break;
                                    case 1:
                                        /*
                                          "A worthy ally"
                                         */
                                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                            "genie_06.wav");
                                        break;
                                    case 2:
                                        /*
                                          "Watch my back"
                                         */
                                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                            "genie_07.wav");
                                        break;
                                    case 3:
                                        /*
                                          "Yeeees"
                                         */
                                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                            "genie_08.wav");
                                        break;
                                    case 4:
                                        /*
                                          "On my honour"
                                         */
                                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                            "genie_09.wav");
                                        break;
                                    case 5:
                                        /*
                                          "We rule"
                                         */
                                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                            "genie_10.wav");
                                        break;
                                    case 6:
                                        /*
                                          "I pledge allegiance"
                                         */
                                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                            "genie_04.wav");
                                    }
                                }
                            } else {
                                DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[playerID_01] = bVar1;
                                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::scheduleSFXVariation, DAT_SFXState::ptr)(
                                    7, 1);
                            }
                        }
                    }
                    if ((param_1 + -10 == DAT_00df423c::instance) && (!INT_00df4244::instance)) {
                        INT_00df4244::instance = 1;
                    } else {
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions,
                            DAT_GameSynchronyState::ptr)();
                        DAT_00df423c::instance = 0;
                    }
                }
                if (param_1 == 0x15) {
                    if ((DAT_00df423c::instance)
                        && (DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[DAT_00df423c::instance] != 0)) {
                        DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[(
                            char)DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[DAT_00df423c::instance]] = 0;
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions,
                            DAT_GameSynchronyState::ptr)();
                        DAT_00df423c::instance = 0;
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::scheduleSFXVariation, DAT_SFXState::ptr)(7, 0);
                    }
                } else if (param_1 == 100) {
                    DAT_MenuModalComposition1::instance.activeModalDialogID = UI::Enums::MMT_NONE;
                    MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                    MACRO_CALL_MEMBER(
                        Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions, DAT_GameSynchronyState::ptr)();
                    char cVar2 = '\0' < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[1];
                    if ('\0' < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[2]) {
                        cVar2 = cVar2 + '\x01';
                    }
                    if ('\0' < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[3]) {
                        cVar2 = cVar2 + '\x01';
                    }
                    if ('\0' < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[4]) {
                        cVar2 = cVar2 + '\x01';
                    }
                    if ('\0' < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[5]) {
                        cVar2 = cVar2 + '\x01';
                    }
                    if ('\0' < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[6]) {
                        cVar2 = cVar2 + '\x01';
                    }
                    if ('\0' < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[7]) {
                        cVar2 = cVar2 + '\x01';
                    }
                    if ('\0' < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[8]) {
                        cVar2 = cVar2 + '\x01';
                    }
                    if (cVar2 != '\0') {
                        /*
                          "The sides are drawn"
                         */
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)("Genie_02.wav");
                    }
                } else {
                    if (param_1 == 0x65) {
                        DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[0]
                            = DAT_GameSynchronyState::instance.playerGroupArray2Unk[0];
                        DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[1]
                            = DAT_GameSynchronyState::instance.playerGroupArray2Unk[1];
                        DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[2]
                            = DAT_GameSynchronyState::instance.playerGroupArray2Unk[2];
                        DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[3]
                            = DAT_GameSynchronyState::instance.playerGroupArray2Unk[3];
                        DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[4]
                            = DAT_GameSynchronyState::instance.playerGroupArray2Unk[4];
                        DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[5]
                            = DAT_GameSynchronyState::instance.playerGroupArray2Unk[5];
                        DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[6]
                            = DAT_GameSynchronyState::instance.playerGroupArray2Unk[6];
                        DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[7]
                            = DAT_GameSynchronyState::instance.playerGroupArray2Unk[7];
                        DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[8]
                            = DAT_GameSynchronyState::instance.playerGroupArray2Unk[8];
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions,
                            DAT_GameSynchronyState::ptr)();
                        DAT_MenuModalComposition1::instance.activeModalDialogID = UI::Enums::MMT_NONE;
                        MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions,
                            DAT_GameSynchronyState::ptr)();
                    }
                    if (param_1 == 200) {
                        if (DAT_00df423c::instance) {
                            DAT_00df423c::instance = 0;
                        }
                    } else if (((param_1 == 0xc9) || (param_1 == 0xca)) && DAT_00df423c::instance
                        && (INT_00df4244::instance != 1 || (param_1 == 0xc9))) {
                        DAT_00df423c::instance = 0;
                    }
                }
            }
        }

    }
}
}
