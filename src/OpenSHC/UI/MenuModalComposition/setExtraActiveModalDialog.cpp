#include "../MenuModalComposition.func.hpp"

#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/UI/Menu.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/UI/Enums/MenuItemHandleState.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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
    // FUNCTION: STRONGHOLDCRUSADER 0x004AA0A0
    void MenuModalComposition::setExtraActiveModalDialog(MenuModalType menuModalID, int dialogX, int dialogY)
    {
        uint uVar1;
        BOOLEnum BVar2;
        MenuModal* _modalMenu;
        DWORD DVar3;
        int iVar4;
        MenuModalComposition* pMVar5;
        Menu* _menuPtr;
        if ((this->slot == 0)
            && (DAT_MenuTextInputState::instance.currentModalDialog != OpenSHC::UI::Enums::MMT_NO_MENU)) {
            MACRO_CALL_MEMBER(
                OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
        }
        if (this->activeModalDialogID == OpenSHC::UI::Enums::MMT_DISPLAY_AI_LORD_MESSAGE) {
            this->activeModalDialogID = OpenSHC::UI::Enums::MMT_NONE;
            BVar2 = MACRO_CALL_MEMBER(
                OpenSHC::Rendering::Bink::AIMessageQueue_Func::playNextStoredAIMessage, DAT_VideoBikQueue::ptr)();
            if (BVar2 != FALSE) {}
        }
        this->activeModalDialogID = menuModalID;
        if (menuModalID != OpenSHC::UI::Enums::MMT_NONE) {
            _modalMenu = MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::findModalMenu, this)(menuModalID);
            pMVar5 = this;
            /*
              Just memcopies it into current modal menu? -TheRedDaemon
             */
            for (iVar4 = 10; pMVar5 = (MenuModalComposition*)&pMVar5->modalMenu, iVar4 != 0; iVar4 = iVar4 + -1) {
                ((MenuModal*)pMVar5)->menuModalID = _modalMenu->menuModalID;
                _modalMenu = (MenuModal*)&_modalMenu->x;
            }
        }
        uVar1 = (this->modalMenu).borderStyle;
        this->modalDragDropUnk = 0;
        (this->modalMenu).x = dialogX;
        (this->modalMenu).y = dialogY;
        if ((uVar1 & 0x220) != 0) {
            (this->modalMenu).width = (((this->modalMenu).width + -1) / 0x18 + 1) * 0x18;
            (this->modalMenu).height = (((this->modalMenu).height + -1) / 0x18 + 1) * 0x18;
        }
        if (dialogX < 0) {
            (this->modalMenu).x = 0;
        }
        if (dialogY < 0) {
            (this->modalMenu).y = 0;
        }
        iVar4 = (this->modalMenu).width;
        if (DAT_WindowAndDirectDraw::instance.gameResolutionX <= (this->modalMenu).x + iVar4) {
            (this->modalMenu).x = DAT_WindowAndDirectDraw::instance.gameResolutionX - iVar4;
        }
        iVar4 = (this->modalMenu).height;
        if (DAT_WindowAndDirectDraw::instance.gameResolutionY <= (this->modalMenu).y + iVar4) {
            (this->modalMenu).y = DAT_WindowAndDirectDraw::instance.gameResolutionY - iVar4;
        }
        this->disappearAfter = 0x20;
        this->mbr_0x6c = 0;
        DVar3 = timeGetTime();
        uVar1 = (this->modalMenu).borderStyle;
        this->timeItIsSet = DVar3;
        if ((uVar1 & 0x400) != 0) {
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
