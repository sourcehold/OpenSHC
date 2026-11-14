#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/UnusedDemoBuyItScreen.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_UnusedDemoBuyItScreen.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A820
    void Init::Constructor_MenuView_UnusedDemoBuyItScreen()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_UnusedDemoBuyItScreen::ptr)(
            UI::Enums::MVT_UNUSED_DEMO_BUY_IT_SCREEN,
            UI::MenuViews::UnusedDemoBuyItScreen_Func::MenuView_UnusedDemoBuyItScreen_Prepare::get(),
            UI::MenuViews::UnusedDemoBuyItScreen_Func::MenuView_UnusedDemoBuyItScreen_DoInitial::get(),
            UI::MenuViews::UnusedDemoBuyItScreen_Func::MenuView_UnusedDemoBuyItScreen_DoEveryFrame::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_UnusedDemoBuyItScreen::get());
    }

}
}
