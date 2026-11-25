#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_UnusedDemoBuyItScreen.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AFA0
    void Init::Constructor_Menu_UnusedDemoBuyItScreen()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_UnusedDemoBuyItScreen::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_UnusedDemoBuyItScreen);
    }

}
}
