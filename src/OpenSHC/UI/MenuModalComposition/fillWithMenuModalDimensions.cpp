#include "../MenuModalComposition.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {

    using UI::Enums::MenuModalType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004AA3E0
    void MenuModalComposition::fillWithMenuModalDimensions(int* xPtr, int* yPtr, int* widthPtr, int* heigthPtr)
    {
        int _y;
        if (this->activeModalDialogID != UI::Enums::MMT_NONE) {
            BOOLEnum _areWeInAnInGameMenu
                = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
            if (!_areWeInAnInGameMenu) {
                *xPtr = this->modalMenu.x;
                _y = this->modalMenu.y;
            } else {
                *xPtr = this->modalMenu.x + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX;
                _y = this->modalMenu.y + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY;
            }
            *yPtr = _y;
            *widthPtr = this->modalMenu.width;
            *heigthPtr = this->modalMenu.height;
            if ((byte)this->modalMenu.borderStyle & 2) {
                *yPtr = *yPtr + 0xc;
                *heigthPtr = *heigthPtr + -0xc;
            }
        }
    }

}
}
