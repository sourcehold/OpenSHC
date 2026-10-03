#include "../MenuModalComposition.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
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

    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::UI::Enums::MenuModalType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004B2820
    void MenuModalComposition::activateModalDialog2(MenuModalType modalDialogID)
    {
        BOOL _startedPlayingAIMessage;
        MenuModal* _modalMenu;
        BOOLEnum _areWeInAnInGameMenu;
        int iVar1;
        MenuModalComposition* pMVar2;
        int _y2;
        int _x2;
        if ((this->slot == 0)
            && (DAT_MenuTextInputState::instance.currentModalDialog != OpenSHC::UI::Enums::MMT_NO_MENU)) {
            MACRO_CALL_MEMBER(
                OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
        }
        if (this->activeModalDialogID == OpenSHC::UI::Enums::MMT_DISPLAY_AI_LORD_MESSAGE) {
            this->activeModalDialogID = OpenSHC::UI::Enums::MMT_NONE;
            _startedPlayingAIMessage = MACRO_CALL_MEMBER(
                OpenSHC::Rendering::Bink::AIMessageQueue_Func::playNextStoredAIMessage, DAT_VideoBikQueue::ptr)();
            if (_startedPlayingAIMessage != 0) {}
        }
        this->activeModalDialogID = modalDialogID;
        if (modalDialogID != OpenSHC::UI::Enums::MMT_NONE) {
            _modalMenu = MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::findModalMenu, this)(modalDialogID);
            pMVar2 = this;
            /*
              Makes found current. - TheRedDaemon
             */
            for (iVar1 = 10; pMVar2 = (MenuModalComposition*)&pMVar2->modalMenu, iVar1 != 0; iVar1 = iVar1 + -1) {
                ((MenuModal*)pMVar2)->menuModalID = _modalMenu->menuModalID;
                _modalMenu = (MenuModal*)&_modalMenu->x;
            }
        }
        this->modalDragDropUnk = 0;
        if ((this->modalMenu.borderStyle & 0x220U) != 0) {
            this->modalMenu.width = ((this->modalMenu.width + -1) / 0x18 + 1) * 0x18;
            this->modalMenu.height = ((this->modalMenu.height + -1) / 0x18 + 1) * 0x18;
        }
        _areWeInAnInGameMenu
            = MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
        if (_areWeInAnInGameMenu == FALSE) {
            if (this->modalMenu.x == -1) {
                this->modalMenu.x = DAT_WindowAndDirectDraw::instance.gameResolutionX / 2 - this->modalMenu.width / 2;
            } else {
                this->modalMenu.x = (DAT_WindowAndDirectDraw::instance.gameResolutionX + -800) / 2 + this->modalMenu.x;
            }
            if (this->modalMenu.y == -1) {
                this->modalMenu.y = DAT_WindowAndDirectDraw::instance.gameResolutionY / 2 - this->modalMenu.height / 2;
                goto LAB_004b29a5;
            }
        } else {
            if (this->modalMenu.x == -1) {
                this->modalMenu.x = DAT_WindowAndDirectDraw::instance.gameResolutionX / 2 - this->modalMenu.width / 2;
            } else {
                this->modalMenu.x = (DAT_WindowAndDirectDraw::instance.gameResolutionX + -800) / 2 + this->modalMenu.x;
            }
            if (this->modalMenu.y == -1) {
                this->modalMenu.y
                    = (DAT_WindowAndDirectDraw::instance.gameResolutionY + -0x80) / 2 - this->modalMenu.height / 2;
                goto LAB_004b29a5;
            }
        }
        this->modalMenu.y = (DAT_WindowAndDirectDraw::instance.gameResolutionY + -600) / 2 + this->modalMenu.y;
    LAB_004b29a5:
        this->disappearAfter = 0x20;
        this->mbr_0x6c = 0;
        this->timeItIsSet = timeGetTime();
        if ((this->modalMenu.borderStyle & 0x400U) != 0) {
            this->disappearAfter = 0;
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::renderMenuModal, this)();
        if (0x1e < (int)(this->timeItIsSet - DWORD_00df5534::instance)) {
            DWORD_00df5534::instance = this->timeItIsSet;
            _areWeInAnInGameMenu
                = MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
            if (_areWeInAnInGameMenu != FALSE) {
                DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::bltMapGameSurfaceToScreen,
                    DAT_WindowAndDirectDraw::ptr)(
                    this->modalMenu.x + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX,
                    this->modalMenu.y + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY,
                    this->modalMenu.width + this->modalMenu.x
                        + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX,
                    this->modalMenu.height + this->modalMenu.y
                        + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY);
                this->activeModalDialogID = OpenSHC::UI::Enums::MMT_NONE;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::bltScreenMenuSurfaceToScreen,
                DAT_WindowAndDirectDraw::ptr)(this->modalMenu.x, this->modalMenu.y,
                this->modalMenu.width + this->modalMenu.x, this->modalMenu.height + this->modalMenu.y);
        }
        this->activeModalDialogID = OpenSHC::UI::Enums::MMT_NONE;
    }

}
}
