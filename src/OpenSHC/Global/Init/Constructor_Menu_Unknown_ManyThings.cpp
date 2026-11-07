#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_Unknown_ManyThings.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AA60
    void Init::Constructor_Menu_Unknown_ManyThings()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_Unknown_ManyThings::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_Unknown_ManyThings);
    }

}
}
