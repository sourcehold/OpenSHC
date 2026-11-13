#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/CrusadeEndscreen.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_CrusadeEndscreen.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AA30
    void Init::Constructor_MenuView_CrusadeEndscreen()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_CrusadeEndscreen::ptr)(
            UI::Enums::MVT_CRUSADE_ENDSCREEN,
            UI::MenuViews::CrusadeEndscreen_Func::MenuView_CrusadeEndscreen_Prepare::get(),
            UI::MenuViews::CrusadeEndscreen_Func::MenuView_CrusadeEndscreen_DoInitial::get(),
            UI::MenuViews::CrusadeEndscreen_Func::MenuView_CrusadeEndscreen_DoEveryFrame::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_CrusadeEndscreen::get());
    }

}
}
