#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_NewEventCondition.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B070
    void Init::Constructor_Menu_NewEventCondition()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_NewEventCondition::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_NewEventCondition);
    }

}
}
