#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_TriggerInvasion.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B0E0
    void Init::Constructor_Menu_TriggerInvasion()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_TriggerInvasion::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_TriggerInvasion);
    }

}
}
