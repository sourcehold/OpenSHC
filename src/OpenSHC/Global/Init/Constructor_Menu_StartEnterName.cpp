#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_StartEnterName.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AA90
    void Init::Constructor_Menu_StartEnterName()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_StartEnterName::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_StartEnterName);
    }

}
}
