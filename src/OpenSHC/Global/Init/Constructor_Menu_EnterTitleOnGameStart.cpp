#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_EnterTitleOnGameStart.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059ADF0
    void Init::Constructor_Menu_EnterTitleOnGameStart()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_EnterTitleOnGameStart::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_EnterTitleOnGameStart);
    }

}
}
