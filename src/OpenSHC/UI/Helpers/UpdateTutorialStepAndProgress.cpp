#include "../Helpers.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/IO.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuItems/TutorialBox.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00df5540.hpp"
#include "OpenSHC/Globals/DAT_00df5544.hpp"
#include "OpenSHC/Globals/DAT_00df5558.hpp"
#include "OpenSHC/Globals/DAT_00df555c.hpp"
#include "OpenSHC/Globals/DAT_00df5560.hpp"
#include "OpenSHC/Globals/DAT_00df5564.hpp"
#include "OpenSHC/Globals/DAT_00df556c.hpp"
#include "OpenSHC/Globals/DAT_00df5588.hpp"
#include "OpenSHC/Globals/DAT_00df558c.hpp"
#include "OpenSHC/Globals/DAT_00df5590.hpp"
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
#include "OpenSHC/Globals/INT_00df5574.hpp"
#include "OpenSHC/Globals/INT_00df557c.hpp"
#include "OpenSHC/Globals/INT_00df5580.hpp"
#include "OpenSHC/Globals/INT_00df5584.hpp"
#include "OpenSHC/Globals/INT_00df5650.hpp"
#include "OpenSHC/Globals/INT_00df5654.hpp"
#include "OpenSHC/Globals/INT_DisableTutorialRestrictions.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"
#include "OpenSHC/Globals/TUT_RotateMapHappened.hpp"

namespace OpenSHC {
namespace UI {

    using Audio::MSS::enums::SHC_SoundStream;
    using Commands::MappersEnum;
    using UI::Enums::BuildingsAndStatusMenuTabType;
    using UI::Enums::MenuModalType;
    using UI::Enums::MenuViewType;
    using WindowsHelper::Enums::BOOLEnum;

