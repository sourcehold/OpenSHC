#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_BuildMenu.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AD60
    void Init::Constructor_Menu_BuildMenu()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_BuildMenu::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_BuildMenu);
    }

}
}
