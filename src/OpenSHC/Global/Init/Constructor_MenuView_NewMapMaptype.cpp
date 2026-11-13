#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/NewMapMaptype.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_NewMapMaptype.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A4C0
    void Init::Constructor_MenuView_NewMapMaptype()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_NewMapMaptype::ptr)(
            UI::Enums::MVT_NEW_MAP_MAPTYPE, UI::MenuViews::NewMapMaptype_Func::MenuView_NewMapMaptype_Prepare::get(),
            UI::MenuViews::General_Func::MenuView_General_DoInitial_DefaultMainMenuStructure::get(),
            UI::MenuViews::General_Func::MenuView_General_DoEveryFrame_FirstGfxCentered::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_NewMapMaptype::get());
    }

}
}
