#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/CrusadeMissionIntro.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_CrusadeMissionIntro.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A9A0
    void Init::Constructor_MenuView_CrusadeMissionIntro()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_CrusadeMissionIntro::ptr)(
            UI::Enums::MVT_CRUSADE_MISSION_INTRO,
            UI::MenuViews::CrusadeMissionIntro_Func::MenuView_CrusadeMissionIntro_Prepare::get(),
            UI::MenuViews::General_Func::MenuView_General_DoInitial_CrusadeAndRankMenu::get(),
            UI::MenuViews::CrusadeMissionIntro_Func::MenuView_CrusadeMissionIntro_DoEveryFrame::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_CrusadeMissionIntro::get());
    }

}
}
