#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_IntroVideo.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AA80
    void Init::Constructor_Menu_IntroVideo()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_IntroVideo::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_IntroVideo);
    }

}
}
