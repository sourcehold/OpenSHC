#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/MapEditorLandscaping.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_MapEditorLandscaping.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A3D0
    void Init::Constructor_MenuView_MapEditorLandscaping()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_MapEditorLandscaping::ptr)(
            UI::Enums::MVT_MAP_EDITOR_LANDSCAPING,
            UI::MenuViews::MapEditorLandscaping_Func::MenuView_MapEditorLandscaping_Prepare::get(),
            UI::MenuViews::MapEditorLandscaping_Func::MenuView_MapEditorLandscaping_DoInitial::get(),
            UI::MenuViews::MapEditorLandscaping_Func::MenuView_MapEditorLandscaping_DoEveryFrame::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_MapEditorLandscaping::get());
    }

}
}
