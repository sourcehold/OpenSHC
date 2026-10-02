#include "../GameLost.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Game/Skirmish.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/UI/Enums/BuildMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_00eb9af8.hpp"
#include "OpenSHC/Globals/DAT_00ec082c.hpp"
#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_FinalResultsOrderByColumn.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition3.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/DWORD_00ed27b4.hpp"
#include "OpenSHC/Globals/INT_00eb0e44.hpp"
#include "OpenSHC/Globals/INT_00ed279c.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::Game::GameMode;
        using OpenSHC::Game::GameMode2;
        using OpenSHC::Rendering::ScreenResolutionEnum;
        using OpenSHC::UI::Enums::BuildMenuTabType;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "UnsortedBinkFlagInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004D55D0
        void GameLost::MenuView_GameLost_Prepare()
        {
            Menu* pMVar1;
            DWORD DVar2;
            int iVar3;
            int xPos;
            char* binkFileName;
            DVar2 = timeGetTime();
            DAT_GameCore::instance.gameDuration = DVar2 - DAT_GameCore::instance.timeSum_2;
            INT_00ed279c::instance = 0;
            DAT_FinalResultsOrderByColumn::instance = 0;
            DAT_00eb9af8::instance = 0;
            *(char*)&INT_00eb0e44::instance = 0;
            DAT_VideoBikQueue::instance.storedMessages_0x924 = 0;
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                DAT_MenuModalComposition2::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                DAT_MenuModalComposition3::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
                DAT_GameCore::instance.activeMenuTab.buildMenuTab = ((BuildMenuTabType)0);
                DAT_00ec082c::instance = 0;
            } else {
                DAT_GameCore::instance.activeMenuTab.buildMenuTab = ((BuildMenuTabType)2);
                DAT_00ec082c::instance = 2;
            }
            MACRO_CALL(OpenSHC::Game::Skirmish_Func::StoreLocalTime)();
            DWORD_00ed27b4::instance = 0;
            MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::setupLossMusic, DAT_SoundSystemState::ptr)();
            DAT_MenuHandlerState::instance.y = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            DAT_MenuHandlerState::instance.x = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            pMVar1 = DAT_MenuHandlerState::instance.currentMenu;
            (DAT_MenuHandlerState::instance.currentMenu)->xPosition
                = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            pMVar1->yPosition = DAT_MenuHandlerState::instance.y;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(0,
                0, DAT_WindowAndDirectDraw::instance.resolutionX, DAT_WindowAndDirectDraw::instance.resolutionY,
                (ushort)((int)(COL_BLACK::instance.shortValue)));
            if (DAT_GameSynchronyState::instance.currentGameMode
                == OpenSHC::Game::GM_SKIRMISH_END_OF_GAME_SINGLE_PLAYER)
                goto LAB_004d575f;
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION) {
                if (DAT_GameCore::instance.missionNumber1to20 - 6U < 5) {
                    iVar3 = DAT_MenuHandlerState::instance.y + 0x3c;
                    xPos = DAT_MenuHandlerState::instance.x + 0x50;
                    binkFileName = "arabian_lose.bik";
                } else {
                LAB_004d574d:
                    iVar3 = DAT_MenuHandlerState::instance.y + 0x3c;
                    xPos = DAT_MenuHandlerState::instance.x + 0x50;
                    binkFileName = "crusader_lose.bik";
                }
            } else {
                iVar3 = MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::getLordTypeForPlayer,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
                if (iVar3 != 1)
                    goto LAB_004d574d;
                iVar3 = DAT_MenuHandlerState::instance.y + 0x3c;
                xPos = DAT_MenuHandlerState::instance.x + 0x50;
                binkFileName = "arabian_lose.bik";
            }
            MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::playBINK, DAT_BinkControlState::ptr)(
                0, binkFileName, 0, 0, xPos, iVar3, 2);
        LAB_004d575f:
            MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadTGX_shc_back)();
            DAT_MenuTextInputState::instance.DAT_SomeTextArrayIndex = 9;
            MACRO_CALL_MEMBER(
                OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
        }

    }
}
}
