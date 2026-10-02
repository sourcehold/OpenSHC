#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_UnusedChooseAvailableKeeps.hpp"

namespace OpenSHC {
namespace Global {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059AC40
    void Init::Constructor_Menu_UnusedChooseAvailableKeeps()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::Menu_Func::Constructor_Menu, Menu_UnusedChooseAvailableKeeps::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_UnusedChooseAvailableKeeps);
    }

}
}
