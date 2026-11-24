#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/DebugDataAiInfo.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_DebugDataAiInfo.hpp"
#include "OpenSHC/Globals/Menu_DebugModals.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B1E0
    void Init::Constructor_MenuModal_DebugDataAiInfo()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_DebugDataAiInfo::ptr)(
            UI::Enums::MMT_DEBUG_DATA_AI_INFO, 10, 3, 780, 240, 14, COL_WHITE::instance.shortValue,
            UI::MenuModals::DebugDataAiInfo_Func::MenuModalRenderFunction_DebugDataAiInfo::get(),
            Menu_DebugModals::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_DebugDataAiInfo::get());
    }

}
}
