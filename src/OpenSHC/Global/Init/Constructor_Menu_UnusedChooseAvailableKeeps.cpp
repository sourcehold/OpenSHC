#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_UnusedChooseAvailableKeeps.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AC40
    void Init::Constructor_Menu_UnusedChooseAvailableKeeps()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_UnusedChooseAvailableKeeps::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_UnusedChooseAvailableKeeps);
    }

}
}
