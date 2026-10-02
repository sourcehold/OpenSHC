#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_NewEvent.hpp"

namespace OpenSHC {
namespace Global {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059B060
    void Init::Constructor_Menu_NewEvent()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::Menu_Func::Constructor_Menu, Menu_NewEvent::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_NewEvent);
    }

}
}
