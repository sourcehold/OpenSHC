#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_IntroLogos.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AA70
    void Init::Constructor_Menu_IntroLogos()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_IntroLogos::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_IntroLogos);
    }

}
}
