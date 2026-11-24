#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/AiLordSelect.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_BasicAiLordSelect.hpp"
#include "OpenSHC/Globals/Menu_BasicAiLordSelect.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C0A0
    void Init::Constructor_MenuModal_BasicAiLordSelect()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_BasicAiLordSelect::ptr)(
            UI::Enums::MMT_BASIC_AI_LORD_SELECT, 200, 200, 648, 288, 4160, COL_WHITE::instance.shortValue,
            UI::MenuModals::AiLordSelect_Func::MenuModalRenderFunction_AiLordSelect::get(),
            Menu_BasicAiLordSelect::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_BasicAiLordSelect::get());
    }

}
}
