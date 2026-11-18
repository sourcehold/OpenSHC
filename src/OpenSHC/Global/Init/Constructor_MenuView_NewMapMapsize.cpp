#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/NewMapMapsize.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_NewMapMapsize.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A4F0
    void Init::Constructor_MenuView_NewMapMapsize()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_NewMapMapsize::ptr)(
            UI::Enums::MVT_NEW_MAP_MAPSIZE, UI::MenuViews::NewMapMapsize_Func::MenuView_NewMapMapsize_Prepare::get(),
            UI::MenuViews::General_Func::MenuView_General_DoInitial_DefaultMainMenuStructure::get(),
            UI::MenuViews::NewMapMapsize_Func::MenuView_NewMapMapsize_DoEveryFrame::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_NewMapMapsize::get());
    }

}
}
