#include "../MenuModalComposition.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/UI/Menu.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/UI/Enums/MenuItemHandleState.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Enums::MenuItemHandleState;
    using OpenSHC::UI::Enums::MenuModalType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004A9ED0
    void MenuModalComposition::activateModalDialog(MenuModalType menuModalID, BOOLEnum retainOther)
    {
        BOOL _startedPlayingAIMessage;
        MenuModal* _modalMenu;
        BOOLEnum _areWeInAnInGameMenu;
        DWORD _now;
        int _modalCopyLoopIndex;
        MenuModalComposition* pMVar1;
        uint _borderStyle;
        Menu* _menuPtr;
        int _modalMenuX;
        int _modalMenuY;
        if (((retainOther == FALSE) && (this->slot == 0))
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
        this->activeModalDialogID = menuModalID;
        if (menuModalID != OpenSHC::UI::Enums::MMT_NONE) {
            _modalMenu = MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::findModalMenu, this)(menuModalID);
            pMVar1 = this;
            /*
              just copy the menumodal into a fixed spot in memory.
             */
            for (_modalCopyLoopIndex = 10; pMVar1 = (MenuModalComposition*)&pMVar1->modalMenu, _modalCopyLoopIndex != 0;
                _modalCopyLoopIndex = _modalCopyLoopIndex + -1) {
                ((MenuModal*)pMVar1)->menuModalID = _modalMenu->menuModalID;
                _modalMenu = (MenuModal*)&_modalMenu->x;
            }
        }
        _borderStyle = (this->modalMenu).borderStyle;
        this->modalDragDropUnk = 0;
        if ((_borderStyle & 0x220) != 0) {
            (this->modalMenu).width = (((this->modalMenu).width + -1) / 0x18 + 1) * 0x18;
            (this->modalMenu).height = (((this->modalMenu).height + -1) / 0x18 + 1) * 0x18;
        }
        _areWeInAnInGameMenu
            = MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
        _modalMenuX = (this->modalMenu).x;
        if (_areWeInAnInGameMenu == FALSE) {
            if (_modalMenuX == -1) {
                _modalMenuX = DAT_WindowAndDirectDraw::instance.gameResolutionX / 2 - (this->modalMenu).width / 2;
            } else {
                _modalMenuX = (DAT_WindowAndDirectDraw::instance.gameResolutionX + -800) / 2 + _modalMenuX;
            }
            _modalMenuY = (this->modalMenu).y;
            (this->modalMenu).x = _modalMenuX;
            if (_modalMenuY != -1)
                goto LAB_004aa048;
            _modalMenuY = DAT_WindowAndDirectDraw::instance.gameResolutionY / 2 - (this->modalMenu).height / 2;
        } else {
            if (_modalMenuX == -1) {
                _modalMenuX = DAT_WindowAndDirectDraw::instance.gameResolutionX / 2 - (this->modalMenu).width / 2;
            } else {
                _modalMenuX = (DAT_WindowAndDirectDraw::instance.gameResolutionX + -800) / 2 + _modalMenuX;
            }
            _modalMenuY = (this->modalMenu).y;
            (this->modalMenu).x = _modalMenuX;
            if (_modalMenuY == -1) {
                (this->modalMenu).y
                    = (DAT_WindowAndDirectDraw::instance.gameResolutionY + -128) / 2 - (this->modalMenu).height / 2;
                goto LAB_004aa057;
            }
        LAB_004aa048:
            _modalMenuY = (DAT_WindowAndDirectDraw::instance.gameResolutionY + -600) / 2 + _modalMenuY;
        }
        (this->modalMenu).y = _modalMenuY;
    LAB_004aa057:
        this->disappearAfter = 0x20;
        this->mbr_0x6c = 0;
        _now = timeGetTime();
        _borderStyle = (this->modalMenu).borderStyle;
        this->timeItIsSet = _now;
        if ((_borderStyle & 0x400) != 0) {
            this->disappearAfter = 0;
        }
        _menuPtr = (this->modalMenu).pointerToMenu;
        if (_menuPtr != (Menu*)0x0) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Menu_Func::handleMenuItems, _menuPtr)(
                OpenSHC::UI::Enums::MIHS_RESET_MENU_ITEM_STATEUnk);
            _menuPtr->zero = 0;
            ((this->modalMenu).pointerToMenu)->thousand = 0;
            ((this->modalMenu).pointerToMenu)->one = 1;
        }
    }

}
}
