/**
  path: 'OpenSHC/UI/MenuView.func.hpp'
*/

#include "OpenSHC/UI/Enums/MenuViewTypeInt.hpp"
#include "OpenSHC/UI/MenuView.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuView_Func {

        using OpenSHC::UI::MenuView;
        using OpenSHC::UI::Enums::MenuViewTypeInt;

        MACRO_FUNCTION_RESOLVER(MenuView* (MenuView::*)(MenuViewTypeInt), false, Address::SHC_3BB0A8C1_0x004F4050,
            &MenuView::Constructor_MenuView_Reduced)
        Constructor_MenuView_Reduced;

    } // namespace MenuView_Func
} // namespace UI
} // namespace OpenSHC
