#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/LobbyMenu.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_LobbyMenu.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A2E0
    void Init::Constructor_MenuView_LobbyMenu()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_LobbyMenu::ptr)(UI::Enums::MVT_LOBBY_MENU,
            UI::MenuViews::LobbyMenu_Func::MenuView_LobbyMenu_Prepare::get(),
            UI::MenuViews::General_Func::MenuView_General_DoInitial_DefaultMainMenuStructure::get(),
            UI::MenuViews::LobbyMenu_Func::MenuView_LobbyMenu_DoEveryFrame::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_LobbyMenu::get());
    }

}
}
