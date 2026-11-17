#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/HistoricMissionIntro.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_HistoricMissionIntro.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A8B0
    void Init::Constructor_MenuView_HistoricMissionIntro()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_HistoricMissionIntro::ptr)(
            UI::Enums::MVT_HISTORIC_MISSION_INTRO,
            UI::MenuViews::HistoricMissionIntro_Func::MenuView_HistoricMissionIntro_Prepare::get(),
            UI::MenuViews::General_Func::MenuView_General_DoInitial_BlackBorderAndGfx::get(),
            UI::MenuViews::HistoricMissionIntro_Func::MenuView_HistoricMissionIntro_DoEveryFrame::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_HistoricMissionIntro::get());
    }

}
}
