#include "../MenuModal.func.hpp"

#include "OpenSHC/Globals/DAT_ModalMenuArrayPointerToStackTop.hpp"

namespace OpenSHC {
namespace UI {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004A9E00
    MenuModal* MenuModal::Constructor_MenuModal(MenuModalType menuModalId, int xPos, int yPos, int width, int height,
        int borderStyle, int backgroundColourIndex, MenuModalRenderFunction* renderFunctionPtr, Menu* menuPtr)
    {
        this->menuModalID = menuModalId;
        this->x = xPos;
        this->y = yPos;
        this->width = width;
        this->height = height;
        this->borderStyle = borderStyle;
        this->backgroundColourIndex = backgroundColourIndex;
        this->menuModalRenderFunction = renderFunctionPtr;
        this->pointerToMenu = menuPtr;
        this->pointerToNextModalMenu = DAT_ModalMenuArrayPointerToStackTop::instance;
        DAT_ModalMenuArrayPointerToStackTop::instance = this;
        return this;
    }

}
}
