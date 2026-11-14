#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/DebugDataAivStateUnk.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_DebugDataAivStateUnk.hpp"
#include "OpenSHC/Globals/Menu_DebugModals.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C380
    void Init::Constructor_MenuModal_DebugDataAivStateUnk()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_DebugDataAivStateUnk::ptr)(
            UI::Enums::MMT_DEBUG_DATA_AIV_STATEUnk, 267, 3, 400, 242, 14, COL_WHITE::instance.shortValue,
            UI::MenuModals::DebugDataAivStateUnk_Func::MenuModalRenderFunction_DebugDataAivStateUnk::get(),
            Menu_DebugModals::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_DebugDataAivStateUnk::get());
    }

}
}
