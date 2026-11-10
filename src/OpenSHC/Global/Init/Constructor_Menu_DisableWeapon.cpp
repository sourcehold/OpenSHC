#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_DisableWeapon.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B0D0
    void Init::Constructor_Menu_DisableWeapon()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_DisableWeapon::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_DisableWeapon);
    }

}
}
