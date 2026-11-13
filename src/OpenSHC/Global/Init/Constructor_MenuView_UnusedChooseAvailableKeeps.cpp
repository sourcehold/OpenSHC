#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/UnusedChooseAvailableKeeps.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_UnusedChooseAvailableKeeps.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A520
    void Init::Constructor_MenuView_UnusedChooseAvailableKeeps()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_UnusedChooseAvailableKeeps::ptr)(
            UI::Enums::MVT_UNUSED_CHOOSE_AVAILABLE_KEEPS,
            UI::MenuViews::UnusedChooseAvailableKeeps_Func::MenuView_UnusedChooseAvailableKeeps_Prepare::get(),
            UI::MenuViews::General_Func::MenuView_General_DoInitial_ScreenToBlack::get(),
            UI::MenuViews::UnusedChooseAvailableKeeps_Func::MenuView_UnusedChooseAvailableKeeps_DoEveryFrame::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_UnusedChooseAvailableKeeps::get());
    }

}
}
