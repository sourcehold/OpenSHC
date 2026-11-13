#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/HistoricCampaignOutro.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_HistoricCampaignOutro.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A910
    void Init::Constructor_MenuView_HistoricCampaignOutro()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_HistoricCampaignOutro::ptr)(
            UI::Enums::MVT_HISTORIC_CAMPAIGN_OUTRO,
            UI::MenuViews::HistoricCampaignOutro_Func::MenuView_HistoricCampaignOutro_Prepare::get(),
            UI::MenuViews::General_Func::MenuView_General_DoInitial_BlackBorderAndGfx::get(),
            UI::MenuViews::HistoricCampaignOutro_Func::MenuView_HistoricCampaignOutro_DoEveryFrame::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_HistoricCampaignOutro::get());
    }

}
}
