#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/BuildMenu.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_BuildMenu.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A400
    void Init::Constructor_MenuView_BuildMenu()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_BuildMenu::ptr)(UI::Enums::MVT_BUILD_MENU,
            UI::MenuViews::BuildMenu_Func::MenuView_BuildMenu_Prepare::get(),
            UI::MenuViews::BuildMenu_Func::MenuView_BuildMenu_DoInitial::get(),
            UI::MenuViews::BuildMenu_Func::MenuView_BuildMenu_DoEveryFrame::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_BuildMenu::get());
    }

}
}
