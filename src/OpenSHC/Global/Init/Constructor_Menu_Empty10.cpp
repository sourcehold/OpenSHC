#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_Empty10.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AFC0
    void Init::Constructor_Menu_Empty10()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_Empty10::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_Empty10);
    }

}
}
