#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_BuildingAndStatusMenu.hpp"

namespace OpenSHC {
namespace Global {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059AD70
    void Init::Constructor_Menu_BuildingAndStatusMenu()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::Menu_Func::Constructor_Menu, Menu_BuildingAndStatusMenu::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_BuildingAndStatusMenu);
    }

}
}
