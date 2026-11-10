#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_CustomScenarios.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AAD0
    void Init::Constructor_Menu_CustomScenarios()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_CustomScenarios::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_CustomScenarios);
    }

}
}
