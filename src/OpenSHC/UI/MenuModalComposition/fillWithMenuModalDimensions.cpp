#include "../MenuModalComposition.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004AA3E0
    void MenuModalComposition::fillWithMenuModalDimensions(int* xPtr, int* yPtr, int* widthPtr, int* heightPtr)
    {
        if (this->activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE) {
            return;
        }
        if (MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()) {
            *xPtr = this->modalMenu.x + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX;
            *yPtr = this->modalMenu.y + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY;
        } else {
            *xPtr = this->modalMenu.x;
            *yPtr = this->modalMenu.y;
        }
        *widthPtr = this->modalMenu.width;
        *heightPtr = this->modalMenu.height;
        if ((this->modalMenu.borderStyle & 2) != 0) {
            // below the title bar
            *yPtr += 12;
            *heightPtr -= 12;
        }
    }

}
}
