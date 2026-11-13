#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/UnusedSomeMissionStartUnk.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_UnusedSomeMissionStartUnk.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A220
    void Init::Constructor_MenuView_UnusedSomeMissionStartUnk()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_UnusedSomeMissionStartUnk::ptr)(
            UI::Enums::MVT_UNUSED_SOME_MISSION_STARTUnk,
            UI::MenuViews::UnusedSomeMissionStartUnk_Func::MenuView_UnusedSomeMissionStartUnk_Prepare::get(),
            UI::MenuViews::General_Func::MenuView_General_DoInitial_DefaultMainMenuStructure::get(),
            UI::MenuViews::General_Func::MenuView_General_DoEveryFrame_FirstGfxCentered::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_UnusedSomeMissionStartUnk::get());
    }

}
}
