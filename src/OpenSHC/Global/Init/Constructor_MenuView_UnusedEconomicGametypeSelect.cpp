#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/UnusedEconomicGametypeSelect.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_UnusedEconomicGametypeSelect.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A790
    void Init::Constructor_MenuView_UnusedEconomicGametypeSelect()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_UnusedEconomicGametypeSelect::ptr)(
            UI::Enums::MVT_UNUSED_ECONOMIC_GAMETYPE_SELECT,
            UI::MenuViews::UnusedEconomicGametypeSelect_Func::MenuView_UnusedEconomicGametypeSelect_Prepare::get(),
            UI::MenuViews::UnusedEconomicGametypeSelect_Func::MenuView_UnusedEconomicGametypeSelect_DoInitial::get(),
            UI::MenuViews::General_Func::MenuView_General_DoEveryFrame_FirstGfxCentered::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_UnusedEconomicGametypeSelect::get());
    }

}
}
