#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_AlliesOrder.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AEA0
    void Init::Constructor_Menu_AlliesOrder()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_AlliesOrder::ptr)(
            DAT_RenderingDefinedData::instance.MenuItem_AlliesOrder);
    }

}
}
