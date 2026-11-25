#include "../InGameMenu.func.hpp"

#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/ScrollingHandler.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"

#include "OpenSHC/Globals/DAT_CurrentFramerate.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_ScrollingHandler.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00434120
        void InGameMenu::MenuItemActionHandler_InGameMenu_Scrolling()
        {
            if (!MACRO_CALL(OpenSHC::UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                    OpenSHC::UI::Enums::DEID_DEBUG_NUMBERS)) {
                // element state -1000 updates the frame rate below without drawing the debug numbers
                MACRO_CALL(OpenSHC::UI::DisplayElements_Func::RenderDebugNumbersDisplayElement)(0, 0, -1000);
            }
            if (DAT_MouseState::instance.selectionBoxMode != 0) {
                return;
            }
            if (DAT_MouseState::instance.rightClickState) {
                return;
            }
            int scrollDistance = MACRO_CALL_MEMBER(
                OpenSHC::UI::ScrollingHandler_Func::getScrollDistanceBaseUnk, DAT_ScrollingHandler::ptr)();
            if (scrollDistance == 0) {
                return;
            }
            // below the game speed's frame rate the step grows by speed / ((speed + frame rate) / 2), making up for
            // part of the slowdown
            if (DAT_CurrentFramerate::instance < DAT_GameCore::instance.gameSpeedLevel
                && DAT_CurrentFramerate::instance != 0) {
                scrollDistance = DAT_GameCore::instance.gameSpeedLevel * scrollDistance
                    / ((DAT_GameCore::instance.gameSpeedLevel - DAT_CurrentFramerate::instance) / 2
                        + DAT_CurrentFramerate::instance);
            }
            switch (DAT_ScrollingHandler::instance.scrollDirection_0x4) {
            case OpenSHC::UI::SD_UP:
                DAT_ViewportRenderState::instance.viewportState.viewportY -= scrollDistance;
                break;
            case OpenSHC::UI::SD_UP_RIGHT:
                DAT_ViewportRenderState::instance.viewportState.viewportY -= scrollDistance;
                // falls through to the step right
            case OpenSHC::UI::SD_RIGHT:
                DAT_ViewportRenderState::instance.viewportState.viewportX += scrollDistance;
                break;
            case OpenSHC::UI::SD_DOWN_RIGHT:
                DAT_ViewportRenderState::instance.viewportState.viewportY += scrollDistance;
                DAT_ViewportRenderState::instance.viewportState.viewportX += scrollDistance;
                break;
            case OpenSHC::UI::SD_DOWN:
                DAT_ViewportRenderState::instance.viewportState.viewportY += scrollDistance;
                break;
            case OpenSHC::UI::SD_DOWN_LEFT:
                DAT_ViewportRenderState::instance.viewportState.viewportY += scrollDistance;
                DAT_ViewportRenderState::instance.viewportState.viewportX -= scrollDistance;
                break;
            case OpenSHC::UI::SD_UP_LEFT:
                DAT_ViewportRenderState::instance.viewportState.viewportY -= scrollDistance;
                // falls through to the step left
            case OpenSHC::UI::SD_LEFT:
                DAT_ViewportRenderState::instance.viewportState.viewportX -= scrollDistance;
                break;
            }
            MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize,
                DAT_ViewportRenderState::ptr)();
            // tutorial action 1: the player scrolled the view
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL) {
                MACRO_CALL(OpenSHC::UI::Helpers_Func::RecordTutorialPlayerAction)(1);
            }
        }

    }
}
}
