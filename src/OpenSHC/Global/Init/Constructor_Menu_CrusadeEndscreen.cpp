#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_CrusadeEndscreen.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AD00
    void Init::Constructor_Menu_CrusadeEndscreen()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_CrusadeEndscreen::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_CrusadeEndscreen);
    }

}
}
