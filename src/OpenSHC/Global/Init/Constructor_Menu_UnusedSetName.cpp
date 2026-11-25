#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_UnusedSetName.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AB10
    void Init::Constructor_Menu_UnusedSetName()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_UnusedSetName::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_UnusedSetName);
    }

}
}
