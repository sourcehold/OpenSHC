#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_Unknown21.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A2B0
    void Init::Constructor_MenuView_Unknown21()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_Unknown21::ptr)(UI::Enums::MVT_UNKNOWN_21,
            UI::Helpers_Func::MainMenu_Unknown21_Prepare::get(),
            UI::MenuViews::General_Func::MenuView_General_DoInitial_DefaultMainMenuStructure::get(),
            UI::MenuViews::General_Func::MenuView_General_DoEveryFrame_FirstGfxCentered::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_Unknown21::get());
    }

}
}
