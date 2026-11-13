#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/GameStartEnterName.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_GameStartEnterName.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A700
    void Init::Constructor_MenuView_GameStartEnterName()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_GameStartEnterName::ptr)(
            UI::Enums::MVT_GAME_START_ENTER_NAME,
            UI::MenuViews::GameStartEnterName_Func::MenuView_GameStartEnterName_Prepare::get(),
            UI::MenuViews::GameStartEnterName_Func::MenuView_GameStartEnterName_DoInitial::get(),
            UI::MenuViews::GameStartEnterName_Func::MenuView_GameStartEnterName_DoEveryFrame::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_GameStartEnterName::get());
    }

}
}
