#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/MenuModal_UnusedWinCondition.hpp"
#include "OpenSHC/Globals/Menu_UnusedWinCondition.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B160
    void Init::Constructor_MenuModal_UnusedWinCondition()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_UnusedWinCondition::ptr)(
            UI::Enums::MMT_UNUSED_WIN_CONDITION, 0, 0, 240, 0, 0, 0,
            (UI::MenuModalRenderFunction*)Global_Func::DoNothing::get(), Menu_UnusedWinCondition::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_UnusedWinCondition::get());
    }

}
}
