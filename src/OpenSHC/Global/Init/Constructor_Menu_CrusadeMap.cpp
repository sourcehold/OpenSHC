#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_CrusadeMap.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059ACE0
    void Init::Constructor_Menu_CrusadeMap()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_CrusadeMap::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_CrusadeMap);
    }

}
}
