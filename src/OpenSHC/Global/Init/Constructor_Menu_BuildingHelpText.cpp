#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_BuildingHelpText.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AF50
    void Init::Constructor_Menu_BuildingHelpText()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_BuildingHelpText::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_BuildingHelpText);
    }

}
}
