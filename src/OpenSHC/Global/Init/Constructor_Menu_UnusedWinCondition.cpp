#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_UnusedWinCondition.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059ABF0
    void Init::Constructor_Menu_UnusedWinCondition()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_UnusedWinCondition::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_UnusedWinCondition);
    }

}
}
