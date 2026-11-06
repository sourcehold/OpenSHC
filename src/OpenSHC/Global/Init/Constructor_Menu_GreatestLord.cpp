#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_GreatestLord.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AED0
    void Init::Constructor_Menu_GreatestLord()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_GreatestLord::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_GreatestLord);
    }

}
}
