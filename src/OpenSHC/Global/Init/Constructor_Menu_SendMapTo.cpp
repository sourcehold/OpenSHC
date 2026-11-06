#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_SendMapTo.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AB60
    void Init::Constructor_Menu_SendMapTo()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_SendMapTo::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_SendMapTo);
    }

}
}
