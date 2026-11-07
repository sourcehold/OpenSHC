#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_NewEvent.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B060
    void Init::Constructor_Menu_NewEvent()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_NewEvent::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_NewEvent);
    }

}
}
