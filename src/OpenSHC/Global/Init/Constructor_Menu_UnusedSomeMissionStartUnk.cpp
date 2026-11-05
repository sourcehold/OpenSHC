#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_UnusedSomeMissionStartUnk.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AAE0
    void Init::Constructor_Menu_UnusedSomeMissionStartUnk()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_UnusedSomeMissionStartUnk::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_UnusedSomeMissionStartUnk);
    }

}
}
