#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_LoadMap.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AE10
    void Init::Constructor_Menu_LoadMap()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_LoadMap::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_LoadMap);
    }

}
}
