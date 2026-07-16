/**
  path: 'OpenSHC/UI/DisplayElement.func.hpp'
*/

#include "OpenSHC/UI/DisplayElement.hpp"
namespace OpenSHC {
namespace UI {
    namespace DisplayElement_Func {

        // Constructor

        MACRO_FUNCTION_RESOLVER(DisplayElement* (DisplayElement::*)(eOnScreenText, int, int, dword,
                                    DisplayElementRenderFunc*, DisplayElementPositionModifier),
            false, Address::SHC_3BB0A8C1_0x004AF5E0, &DisplayElement::Constructor_DisplayElement)
        Constructor_DisplayElement;

    } // namespace DisplayElement_Func
} // namespace UI
} // namespace OpenSHC
