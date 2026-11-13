#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/UnusedExtremeAd.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_UnusedExtremeAd.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A6A0
    void Init::Constructor_MenuView_UnusedExtremeAd()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_UnusedExtremeAd::ptr)(
            UI::Enums::MVT_UNUSED_EXTREME_AD,
            UI::MenuViews::UnusedExtremeAd_Func::MenuView_UnusedExtremeAd_Prepare::get(),
            UI::MenuViews::UnusedExtremeAd_Func::MenuView_UnusedExtremeAd_DoInitial::get(),
            UI::MenuViews::UnusedExtremeAd_Func::MenuView_UnusedExtremeAd_DoEveryFrame::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_UnusedExtremeAd::get());
    }

}
}
