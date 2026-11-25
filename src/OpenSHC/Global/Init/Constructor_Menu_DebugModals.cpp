#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_DebugModals.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AF00
    void Init::Constructor_Menu_DebugModals()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_DebugModals::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_DebugModals);
    }

}
}
