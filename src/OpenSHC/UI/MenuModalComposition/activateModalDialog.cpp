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

    // FUNCTION: STRONGHOLDCRUSADER 0x004A9ED0
    void MenuModalComposition::activateModalDialog(MenuModalType menuModalID, BOOLEnum retainOther)
    {
        if (retainOther == FALSE && this->slot == 0
            && DAT_MenuTextInputState::instance.currentModalDialog != OpenSHC::UI::Enums::MMT_NO_MENU) {
            MACRO_CALL_MEMBER(
                OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
        }
        if (this->activeModalDialogID == OpenSHC::UI::Enums::MMT_DISPLAY_AI_LORD_MESSAGE) {
            this->activeModalDialogID = OpenSHC::UI::Enums::MMT_NONE;
            if (MACRO_CALL_MEMBER(
                    OpenSHC::Rendering::Bink::AIMessageQueue_Func::playNextStoredAIMessage, DAT_VideoBikQueue::ptr)()
                != FALSE) {
                return;
            }
        }
        this->activeModalDialogID = menuModalID;
        if (menuModalID != OpenSHC::UI::Enums::MMT_NONE) {
            // just copy the menumodal into a fixed spot in memory.
            memcpy(&this->modalMenu,
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::findModalMenu, this)(menuModalID),
                sizeof(MenuModal));
        }
        this->modalDragDropUnk = 0;
        if ((this->modalMenu.borderStyle & 0x220) != 0) {
            // tiled frames come in whole 24x24 tiles
            this->modalMenu.width = ((this->modalMenu.width - 1) / 24 + 1) * 24;
            this->modalMenu.height = ((this->modalMenu.height - 1) / 24 + 1) * 24;
        }
        if (MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE) {
            if (this->modalMenu.x == -1) {
                this->modalMenu.x = DAT_WindowAndDirectDraw::instance.gameResolutionX / 2 - this->modalMenu.width / 2;
            } else {
                this->modalMenu.x = (DAT_WindowAndDirectDraw::instance.gameResolutionX - 800) / 2 + this->modalMenu.x;
            }
            if (this->modalMenu.y == -1) {
                // centred over the map, above the 128 pixel high menu bar
                this->modalMenu.y
                    = (DAT_WindowAndDirectDraw::instance.gameResolutionY - 128) / 2 - this->modalMenu.height / 2;
            } else {
                this->modalMenu.y = (DAT_WindowAndDirectDraw::instance.gameResolutionY - 600) / 2 + this->modalMenu.y;
            }
        } else {
            if (this->modalMenu.x == -1) {
                this->modalMenu.x = DAT_WindowAndDirectDraw::instance.gameResolutionX / 2 - this->modalMenu.width / 2;
            } else {
                this->modalMenu.x = (DAT_WindowAndDirectDraw::instance.gameResolutionX - 800) / 2 + this->modalMenu.x;
            }
            if (this->modalMenu.y == -1) {
                this->modalMenu.y = DAT_WindowAndDirectDraw::instance.gameResolutionY / 2 - this->modalMenu.height / 2;
            } else {
                this->modalMenu.y = (DAT_WindowAndDirectDraw::instance.gameResolutionY - 600) / 2 + this->modalMenu.y;
            }
        }
        this->disappearAfter = 32;
        this->mbr_0x6c = 0;
        this->timeItIsSet = timeGetTime();
        if ((this->modalMenu.borderStyle & 0x400) != 0) {
            this->disappearAfter = 0;
        }
        Menu* const menu = this->modalMenu.pointerToMenu;
        if (menu != NULL) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Menu_Func::handleMenuItems, menu)(
                OpenSHC::UI::Enums::MIHS_RESET_MENU_ITEM_STATEUnk);
            menu->zero = 0;
            this->modalMenu.pointerToMenu->thousand = 0;
            this->modalMenu.pointerToMenu->one = 1;
        }
    }

}
}
