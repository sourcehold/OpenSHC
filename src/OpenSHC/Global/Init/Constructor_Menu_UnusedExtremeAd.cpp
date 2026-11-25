#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_UnusedExtremeAd.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AC90
    void Init::Constructor_Menu_UnusedExtremeAd()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_UnusedExtremeAd::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_UnusedExtremeAd);
    }

}
}
