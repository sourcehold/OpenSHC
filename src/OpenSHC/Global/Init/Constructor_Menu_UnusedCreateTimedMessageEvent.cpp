#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_UnusedCreateTimedMessageEvent.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B050
    void Init::Constructor_Menu_UnusedCreateTimedMessageEvent()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_UnusedCreateTimedMessageEvent::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_UnusedCreateTimedMessageEvent);
    }

}
}
