#include "../MenuModalComposition.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/Menu.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Enums::MenuModalType;
    using OpenSHC::UI::Enums::MenuViewType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004AA1F0
    void MenuModalComposition::update()
    {
        int _x2;
        BOOLEnum _areWeInAnInGameMenu;
        int _isInTickingGameMode;
        int _y2;
        int _x3;
        int _x;
        int _width;
        int _heigth;
        int _height2;
        int _modalMenuXPos;
        uint _borderStyle;
        Menu* _menuPtr;
        int _y;
        this->minus1 = 0;
        this->mbr_0x78 = 0;
        if (this->activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE) {}
        _borderStyle = (this->modalMenu).borderStyle;
        if (((_borderStyle & 4) == 0) || ((_borderStyle & 2) == 0))
            goto LAB_004aa311;
        if (DAT_MouseState::instance.leftClickStart == 0) {
        LAB_004aa272:
            if (this->modalDragDropUnk == 0)
                goto LAB_004aa311;
        } else if (this->modalDragDropUnk == 0) {
            _x = (this->modalMenu).x;
            if ((((_x <= DAT_MouseState::instance.screenSpaceX)
                     && (DAT_MouseState::instance.screenSpaceX < (this->modalMenu).width + _x))
                    && (_y = (this->modalMenu).y, _y <= DAT_MouseState::instance.screenSpaceY))
                && (DAT_MouseState::instance.screenSpaceY < _y + 0xc)) {
                this->modalDragDropUnk = 1;
                this->mouseRelativeX = DAT_MouseState::instance.screenSpaceX - _x;
                this->mouseRelativeY = DAT_MouseState::instance.screenSpaceY - _y;
                goto LAB_004aa311;
            }
            goto LAB_004aa272;
        }
        if (DAT_MouseState::instance.leftClickState == FALSE) {
            this->modalDragDropUnk = 0;
        } else {
            _x2 = DAT_MouseState::instance.screenSpaceX - this->mouseRelativeX;
            (this->modalMenu).x = _x2;
            _y2 = DAT_MouseState::instance.screenSpaceY - this->mouseRelativeY;
            (this->modalMenu).y = _y2;
            if (_x2 < 0) {
                (this->modalMenu).x = 0;
            }
            if (_y2 < 0) {
                (this->modalMenu).y = 0;
            }
            _areWeInAnInGameMenu
                = MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
            _width = (this->modalMenu).width;
            _x3 = (this->modalMenu).x + _width;
            if (_areWeInAnInGameMenu == FALSE) {
                if (DAT_WindowAndDirectDraw::instance.gameResolutionX <= _x3) {
                    (this->modalMenu).x = DAT_WindowAndDirectDraw::instance.gameResolutionX - _width;
                }
                _heigth = (this->modalMenu).height;
                if ((this->modalMenu).y + _heigth < DAT_WindowAndDirectDraw::instance.gameResolutionY)
                    goto LAB_004aa311;
                _y = DAT_WindowAndDirectDraw::instance.gameResolutionY - _heigth;
            } else {
                if (DAT_WindowAndDirectDraw::instance.gameResolutionX <= _x3) {
                    (this->modalMenu).x = DAT_WindowAndDirectDraw::instance.gameResolutionX - _width;
                }
                _height2 = (this->modalMenu).height;
                if ((this->modalMenu).y + _height2 < DAT_WindowAndDirectDraw::instance.gameResolutionY + -0x80)
                    goto LAB_004aa311;
                _y = (DAT_WindowAndDirectDraw::instance.gameResolutionY - _height2) + -0x80;
            }
            (this->modalMenu).y = _y;
        }
    LAB_004aa311:
        _menuPtr = (this->modalMenu).pointerToMenu;
        if (_menuPtr != (Menu*)0x0) {
            _y = (this->modalMenu).y;
            _menuPtr->xPosition = (this->modalMenu).x;
            _menuPtr->yPosition = _y;
MACRO_CALL_MEMBER(OpenSHC::UI::Menu_Func::updateMenuButtons, (this->modalMenu).pointerToMenu)();
        }
        if (this->minus1 == -1) {
            this->minus1 = 0;
        } else {
            _modalMenuXPos = (this->modalMenu).x;
            if ((((_modalMenuXPos <= DAT_MouseState::instance.screenSpaceX)
                     && (DAT_MouseState::instance.screenSpaceX < (this->modalMenu).width + _modalMenuXPos))
                    && ((_y = (this->modalMenu).y,
                        _y <= DAT_MouseState::instance.screenSpaceY
                            && (DAT_MouseState::instance.screenSpaceY < (this->modalMenu).height + _y))))
                || (this->modalDragDropUnk != 0)) {
                this->minus1 = 1;
            }
            _areWeInAnInGameMenu
                = MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
            if ((_areWeInAnInGameMenu == FALSE)
                && (DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_SCENARIO_DESCRIPTION)) {
                this->minus1 = 1;
            }
            if ((this->slot == 0)
                && (_isInTickingGameMode
                    = MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::isGameHaltingMenuOpen, DAT_GameCore::ptr)(),
                    _isInTickingGameMode != 0)) {
                this->minus1 = 1;
            }
        }
        _borderStyle = (this->modalMenu).borderStyle;
        if ((_borderStyle & 0x800) != 0) {
            this->minus1 = (uint)(DAT_MenuHandlerState::instance.field18_0x3c != 0);
        }
        if ((_borderStyle & 0x1000) != 0) {
            if ((this->minus1 != 0)
                && (this->activeModalDialogID != OpenSHC::UI::Enums::MMT_DISPLAY_SCENARIO_HELP_TEXT)) {
                this->mbr_0x78 = 1;
            }
            this->minus1 = 0;
        }
    }

}
}
