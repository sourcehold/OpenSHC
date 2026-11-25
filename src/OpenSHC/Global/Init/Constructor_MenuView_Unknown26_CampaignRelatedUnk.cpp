#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/Unknown26.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_Unknown26_CampaignRelatedUnk.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A5B0
    void Init::Constructor_MenuView_Unknown26_CampaignRelatedUnk()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_Unknown26_CampaignRelatedUnk::ptr)(
            UI::Enums::MVT_UNKNOWN_26_CAMPAIGN_RELATEDUnk,
            UI::MenuViews::Unknown26_Func::MenuView_Unknown26_CampaignRelatedUnk_Prepare::get(),
            UI::MenuViews::Unknown26_Func::MenuView_Unknown26_CampaignRelatedUnk_DoInitial::get(),
            UI::MenuViews::Unknown26_Func::MenuView_Unknown26_CampaignRelatedUnk_DoEveryFrame::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_Unknown26_CampaignRelatedUnk::get());
    }

}
}
