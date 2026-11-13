#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/IntroLogos.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_IntroLogos.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A190
    void Init::Constructor_MenuView_IntroLogos()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_IntroLogos::ptr)(UI::Enums::MVT_INTRO_LOGOS,
            UI::MenuViews::IntroLogos_Func::MenuView_IntroLogos_Prepare::get(),
            UI::MenuViews::IntroLogos_Func::MenuView_IntroLogos_DoInitial::get(),
            UI::MenuViews::IntroLogos_Func::MenuView_IntroLogos_DoEveryFrame::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_IntroLogos::get());
    }

}
}
