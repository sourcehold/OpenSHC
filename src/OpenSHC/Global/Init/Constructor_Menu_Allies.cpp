#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_Allies.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AE90
    void Init::Constructor_Menu_Allies()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_Allies::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_Allies);
    }

}
}
