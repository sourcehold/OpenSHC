#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/IntroVideo.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_IntroVideo.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A850
    void Init::Constructor_MenuView_IntroVideo()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_IntroVideo::ptr)(UI::Enums::MVT_INTRO_VIDEO,
            UI::MenuViews::IntroVideo_Func::MenuView_IntroVideo_Prepare::get(),
            UI::MenuViews::General_Func::MenuView_General_DoInitial_OnlySetMenuXY::get(),
            UI::MenuViews::IntroVideo_Func::MenuView_IntroVideo_DoEveryFrame::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_IntroVideo::get());
    }

}
}
