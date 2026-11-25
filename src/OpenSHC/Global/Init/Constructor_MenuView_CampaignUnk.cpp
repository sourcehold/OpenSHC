#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/CampaignUnk.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_CampaignUnk.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A5E0
    void Init::Constructor_MenuView_CampaignUnk()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_CampaignUnk::ptr)(
            UI::Enums::MVT_UNKNOWN_27_CAMPAIGNUnk, UI::MenuViews::CampaignUnk_Func::MenuView_CampaignUnk_Prepare::get(),
            UI::MenuViews::CampaignUnk_Func::MenuView_CampaignUnk_DoInitial::get(),
            UI::MenuViews::CampaignUnk_Func::MenuView_CampaignUnk_DoEveryFrame::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_CampaignUnk::get());
    }

}
}
