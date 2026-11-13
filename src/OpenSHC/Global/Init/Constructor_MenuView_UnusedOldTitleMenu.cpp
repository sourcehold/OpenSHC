#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/UnusedOldTitleMenu.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_UnusedOldTitleMenu.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A250
    void Init::Constructor_MenuView_UnusedOldTitleMenu()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_UnusedOldTitleMenu::ptr)(
            UI::Enums::MVT_UNUSED_OLD_TITLE_MENU,
            UI::MenuViews::UnusedOldTitleMenu_Func::MenuView_UnusedOldTitleMenu_Prepare::get(),
            UI::MenuViews::UnusedOldTitleMenu_Func::MenuView_UnusedOldTitleMenu_DoInitial::get(),
            Global_Func::DoNothing::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_UnusedOldTitleMenu::get());
    }

}
}