    /*
      Main per-frame tutorial update function. Manages the tutorial modal dialog (MMT_TUTORIAL_BOX /
      MMT_TUTORIAL_BOX_WITH_LEAVE), plays step speech audio with delay, handles step transition   fade-in/out via
      DAT_00df5540 state machine, advances DAT_TutorialCurrentStep on completion,   evaluates per-step completion
      conditions against recorded player actions (DAT_00df5588,   TUT_RotateMapHappened, etc.), sets DAT_00df5560 when
      the step condition is met, and calls   MenuItemActionHandler_TutorialBox_Main(1) to show the continue button.
      renamed by: Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004BD1B0
    void Helpers::UpdateTutorialStepAndProgress()
    {
        DWORD DVar1;
        uint uVar4;
        BOOLEnum BVar2;
        bool bVar5;
        MenuModalType menuModalID;
        int local_48;
        char local_44[32];
        char local_24[32];
        uint local_4 = MSVC_SecurityCookie::instance ^ (uint)&local_48;
        local_48 = DAT_00df5560::instance;
        if (INT_DisableTutorialRestrictions::instance
            && DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_TUTORIAL_BOX
            && DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_TUTORIAL_BOX_WITH_LEAVE)
            goto LAB_004bd764;
        DWORD _now = timeGetTime();
        if (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_NONE) {
            if (DAT_TutorialCurrentStep::instance == 0x1f) {
                menuModalID = UI::Enums::MMT_TUTORIAL_BOX_WITH_LEAVE;
            } else {
                menuModalID = UI::Enums::MMT_TUTORIAL_BOX;
            }
            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
                menuModalID, FALSE);
        }
        int iVar3 = DAT_00df5558::instance + DAT_TutorialCurrentStep::instance * 4;
        if (iVar3 != INT_00df5654::instance) {
            INT_00df5650::instance = 0;
            INT_00df5654::instance = iVar3;
            DWORD_00df564c::instance = timeGetTime();
        }
        if (!INT_00df5650::instance && 0 < DAT_00df5558::instance && DAT_00df5558::instance < DAT_00df555c::instance
            && (DVar1 = timeGetTime(), 1000 < DVar1 - DWORD_00df564c::instance)) {
            INT_00df5650::instance = 1;
            MACRO_CALL(OS_Func::_sprintf)(local_44, "%s%s", "fx\\speech\\",
                (DAT_00df5558::instance + DAT_TutorialCurrentStep::instance * 3) * 32 + 0xb3d810);
            BVar2 = MACRO_CALL(IO_Func::FileExists)(local_44);
            if (BVar2) {
                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::playAmbientStreamWithLoop, DAT_SoundSystemState::ptr)(
                    local_44);
            }
        }
        if ((DAT_00df5564::instance) && (1000 < _now - DWORD_00df5568::instance)) {
            DAT_00df5564::instance = 0;
        }
        if (!DAT_FileDoesntExist::instance && (!DAT_00df5558::instance || (INT_00df5650::instance))
            && !DAT_00df5540::instance) {
            uVar4 = DAT_00df5544::instance;
            if (DAT_00df5558::instance < DAT_00df555c::instance + -1) {
                BVar2 = MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::isSampleOrStreamPlaying,
                    DAT_SoundSystemState::ptr)(Audio::MSS::enums::SND_STR_SPEECH_1);
                if (!BVar2
                    && (BVar2 = MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::isSampleOrStreamPlaying,
                            DAT_SoundSystemState::ptr)(Audio::MSS::enums::SND_STR_SPEECH_2),
                        !BVar2)
                    && DAT_SoundSystemState::instance.waveOutOpenUnk_0x8
                    && DAT_SoundSystemState::instance.soundActiveUnk_0x0) {
                    MACRO_CALL(UI::MenuItems::TutorialBox_Func::MenuItemActionHandler_TutorialBox_Main)(1);
                }
                goto LAB_004bd354;
            }
        LAB_004bd3e9:
            DAT_00df5544::instance = uVar4;
            if (DAT_00df5560::instance)
                goto LAB_004bd764;
        } else {
        LAB_004bd354:
            if (DAT_00df5540::instance == 1) {
                uVar4 = _now - DWORD_00df5548::instance >> 5;
                if (uVar4 < 0x20) {
                    uVar4 = 0x1f - uVar4;
                } else {
                    MACRO_CALL(OS_Func::_sprintf)(
                        local_44, "%s%s", "fx\\speech\\", DAT_TutorialCurrentStep::instance * 96 + 0xb3d810);
                    BVar2 = MACRO_CALL(IO_Func::FileExists)(local_44);
                    if (BVar2) {
                        MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::playAmbientStreamWithLoop,
                            DAT_SoundSystemState::ptr)(local_44);
                    }
                    DAT_00df5540::instance = 0;
                    uVar4 = DAT_00df5544::instance;
                }
                goto LAB_004bd3e9;
            }
            uVar4 = DAT_00df5544::instance;
            if (DAT_00df5540::instance != 2)
                goto LAB_004bd3e9;
            uVar4 = _now - DWORD_00df5548::instance >> 5;
            if (!uVar4) {
                uVar4 = 1;
                goto LAB_004bd3e9;
            }
            if (uVar4 < 0x20)
                goto LAB_004bd3e9;
            DAT_TutorialCurrentStep::instance = DAT_TutorialCurrentStep::instance + 1;
            if (INT_DisableTutorialRestrictions::instance) {
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
                    UI::Enums::MMT_NONE, FALSE);
                uVar4 = DAT_00df5544::instance;
                goto LAB_004bd3e9;
            }
            if (DAT_TutorialCurrentStep::instance == 0x1f) {
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
                    UI::Enums::MMT_NONE, FALSE);
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
                    UI::Enums::MMT_TUTORIAL_BOX_WITH_LEAVE, FALSE);
            }
            MACRO_CALL(UI::Helpers_Func::InitTutorialStepTransition)(1);
            MACRO_CALL(UI::Helpers_Func::ResetTutorialActionTrackers)();
            DAT_00df555c::instance
                = DAT_MissionAestheticsDefinedData::instance.TutorialStepActionCount[DAT_TutorialCurrentStep::instance];
            DAT_00df5560::instance = 0;
            DAT_00df5558::instance = 0;
        }
        if ((INT_DisableTutorialRestrictions::instance) || (DAT_00df5540::instance == 2))
            goto LAB_004bd764;
        switch (DAT_TutorialCurrentStep::instance) {
        case 1:
            iVar3 = INT_00df5574::instance;
            goto joined_r0x004bd699;
        case 2:
            if (!DAT_00df5558::instance) {
                bVar5 = DAT_00df5588::instance == 6;
            } else {
                iVar3 = DAT_00df5558::instance;
                if (DAT_00df5558::instance != 1)
                    goto joined_r0x004bd6ad;
                bVar5 = DAT_00df5588::instance == 7;
            }
            if (bVar5) {
                bVar5 = DAT_00df558c::instance == 0x28;
                goto LAB_004bd6bb;
            }
            break;
        case 5:
            if (!DAT_00df5558::instance) {
                if (DAT_00df5588::instance != 6) {
                    bVar5 = DAT_00df5588::instance == 7;
                    goto LAB_004bd514;
                }
                if (DAT_00df558c::instance == 0x13) {
                    DAT_00df5590::instance = 1;
                }
            } else {
            joined_r0x004bd57e:
                if (0 < DAT_00df5558::instance)
                    goto switchD_004bd41e_caseD_0;
            }
            break;
        case 6:
        case 0x13:
            bVar5 = DAT_00df5588::instance == 8;
        LAB_004bd514:
            if (bVar5) {
                bVar5 = DAT_00df558c::instance == 0x13;
                goto LAB_004bd6bb;
            }
            break;
        case 8:
            if (DAT_00df5558::instance)
                goto joined_r0x004bd57e;
            if (DAT_00df5588::instance == 0xc) {
                bVar5 = DAT_00df558c::instance == 4;
                goto LAB_004bd6bb;
            }
            break;
        case 9:
            if (DAT_00df5558::instance)
                goto joined_r0x004bd57e;
            if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU) {
                bVar5 = DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_KEEP_OR_MPMENU_IPX;
                goto LAB_004bd6bb;
            }
            break;
        case 10:
            if (DAT_00df5588::instance == 0xd) {
                bVar5 = DAT_00df558c::instance == 7;
                goto LAB_004bd6bb;
            }
            break;
        case 0xb:
            if (DAT_00df5558::instance != 1)
                goto switchD_004bd41e_caseD_0;
            if (DAT_00df5588::instance == 0xe) {
                DAT_00df5560::instance = 1;
            }
            if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU) {
                bVar5 = DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_STATUS_OVERVIEW;
                goto LAB_004bd6bb;
            }
            break;
        case 0xc:
            if ((DAT_00df5588::instance == 0xf) && (DAT_00df558c::instance == 0x48)) {
                DAT_00df5560::instance = 1;
            }
            if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU) {
                bVar5 = DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_STATUS_POPULARITY;
                goto LAB_004bd6bb;
            }
            break;
        case 0xe:
        case 0x14:
            if (DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_BUILDING_AND_STATUS_MENU) {
                DAT_00df5560::instance = 1;
            }
            bVar5 = DAT_00df5588::instance == 0xb;
        LAB_004bd6bb:
            if (bVar5)
                goto switchD_004bd41e_caseD_0;
            break;
        case 0x11:
            if ((DAT_00df5588::instance == 7) && (DAT_00df558c::instance == 3)) {
                DAT_00df5590::instance = DAT_00df5590::instance + 1;
                DAT_00df5588::instance = 0;
            }
            if (DAT_TileMapState::instance.currentMapperCommand == Commands::M_MAPPER_NULL) {
                bVar5 = DAT_00df5590::instance == 4;
                goto LAB_004bd6bb;
            }
            break;
        case 0x15:
            if ((DAT_00df5588::instance == 7) && (DAT_00df558c::instance == 7)) {
                DAT_00df5590::instance = DAT_00df5590::instance + 1;
                DAT_00df5588::instance = 0;
                bVar5 = DAT_00df5590::instance == 4;
                goto LAB_004bd6bb;
            }
            break;
        case 0x18:
            if (DAT_00df5588::instance == 7) {
                bVar5 = DAT_00df558c::instance == 1;
                goto LAB_004bd6bb;
            }
            break;
        case 0x1b:
            iVar3 = TUT_RotateMapHappened::instance;
        joined_r0x004bd699:
            /*
              hold right click to show extra interface controls
             */
            if (iVar3)
                goto switchD_004bd41e_caseD_0;
            break;
        case 0x1c:
            iVar3 = INT_00df557c::instance;
            goto joined_r0x004bd6ad;
        case 0x1d:
            iVar3 = INT_00df5584::instance;
        joined_r0x004bd6ad:
            if (1 < iVar3)
                goto switchD_004bd41e_caseD_0;
            break;
        case 0x1e:
            if (DAT_00df5558::instance == 1) {
                bVar5 = INT_00df5580::instance == 2;
                goto LAB_004bd6bb;
            }
        case 0:
        case 3:
        case 4:
        case 7:
        case 0xd:
        case 0xf:
        case 0x10:
        case 0x12:
        case 0x16:
        case 0x17:
        case 0x19:
        case 0x1a:
        case 0x1f:
        case 0x20:
        switchD_004bd41e_caseD_0:
            DAT_00df5560::instance = 1;
        }
        if (!local_48) {
            if (!DAT_00df5560::instance)
                goto LAB_004bd764;
            if (DAT_MissionAestheticsDefinedData::instance.TutorialStepSpeechTrigger[DAT_TutorialCurrentStep::instance]
                == 2) {
                iVar3 = DAT_00df556c::instance * 0x60;
                DAT_00df556c::instance = DAT_00df556c::instance + 1;
                MACRO_CALL(OS_Func::_sprintf)(local_24, "%s%s", "fx\\speech\\", iVar3 + 0xb3d810);
                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::playAmbientStreamWithLoop, DAT_SoundSystemState::ptr)(
                    local_24);
                if (0x27 < DAT_00df556c::instance) {
                    DAT_00df556c::instance = 0x24;
                }
            }
        }
        if (DAT_00df5560::instance
            && DAT_MissionAestheticsDefinedData::instance
                    .TutorialStepShowsContinueButton[DAT_TutorialCurrentStep::instance]
                != 0
            && DAT_00df555c::instance + -1 <= DAT_00df5558::instance) {
            /*
              show continue button?
             */
            MACRO_CALL(UI::MenuItems::TutorialBox_Func::MenuItemActionHandler_TutorialBox_Main)(1);
        }
    LAB_004bd764:;
        return;
    }

}
}
