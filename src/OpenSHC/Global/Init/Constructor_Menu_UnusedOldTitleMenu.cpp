#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_UnusedOldTitleMenu.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AB20
    void Init::Constructor_Menu_UnusedOldTitleMenu()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_UnusedOldTitleMenu::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_UnusedOldTitleMenu);
    }

}
}
