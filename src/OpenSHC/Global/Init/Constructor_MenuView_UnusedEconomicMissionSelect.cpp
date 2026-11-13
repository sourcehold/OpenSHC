#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/MissionSelect.func.hpp"
#include "OpenSHC/UI/MenuViews/UnusedEconomicMissionSelect.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_UnusedEconomicMissionSelect.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A1F0
    void Init::Constructor_MenuView_UnusedEconomicMissionSelect()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_UnusedEconomicMissionSelect::ptr)(
            UI::Enums::MVT_UNUSED_ECONOMIC_MISSION_SELECTUnk,
            UI::MenuViews::UnusedEconomicMissionSelect_Func::MenuView_UnusedEconomicMissionSelect_Prepare::get(),
            UI::MenuViews::General_Func::MenuView_General_DoInitial_DefaultMainMenuStructure::get(),
            UI::MenuViews::MissionSelect_Func::MenuView_MissionSelect_DoEveryFrame::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_UnusedEconomicMissionSelect::get());
    }

}
}
