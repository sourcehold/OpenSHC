#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_UnusedSelectRandomNumberOfEnemies.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AB80
    void Init::Constructor_Menu_UnusedSelectRandomNumberOfEnemies()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_UnusedSelectRandomNumberOfEnemies::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_UnusedSelectRandomNumberOfEnemies);
    }

}
}
