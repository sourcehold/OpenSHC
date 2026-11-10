#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_SaveMap.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AE20
    void Init::Constructor_Menu_SaveMap()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_SaveMap::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_SaveMap);
    }

}
}
