#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_MainMenu.hpp"

namespace OpenSHC {
namespace Global {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059AAA0
    void Init::Constructor_Menu_MainMenu()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::Menu_Func::Constructor_Menu, Menu_MainMenu::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_MainMenu);
    }

}
}
