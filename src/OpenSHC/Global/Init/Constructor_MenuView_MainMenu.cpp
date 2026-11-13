#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/MainMenu.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_MainMenu.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A730
    void Init::Constructor_MenuView_MainMenu()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_MainMenu::ptr)(UI::Enums::MVT_MAIN_MENU,
            UI::MenuViews::MainMenu_Func::MenuView_MainMenu_Prepare::get(),
            UI::MenuViews::MainMenu_Func::MenuView_MainMenu_DoInitial::get(),
            UI::MenuViews::MainMenu_Func::MenuView_MainMenu_DoEveryFrame::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_MainMenu::get());
    }

}
}
