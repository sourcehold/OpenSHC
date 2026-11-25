#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_CrusadeMissionIntro.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059ACD0
    void Init::Constructor_Menu_CrusadeMissionIntro()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_CrusadeMissionIntro::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_CrusadeMissionIntro);
    }

}
}
