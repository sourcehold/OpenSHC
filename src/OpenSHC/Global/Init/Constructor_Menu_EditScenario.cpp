#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_EditScenario.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AFF0
    void Init::Constructor_Menu_EditScenario()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_EditScenario::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_EditScenario);
    }

}
}
