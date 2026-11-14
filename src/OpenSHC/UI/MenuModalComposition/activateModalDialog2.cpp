#include "../MenuModalComposition.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/UI/Rendering/WindowAndDirectDraw.func.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/DWORD_00df5534.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Enums::MenuModalType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004B2820
    void MenuModalComposition::activateModalDialog2(MenuModalType modalDialogID)
    {
        if (this->slot == 0 && DAT_MenuTextInputState::instance.currentModalDialog != OpenSHC::UI::Enums::MMT_NO_MENU) {
            MACRO_CALL_MEMBER(
                OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
        }
        if (this->activeModalDialogID == OpenSHC::UI::Enums::MMT_DISPLAY_AI_LORD_MESSAGE) {
            this->activeModalDialogID = OpenSHC::UI::Enums::MMT_NONE;
            if (MACRO_CALL_MEMBER(
                    OpenSHC::Rendering::Bink::AIMessageQueue_Func::playNextStoredAIMessage, DAT_VideoBikQueue::ptr)()) {
                return;
            }
        }
        this->activeModalDialogID = modalDialogID;
        if (modalDialogID != OpenSHC::UI::Enums::MMT_NONE) {
            // Makes found current. - TheRedDaemon
            memcpy(&this->modalMenu,
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::findModalMenu, this)(modalDialogID),
                sizeof(MenuModal));
        }
        this->modalDragDropUnk = 0;
        if ((this->modalMenu.borderStyle & 0x220) != 0) {
            // tiled frames come in whole 24x24 tiles
            this->modalMenu.width = ((this->modalMenu.width - 1) / 24 + 1) * 24;
            this->modalMenu.height = ((this->modalMenu.height - 1) / 24 + 1) * 24;
        }
        if (MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()) {
            if (this->modalMenu.x == -1) {
                this->modalMenu.x = DAT_WindowAndDirectDraw::instance.gameResolutionX / 2 - this->modalMenu.width / 2;
            } else {
                this->modalMenu.x += (DAT_WindowAndDirectDraw::instance.gameResolutionX - 800) / 2;
            }
            if (this->modalMenu.y == -1) {
                // centred over the map, above the 128 pixel high menu bar
                this->modalMenu.y
                    = (DAT_WindowAndDirectDraw::instance.gameResolutionY - 128) / 2 - this->modalMenu.height / 2;
            } else {
                this->modalMenu.y += (DAT_WindowAndDirectDraw::instance.gameResolutionY - 600) / 2;
            }
        } else {
            if (this->modalMenu.x == -1) {
                this->modalMenu.x = DAT_WindowAndDirectDraw::instance.gameResolutionX / 2 - this->modalMenu.width / 2;
            } else {
                this->modalMenu.x += (DAT_WindowAndDirectDraw::instance.gameResolutionX - 800) / 2;
            }
            if (this->modalMenu.y == -1) {
                this->modalMenu.y = DAT_WindowAndDirectDraw::instance.gameResolutionY / 2 - this->modalMenu.height / 2;
            } else {
                this->modalMenu.y += (DAT_WindowAndDirectDraw::instance.gameResolutionY - 600) / 2;
            }
        }
        this->disappearAfter = 32;
        this->mbr_0x6c = 0;
        this->timeItIsSet = timeGetTime();
        if ((this->modalMenu.borderStyle & 0x400) != 0) {
            this->disappearAfter = 0;
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::renderMenuModal, this)();
        if (30 < (int)(this->timeItIsSet - DWORD_00df5534::instance)) {
            DWORD_00df5534::instance = this->timeItIsSet;
            // show the dialog right away: blit its rectangle to the screen
            BOOLEnum const inGame
                = MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
            int x = this->modalMenu.x;
            int y = this->modalMenu.y;
            if (inGame) {
                x += DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX;
                y += DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY;
                DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::bltMapGameSurfaceToScreen,
                    DAT_WindowAndDirectDraw::ptr)(x, y, this->modalMenu.width + x, this->modalMenu.height + y);
                this->activeModalDialogID = OpenSHC::UI::Enums::MMT_NONE;
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::bltScreenMenuSurfaceToScreen,
                DAT_WindowAndDirectDraw::ptr)(x, y, this->modalMenu.width + x, this->modalMenu.height + y);
        }
        this->activeModalDialogID = OpenSHC::UI::Enums::MMT_NONE;
    }

}
}
