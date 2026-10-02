#include "../DisplayElement.func.hpp"

#include "OpenSHC/Globals/DAT_PointerToDisplayElementStackTop.hpp"

namespace OpenSHC {
namespace UI {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004AF5E0
    DisplayElement* DisplayElement::Constructor_DisplayElement(eOnScreenText elementID, int xPos, int yPos,
        dword elementState, DisplayElementRenderFunc* renderFunction, DisplayElementPositionModifier positionModifier)
    {
        this->elementID_0x8 = elementID;
        this->x_0x0 = xPos;
        this->y_0x4 = yPos;
        this->elementStateUnk_0xc = elementState;
        this->activationTime_0x10 = 0;
        this->displayDuration_0x14 = -1;
        this->renderFunction_0x18 = renderFunction;
        this->positionModifier_0x1c = positionModifier;
        this->nextDisplayElement_0x20 = DAT_PointerToDisplayElementStackTop::instance;
        DAT_PointerToDisplayElementStackTop::instance = this;
        return this;
    }

}
}
