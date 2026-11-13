#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/UnusedChooseGameType.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_UnusedChooseGameType.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A550
    void Init::Constructor_MenuView_UnusedChooseGameType()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_UnusedChooseGameType::ptr)(
            UI::Enums::MVT_UNUSED_CHOOSE_GAME_TYPE, Global_Func::DoNothing::get(),
            UI::MenuViews::General_Func::MenuView_General_DoInitial_ScreenToBlack::get(),
            UI::MenuViews::UnusedChooseGameType_Func::MenuView_UnusedChooseGameType_DoEveryFrame::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_UnusedChooseGameType::get());
    }

}
}
