#include "../InGameMenu.func.hpp"

#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/ScrollingHandler.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_CurrentFramerate.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_ScrollingHandler.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Game::GameMode2;
        using OpenSHC::UI::Enums::DisplayElementID;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00434120
        void InGameMenu::MenuItemActionHandler_InGameMenu_Scrolling(int param_1, ...)
        {
            BOOLEnum _debugNumbersDisplayed;
            int _scrollDistance;
            _debugNumbersDisplayed = MACRO_CALL(OpenSHC::UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                OpenSHC::UI::Enums::DEID_DEBUG_NUMBERS);
            if (_debugNumbersDisplayed == FALSE) {
                /*
                  This call uses the function to compute the needed numbers, but the given   element state indicates to
                  not print the debug numbers. -TheRedDaemon
                 */
                MACRO_CALL(OpenSHC::UI::DisplayElements_Func::RenderDebugNumbersDisplayElement)(0, 0, 0xfffffc18);
            }
            if (DAT_MouseState::instance.selectionBoxMode != 0) {}
            if (DAT_MouseState::instance.rightClickState != FALSE) {}
            _scrollDistance = MACRO_CALL_MEMBER(
                OpenSHC::UI::ScrollingHandler_Func::getScrollDistanceBaseUnk, DAT_ScrollingHandler::ptr)();
            if (_scrollDistance == 0) {}
            if ((DAT_CurrentFramerate::instance < (int)DAT_GameCore::instance.gameSpeedLevel)
                && (DAT_CurrentFramerate::instance != 0)) {
                _scrollDistance = (int)(DAT_GameCore::instance.gameSpeedLevel * _scrollDistance)
                    / ((int)(DAT_GameCore::instance.gameSpeedLevel - DAT_CurrentFramerate::instance) / 2
                        + DAT_CurrentFramerate::instance);
            }
            switch (DAT_ScrollingHandler::instance.scrollDirection_0x4) {
            case SD_UP:
                DAT_ViewportRenderState::instance.viewportState.viewportY
                    = DAT_ViewportRenderState::instance.viewportState.viewportY - _scrollDistance;
                break;
            case SD_UP_RIGHT:
                DAT_ViewportRenderState::instance.viewportState.viewportY
                    = DAT_ViewportRenderState::instance.viewportState.viewportY - _scrollDistance;
            case SD_RIGHT:
                DAT_ViewportRenderState::instance.viewportState.viewportX
                    = DAT_ViewportRenderState::instance.viewportState.viewportX + _scrollDistance;
                break;
            case SD_DOWN_RIGHT:
                DAT_ViewportRenderState::instance.viewportState.viewportY
                    = DAT_ViewportRenderState::instance.viewportState.viewportY + _scrollDistance;
                DAT_ViewportRenderState::instance.viewportState.viewportX
                    = DAT_ViewportRenderState::instance.viewportState.viewportX + _scrollDistance;
                break;
            case SD_DOWN:
                DAT_ViewportRenderState::instance.viewportState.viewportY
                    = DAT_ViewportRenderState::instance.viewportState.viewportY + _scrollDistance;
                break;
            case SD_DOWN_LEFT:
                DAT_ViewportRenderState::instance.viewportState.viewportY
                    = DAT_ViewportRenderState::instance.viewportState.viewportY + _scrollDistance;
            case SD_LEFT:
            switchD_004341a6_caseD_6:
                DAT_ViewportRenderState::instance.viewportState.viewportX
                    = DAT_ViewportRenderState::instance.viewportState.viewportX - _scrollDistance;
                break;
            case SD_UP_LEFT:
                DAT_ViewportRenderState::instance.viewportState.viewportY
                    = DAT_ViewportRenderState::instance.viewportState.viewportY - _scrollDistance;
                goto switchD_004341a6_caseD_6;
            }
            MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize,
                DAT_ViewportRenderState::ptr)();
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL) {
                MACRO_CALL(OpenSHC::UI::Helpers_Func::RecordTutorialPlayerAction)(1);
            }
        }

    }
}
}
