#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_AlliesRequestGoods.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AEB0
    void Init::Constructor_Menu_AlliesRequestGoods()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_AlliesRequestGoods::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_AlliesRequestGoods);
    }

}
}
