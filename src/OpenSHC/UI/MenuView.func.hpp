/**
  path: 'OpenSHC/UI/MenuView.func.hpp'
*/

#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/UI/MenuView.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuView_Func {

        using OpenSHC::UI::MenuView;
        using OpenSHC::UI::Enums::MenuViewType;

        // Constructor

        MACRO_FUNCTION_RESOLVER(MenuView* (MenuView::*)(MenuViewType, cdeclVoidFunc*, cdeclVoidFunc*, cdeclVoidFunc*),
            false, Address::SHC_3BB0A8C1_0x004F4020, &MenuView::Constructor_MenuView)
        Constructor_MenuView;

        MACRO_FUNCTION_RESOLVER(MenuView* (MenuView::*)(MenuViewType), false, Address::SHC_3BB0A8C1_0x004F4050,
            &MenuView::Constructor_MenuView_Reduced)
        Constructor_MenuView_Reduced;

    } // namespace MenuView_Func
} // namespace UI
} // namespace OpenSHC
