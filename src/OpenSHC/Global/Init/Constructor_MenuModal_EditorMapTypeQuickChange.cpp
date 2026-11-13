#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/MenuModal_EditorMapTypeQuickChange.hpp"
#include "OpenSHC/Globals/Menu_EditorMapTypeQuickChange.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BDE0
    void Init::Constructor_MenuModal_EditorMapTypeQuickChange()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_EditorMapTypeQuickChange::ptr)(
            UI::Enums::MMT_EDITOR_MAP_TYPE_QUICK_CHANGE, -1, -1, 400, 300, 512, COL_BLACK::instance.shortValue,
            (UI::MenuModalRenderFunction*)Global_Func::DoNothing::get(), Menu_EditorMapTypeQuickChange::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_EditorMapTypeQuickChange::get());
    }

}
}
