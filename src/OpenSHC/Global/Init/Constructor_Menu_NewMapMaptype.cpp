#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_NewMapMaptype.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AC20
    void Init::Constructor_Menu_NewMapMaptype()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_NewMapMaptype::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_NewMapMaptype);
    }

}
}
