#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_SelectCrusade.hpp"

namespace OpenSHC {
namespace Global {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059ABA0
    void Init::Constructor_Menu_SelectCrusade()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::Menu_Func::Constructor_Menu, Menu_SelectCrusade::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_SelectCrusade);
    }

}
}
