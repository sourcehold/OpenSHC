#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/AiLordSelect.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_ExtendedAiLordSelect.hpp"
#include "OpenSHC/Globals/Menu_ExtendedAiLordSelect.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C0F0
    void Init::Constructor_MenuModal_ExtendedAiLordSelect()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_ExtendedAiLordSelect::ptr)(
            UI::Enums::MMT_EXTENDED_AI_LORD_SELECT, 200, 200, 648, 364, 4160, COL_WHITE::instance.shortValue,
            UI::MenuModals::AiLordSelect_Func::MenuModalRenderFunction_AiLordSelect::get(),
            Menu_ExtendedAiLordSelect::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_ExtendedAiLordSelect::get());
    }

}
}
