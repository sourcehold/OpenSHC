#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/Unknown61ReturnToSkrimishMenuUnk.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_Unknown61ReturnToSkrimishMenuUnk.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A340
    void Init::Constructor_MenuView_Unknown61ReturnToSkrimishMenuUnk()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_Unknown61ReturnToSkrimishMenuUnk::ptr)(
            UI::Enums::MVT_UNKNOWN_61_RETURN_TO_SKIRMISH_MENUUnk,
            UI::MenuViews::Unknown61ReturnToSkrimishMenuUnk_Func::MenuView_Unknown61ReturnToSkrimishMenuUnk_Prepare::
                get(),
            UI::MenuViews::Unknown61ReturnToSkrimishMenuUnk_Func::MenuView_Unknown61ReturnToSkrimishMenuUnk_DoInitial::
                get(),
            UI::MenuViews::Unknown61ReturnToSkrimishMenuUnk_Func::
                MenuView_Unknown61ReturnToSkrimishMenuUnk_DoEveryFrame::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_Unknown61ReturnToSkrimishMenuUnk::get());
    }

}
}
