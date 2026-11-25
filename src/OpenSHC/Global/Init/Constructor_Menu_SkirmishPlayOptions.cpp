#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_SkirmishPlayOptions.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AB50
    void Init::Constructor_Menu_SkirmishPlayOptions()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_SkirmishPlayOptions::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_SkirmishPlayOptions);
    }

}
}
