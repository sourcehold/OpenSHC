#include "../MenuModalComposition.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/Menu.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004AA1F0
    void MenuModalComposition::update()
    {
        this->minus1 = 0;
        this->mbr_0x78 = 0;
        if (this->activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE) {
            return;
        }
        if ((this->modalMenu.borderStyle & 4) != 0 && (this->modalMenu.borderStyle & 2) != 0) {
            // the dialog can be dragged by its 12 pixel title bar
            if (DAT_MouseState::instance.leftClickStart != 0 && this->modalDragDropUnk == 0
                && DAT_MouseState::instance.screenSpaceX >= this->modalMenu.x
                && DAT_MouseState::instance.screenSpaceX < this->modalMenu.x + this->modalMenu.width
                && DAT_MouseState::instance.screenSpaceY >= this->modalMenu.y
                && DAT_MouseState::instance.screenSpaceY < this->modalMenu.y + 12) {
                this->modalDragDropUnk = 1;
                this->mouseRelativeX = DAT_MouseState::instance.screenSpaceX - this->modalMenu.x;
                this->mouseRelativeY = DAT_MouseState::instance.screenSpaceY - this->modalMenu.y;
            } else if (this->modalDragDropUnk != 0) {
                if (!DAT_MouseState::instance.leftClickState) {
                    this->modalDragDropUnk = 0;
                } else {
                    this->modalMenu.x = DAT_MouseState::instance.screenSpaceX - this->mouseRelativeX;
                    this->modalMenu.y = DAT_MouseState::instance.screenSpaceY - this->mouseRelativeY;
                    if (this->modalMenu.x < 0) {
                        this->modalMenu.x = 0;
                    }
                    if (this->modalMenu.y < 0) {
                        this->modalMenu.y = 0;
                    }
                    if (MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()) {
                        if (this->modalMenu.x + this->modalMenu.width
                            >= DAT_WindowAndDirectDraw::instance.gameResolutionX) {
                            this->modalMenu.x
                                = DAT_WindowAndDirectDraw::instance.gameResolutionX - this->modalMenu.width;
                        }
                        // stay above the 128 pixel high menu bar
                        if (this->modalMenu.y + this->modalMenu.height
                            >= DAT_WindowAndDirectDraw::instance.gameResolutionY - 128) {
                            this->modalMenu.y
                                = DAT_WindowAndDirectDraw::instance.gameResolutionY - this->modalMenu.height - 128;
                        }
                    } else {
                        if (this->modalMenu.x + this->modalMenu.width
                            >= DAT_WindowAndDirectDraw::instance.gameResolutionX) {
                            this->modalMenu.x
                                = DAT_WindowAndDirectDraw::instance.gameResolutionX - this->modalMenu.width;
                        }
                        if (this->modalMenu.y + this->modalMenu.height
                            >= DAT_WindowAndDirectDraw::instance.gameResolutionY) {
                            this->modalMenu.y
                                = DAT_WindowAndDirectDraw::instance.gameResolutionY - this->modalMenu.height;
                        }
                    }
                }
            }
        }
        Menu* const menu = this->modalMenu.pointerToMenu;
        if (menu != NULL) {
            // y is read first and pointerToMenu again for the call, as the original does
            int const y = this->modalMenu.y;
            menu->xPosition = this->modalMenu.x;
            menu->yPosition = y;
            MACRO_CALL_MEMBER(OpenSHC::UI::Menu_Func::updateMenuButtons, this->modalMenu.pointerToMenu)();
        }
        if (this->minus1 != -1) {
            if ((DAT_MouseState::instance.screenSpaceX >= this->modalMenu.x
                    && DAT_MouseState::instance.screenSpaceX < this->modalMenu.x + this->modalMenu.width
                    && DAT_MouseState::instance.screenSpaceY >= this->modalMenu.y
                    && DAT_MouseState::instance.screenSpaceY < this->modalMenu.y + this->modalMenu.height)
                || this->modalDragDropUnk != 0) {
                this->minus1 = 1;
            }
            if (!MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()
                && DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_SCENARIO_DESCRIPTION) {
                this->minus1 = 1;
            }
            if (this->slot == 0
                && MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::isGameHaltingMenuOpen, DAT_GameCore::ptr)()) {
                this->minus1 = 1;
            }
        } else {
            this->minus1 = 0;
        }
        if ((this->modalMenu.borderStyle & 0x800) != 0) {
            this->minus1 = DAT_MenuHandlerState::instance.field_0x3c != 0;
        }
        if ((this->modalMenu.borderStyle & 0x1000) != 0) {
            if (this->minus1 != 0 && this->activeModalDialogID != OpenSHC::UI::Enums::MMT_DISPLAY_SCENARIO_HELP_TEXT) {
                this->mbr_0x78 = 1;
            }
            this->minus1 = 0;
        }
    }

}
}
