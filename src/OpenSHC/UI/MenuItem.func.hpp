/**
  path: 'OpenSHC/UI/MenuItem.func.hpp'
*/

#include "OpenSHC/UI/MenuItem.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItem_Func {

        MACRO_FUNCTION_RESOLVER(
            int (MenuItem::*)(), false, Address::SHC_3BB0A8C1_0x004F4290, &MenuItem::handleMenuElementsCallbacks)
        handleMenuElementsCallbacks;

        MACRO_FUNCTION_RESOLVER(
            void (MenuItem::*)(), false, Address::SHC_3BB0A8C1_0x004F49D0, &MenuItem::prepareAndRenderMenuItems)
        prepareAndRenderMenuItems;

        MACRO_FUNCTION_RESOLVER(
            void (MenuItem::*)(), false, Address::SHC_3BB0A8C1_0x004F4C30, &MenuItem::resetMenuItemStateUnk)
        resetMenuItemStateUnk;

    } // namespace MenuItem_Func
} // namespace UI
} // namespace OpenSHC
