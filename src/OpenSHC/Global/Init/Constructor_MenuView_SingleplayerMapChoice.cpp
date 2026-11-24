#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/SingleplayerMapChoice.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_SingleplayerMapChoice.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A370
    void Init::Constructor_MenuView_SingleplayerMapChoice()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_SingleplayerMapChoice::ptr)(
            UI::Enums::MVT_SINGLEPLAYER_MAP_CHOICE,
            UI::MenuViews::SingleplayerMapChoice_Func::MenuView_SingleplayerMapChoice_Prepare::get(),
            UI::MenuViews::General_Func::MenuView_General_DoInitial_DefaultMainMenuStructure::get(),
            UI::MenuViews::SingleplayerMapChoice_Func::MenuView_SingleplayerMapChoice_DoEveryFrame::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_SingleplayerMapChoice::get());
    }

}
}
