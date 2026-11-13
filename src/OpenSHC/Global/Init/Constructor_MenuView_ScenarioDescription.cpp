#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/ScenarioDescription.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_ScenarioDescription.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A610
    void Init::Constructor_MenuView_ScenarioDescription()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_ScenarioDescription::ptr)(
            UI::Enums::MVT_SCENARIO_DESCRIPTION,
            UI::MenuViews::ScenarioDescription_Func::MenuView_ScenarioDescription_Prepare::get(),
            UI::MenuViews::ScenarioDescription_Func::MenuView_ScenarioDescription_DoInitial::get(),
            UI::MenuViews::ScenarioDescription_Func::MenuView_ScenarioDescription_DoEveryFrame::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_ScenarioDescription::get());
    }

}
}
