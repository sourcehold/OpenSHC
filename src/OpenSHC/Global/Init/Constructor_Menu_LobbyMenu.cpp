#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_LobbyMenu.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AB30
    void Init::Constructor_Menu_LobbyMenu()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_LobbyMenu::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_LobbyMenu);
    }

}
}
