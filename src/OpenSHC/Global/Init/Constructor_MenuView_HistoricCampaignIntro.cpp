#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/HistoricCampaignIntro.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_HistoricCampaignIntro.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A8E0
    void Init::Constructor_MenuView_HistoricCampaignIntro()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_HistoricCampaignIntro::ptr)(
            UI::Enums::MVT_HISTORIC_CAMPAIGN_INTRO,
            UI::MenuViews::HistoricCampaignIntro_Func::MenuView_HistoricCampaignIntro_Prepare::get(),
            UI::MenuViews::General_Func::MenuView_General_DoInitial_BlackBorderAndGfx::get(),
            UI::MenuViews::HistoricCampaignIntro_Func::MenuView_HistoricCampaignIntro_DoEveryFrame::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_HistoricCampaignIntro::get());
    }

}
}
