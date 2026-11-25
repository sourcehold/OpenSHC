#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_StartGoods.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B020
    void Init::Constructor_Menu_StartGoods()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_StartGoods::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_StartGoods);
    }

}
}
