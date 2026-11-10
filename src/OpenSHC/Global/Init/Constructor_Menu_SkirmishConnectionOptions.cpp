#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_SkirmishConnectionOptions.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AB40
    void Init::Constructor_Menu_SkirmishConnectionOptions()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_SkirmishConnectionOptions::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_SkirmishConnectionOptions);
    }

}
}
