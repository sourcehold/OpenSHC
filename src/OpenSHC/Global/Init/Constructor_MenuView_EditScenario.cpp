#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/EditScenario.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_EditScenario.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A6D0
    void Init::Constructor_MenuView_EditScenario()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_EditScenario::ptr)(
            UI::Enums::MVT_EDIT_SCENARIO, UI::MenuViews::EditScenario_Func::MenuView_EditScenario_Prepare::get(),
            UI::MenuViews::General_Func::MenuView_General_DoInitial_OnlySetMenuXY::get(),
            UI::MenuViews::EditScenario_Func::MenuView_EditScenario_DoEveryFrame::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_EditScenario::get());
    }

}
}
