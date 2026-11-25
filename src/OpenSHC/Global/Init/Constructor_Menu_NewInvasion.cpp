#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_NewInvasion.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B040
    void Init::Constructor_Menu_NewInvasion()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_NewInvasion::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_NewInvasion);
    }

}
}
