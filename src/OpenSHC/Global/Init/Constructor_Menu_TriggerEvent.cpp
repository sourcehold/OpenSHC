#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_TriggerEvent.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B100
    void Init::Constructor_Menu_TriggerEvent()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_TriggerEvent::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_TriggerEvent);
    }

}
}
