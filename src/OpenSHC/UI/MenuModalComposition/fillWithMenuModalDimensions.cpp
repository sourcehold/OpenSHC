#include "../MenuModalComposition.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Enums::MenuModalType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004AA3E0
    void MenuModalComposition::fillWithMenuModalDimensions(int* xPtr, int* yPtr, int* widthPtr, int* heigthPtr)
    {
        BOOLEnum _areWeInAnInGameMenu;
        int _y;
        if (this->activeModalDialogID != OpenSHC::UI::Enums::MMT_NONE) {
            _areWeInAnInGameMenu
                = MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
            if (_areWeInAnInGameMenu == FALSE) {
                *xPtr = this->modalMenu.x;
                _y = this->modalMenu.y;
            } else {
                *xPtr = this->modalMenu.x + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX;
                _y = this->modalMenu.y + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY;
            }
            *yPtr = _y;
            *widthPtr = this->modalMenu.width;
            *heigthPtr = this->modalMenu.height;
            if (((byte)this->modalMenu.borderStyle & 2) != 0) {
                *yPtr = *yPtr + 0xc;
                *heigthPtr = *heigthPtr + -0xc;
            }
        }
    }

}
}
