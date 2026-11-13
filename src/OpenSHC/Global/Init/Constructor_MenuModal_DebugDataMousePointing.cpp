#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/DebugDataMousePointing.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_DebugDataMousePointing.hpp"
#include "OpenSHC/Globals/Menu_DebugModals.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B2E0
    void Init::Constructor_MenuModal_DebugDataMousePointing()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_DebugDataMousePointing::ptr)(
            UI::Enums::MMT_DEBUG_DATA_MOUSE_POINTING, 267, 3, 400, 142, 14, COL_WHITE::instance.shortValue,
            UI::MenuModals::DebugDataMousePointing_Func::MenuModalRenderFunction_DebugDataMousePointing::get(),
            Menu_DebugModals::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_DebugDataMousePointing::get());
    }

}
}
