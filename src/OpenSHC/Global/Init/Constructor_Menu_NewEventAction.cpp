#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_NewEventAction.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B080
    void Init::Constructor_Menu_NewEventAction()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_NewEventAction::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_NewEventAction);
    }

}
}
