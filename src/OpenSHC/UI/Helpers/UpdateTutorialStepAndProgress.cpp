#include "../Helpers.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/IO.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuItems/TutorialBox.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_00df5540.hpp"
#include "OpenSHC/Globals/DAT_00df5544.hpp"
#include "OpenSHC/Globals/DAT_00df5558.hpp"
#include "OpenSHC/Globals/DAT_00df555c.hpp"
#include "OpenSHC/Globals/DAT_00df5560.hpp"
#include "OpenSHC/Globals/DAT_00df556c.hpp"
#include "OpenSHC/Globals/DAT_00df5588.hpp"
#include "OpenSHC/Globals/DAT_00df558c.hpp"
#include "OpenSHC/Globals/DAT_00df5590.hpp"
#include "OpenSHC/Globals/DAT_DisableTutorialRestrictions.hpp"
#include "OpenSHC/Globals/DAT_FileDoesntExist.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TutorialCurrentStep.hpp"
#include "OpenSHC/Globals/DWORD_00df5548.hpp"
#include "OpenSHC/Globals/DWORD_00df5568.hpp"
#include "OpenSHC/Globals/DWORD_00df564c.hpp"
#include "OpenSHC/Globals/INT_00df5564.hpp"
#include "OpenSHC/Globals/INT_00df5574.hpp"
#include "OpenSHC/Globals/INT_00df557c.hpp"
#include "OpenSHC/Globals/INT_00df5580.hpp"
#include "OpenSHC/Globals/INT_00df5584.hpp"
#include "OpenSHC/Globals/INT_00df5650.hpp"
#include "OpenSHC/Globals/INT_00df5654.hpp"
#include "OpenSHC/Globals/TUT_RotateMapHappened.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004BD1B0
    void Helpers::UpdateTutorialStepAndProgress()
    {
        int const wasComplete = DAT_00df5560::instance;
        if (DAT_DisableTutorialRestrictions::instance
            && DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_TUTORIAL_BOX
            && DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_TUTORIAL_BOX_WITH_LEAVE) {
            return;
        }
        DWORD const now = timeGetTime();
        if (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_NONE) {
            if (DAT_TutorialCurrentStep::instance == 31) {
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
                    UI::Enums::MMT_TUTORIAL_BOX_WITH_LEAVE, FALSE);
            } else {
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
                    UI::Enums::MMT_TUTORIAL_BOX, FALSE);
            }
        }

        // A new action of the step restarts the one-second delay before its speech.
        int const actionKey = DAT_00df5558::instance + DAT_TutorialCurrentStep::instance * 4;
        if (actionKey != INT_00df5654::instance) {
            INT_00df5654::instance = actionKey;
            INT_00df5650::instance = 0;
            DWORD_00df564c::instance = timeGetTime();
        }
        char speechPath[32];
        if (!INT_00df5650::instance && DAT_00df5558::instance > 0 && DAT_00df5558::instance < DAT_00df555c::instance
            && timeGetTime() - DWORD_00df564c::instance > 1000) {
            INT_00df5650::instance = 1;
            // "%s%s", "fx\\speech\\"
            MACRO_CALL(OS_Func::_sprintf)(speechPath, s__s_s_005aa800, s_fx_speech__005a64cc,
                DAT_MissionAestheticsDefinedData::instance
                    .field_0x41e4[DAT_TutorialCurrentStep::instance][DAT_00df5558::instance]);
            if (MACRO_CALL(IO_Func::FileExists)(speechPath)) {
                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::playAmbientStreamWithLoop, DAT_SoundSystemState::ptr)(
                    speechPath);
            }
        }
        if (INT_00df5564::instance && now - DWORD_00df5568::instance > 1000) {
            INT_00df5564::instance = 0;
        }
        if (!DAT_FileDoesntExist::instance && (DAT_00df5558::instance == 0 || INT_00df5650::instance)
            && DAT_00df5540::instance == 0 && DAT_00df5558::instance < DAT_00df555c::instance - 1) {
            if (!MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::isSampleOrStreamPlaying, DAT_SoundSystemState::ptr)(
                    Audio::MSS::enums::SND_STR_SPEECH_1)
                && !MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::isSampleOrStreamPlaying, DAT_SoundSystemState::ptr)(
                    Audio::MSS::enums::SND_STR_SPEECH_2)
                && DAT_SoundSystemState::instance.waveOutOpenUnk_0x8
                && DAT_SoundSystemState::instance.soundActiveUnk_0x0) {
                MACRO_CALL(UI::MenuItems::TutorialBox_Func::MenuItemActionHandler_TutorialBox_Main)(1);
            }
        }

        // The step transition: 1 fades the box in and then plays the step's speech, 2 fades it out and then moves
        // on to the next step.
        if (DAT_00df5540::instance == 1) {
            DWORD const fade = (now - DWORD_00df5548::instance) / 32;
            if (fade >= 32) {
                // "%s%s", "fx\\speech\\"
                MACRO_CALL(OS_Func::_sprintf)(speechPath, s__s_s_005aa800, s_fx_speech__005a64cc,
                    DAT_MissionAestheticsDefinedData::instance.field_0x41e4[DAT_TutorialCurrentStep::instance][0]);
                if (MACRO_CALL(IO_Func::FileExists)(speechPath)) {
                    MACRO_CALL_MEMBER(
                        Audio::MSS::SoundSystem_Func::playAmbientStreamWithLoop, DAT_SoundSystemState::ptr)(speechPath);
                }
                DAT_00df5540::instance = 0;
            } else {
                DAT_00df5544::instance = 31 - fade;
            }
        } else if (DAT_00df5540::instance == 2) {
            DWORD fade = (now - DWORD_00df5548::instance) / 32;
            if (fade < 1) {
                fade = 1;
            }
            if (fade >= 32) {
                ++DAT_TutorialCurrentStep::instance;
                if (DAT_DisableTutorialRestrictions::instance) {
                    MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NONE, FALSE);
                } else {
                    if (DAT_TutorialCurrentStep::instance == 31) {
                        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NONE, FALSE);
                        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_TUTORIAL_BOX_WITH_LEAVE, FALSE);
                    }
                    MACRO_CALL(UI::Helpers_Func::InitTutorialStepTransition)(1);
                    MACRO_CALL(UI::Helpers_Func::ResetTutorialActionTrackers)();
                    DAT_00df5560::instance = 0;
                    DAT_00df5558::instance = 0;
                    DAT_00df555c::instance = DAT_MissionAestheticsDefinedData::instance
                                                 .TutorialStepActionCount[DAT_TutorialCurrentStep::instance];
                }
            } else {
                DAT_00df5544::instance = fade;
            }
        }
        if (DAT_00df5560::instance) {
            return;
        }
        if (DAT_DisableTutorialRestrictions::instance || DAT_00df5540::instance == 2) {
            return;
        }

        // The step is done once the player has done what it asks for.
        switch (DAT_TutorialCurrentStep::instance) {
        case 1:
            if (INT_00df5574::instance) {
                DAT_00df5560::instance = 1;
            }
            break;
        case 2:
            if (DAT_00df5558::instance == 0) {
                if (DAT_00df5588::instance == 6 && DAT_00df558c::instance == 40) {
                    DAT_00df5560::instance = 1;
                }
            } else if (DAT_00df5558::instance == 1) {
                if (DAT_00df5588::instance == 7 && DAT_00df558c::instance == 40) {
                    DAT_00df5560::instance = 1;
                }
            } else if (DAT_00df5558::instance > 1) {
                DAT_00df5560::instance = 1;
            }
            break;
        case 5:
            if (DAT_00df5558::instance == 0) {
                if (DAT_00df5588::instance == 6) {
                    if (DAT_00df558c::instance == 19) {
                        DAT_00df5590::instance = 1;
                    }
                } else if (DAT_00df5588::instance == 7 && DAT_00df558c::instance == 19) {
                    DAT_00df5560::instance = 1;
                }
            } else if (DAT_00df5558::instance > 0) {
                DAT_00df5560::instance = 1;
            }
            break;
        case 6:
        case 19:
            if (DAT_00df5588::instance == 8 && DAT_00df558c::instance == 19) {
                DAT_00df5560::instance = 1;
            }
            break;
        case 8:
            if (DAT_00df5558::instance == 0) {
                if (DAT_00df5588::instance == 12 && DAT_00df558c::instance == 4) {
                    DAT_00df5560::instance = 1;
                }
            } else if (DAT_00df5558::instance > 0) {
                DAT_00df5560::instance = 1;
            }
            break;
        case 9:
            if (DAT_00df5558::instance == 0) {
                if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU
                    && DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_KEEP_OR_MPMENU_IPX) {
                    DAT_00df5560::instance = 1;
                }
            } else if (DAT_00df5558::instance > 0) {
                DAT_00df5560::instance = 1;
            }
            break;
        case 10:
            if (DAT_00df5588::instance == 13 && DAT_00df558c::instance == 7) {
                DAT_00df5560::instance = 1;
            }
            break;
        case 11:
            if (DAT_00df5558::instance != 1) {
                DAT_00df5560::instance = 1;
                break;
            }
            // Two ifs with the same body, as in the original.
            if (DAT_00df5588::instance == 14) {
                DAT_00df5560::instance = 1;
            }
            if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU
                && DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_STATUS_OVERVIEW) {
                DAT_00df5560::instance = 1;
            }
            break;
        case 12:
            // Two ifs with the same body, as in the original.
            if (DAT_00df5588::instance == 15 && DAT_00df558c::instance == 72) {
                DAT_00df5560::instance = 1;
            }
            if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU
                && DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_STATUS_POPULARITY) {
                DAT_00df5560::instance = 1;
            }
            break;
        case 14:
        case 20:
            // Two ifs with the same body, as in the original.
            if (DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_BUILDING_AND_STATUS_MENU) {
                DAT_00df5560::instance = 1;
            }
            if (DAT_00df5588::instance == 11) {
                DAT_00df5560::instance = 1;
            }
            break;
        case 17:
            if (DAT_00df5588::instance == 7 && DAT_00df558c::instance == 3) {
                ++DAT_00df5590::instance;
                DAT_00df5588::instance = 0;
            }
            if (DAT_TileMapState::instance.currentMapperCommand == Commands::M_MAPPER_NULL
                && DAT_00df5590::instance == 4) {
                DAT_00df5560::instance = 1;
            }
            break;
        case 21:
            if (DAT_00df5588::instance == 7 && DAT_00df558c::instance == 7) {
                DAT_00df5588::instance = 0;
                ++DAT_00df5590::instance;
                if (DAT_00df5590::instance == 4) {
                    DAT_00df5560::instance = 1;
                }
            }
            break;
        case 24:
            if (DAT_00df5588::instance == 7 && DAT_00df558c::instance == 1) {
                DAT_00df5560::instance = 1;
            }
            break;
        case 27:
            if (TUT_RotateMapHappened::instance != 0) {
                DAT_00df5560::instance = 1;
            }
            break;
        case 28:
            if (INT_00df557c::instance > 1) {
                DAT_00df5560::instance = 1;
            }
            break;
        case 29:
            if (INT_00df5584::instance > 1) {
                DAT_00df5560::instance = 1;
            }
            break;
        case 30:
            if (DAT_00df5558::instance != 1 || INT_00df5580::instance == 2) {
                DAT_00df5560::instance = 1;
            }
            break;
        // Separate bodies, as in the original: stacked labels give a two-level jump table.
        case 0:
            DAT_00df5560::instance = 1;
            break;
        case 3:
            DAT_00df5560::instance = 1;
            break;
        case 4:
            DAT_00df5560::instance = 1;
            break;
        case 7:
            DAT_00df5560::instance = 1;
            break;
        case 13:
            DAT_00df5560::instance = 1;
            break;
        case 15:
            DAT_00df5560::instance = 1;
            break;
        case 16:
            DAT_00df5560::instance = 1;
            break;
        case 18:
            DAT_00df5560::instance = 1;
            break;
        case 22:
            DAT_00df5560::instance = 1;
            break;
        case 23:
            DAT_00df5560::instance = 1;
            break;
        case 25:
            DAT_00df5560::instance = 1;
            break;
        case 26:
            DAT_00df5560::instance = 1;
            break;
        case 31:
            DAT_00df5560::instance = 1;
            break;
        case 32:
            DAT_00df5560::instance = 1;
            break;
        }

        if (!wasComplete) {
            if (!DAT_00df5560::instance) {
                return;
            }
            // A step that has just been completed may praise the player, cycling through speeches 36 to 39.
            if (DAT_MissionAestheticsDefinedData::instance.TutorialStepSpeechTrigger[DAT_TutorialCurrentStep::instance]
                == 2) {
                char praisePath[32];
                // "%s%s", "fx\\speech\\"
                MACRO_CALL(OS_Func::_sprintf)(praisePath, s__s_s_005aa800, s_fx_speech__005a64cc,
                    DAT_MissionAestheticsDefinedData::instance.field_0x41e4[DAT_00df556c::instance++][0]);
                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::playAmbientStreamWithLoop, DAT_SoundSystemState::ptr)(
                    praisePath);
                if (DAT_00df556c::instance > 39) {
                    DAT_00df556c::instance = 36;
                }
            }
        }
        // Show the continue button on the last action of a completed step.
        if (DAT_00df5560::instance
            && DAT_MissionAestheticsDefinedData::instance
                .TutorialStepShowsContinueButton[DAT_TutorialCurrentStep::instance]
            && DAT_00df5558::instance >= DAT_00df555c::instance - 1) {
            MACRO_CALL(UI::MenuItems::TutorialBox_Func::MenuItemActionHandler_TutorialBox_Main)(1);
        }
    }

}
}
