#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_InGameHelpText.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AF60
    void Init::Constructor_Menu_InGameHelpText()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_InGameHelpText::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_InGameHelpText);
    }

}
}
