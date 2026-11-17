#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/DisplayAiLordMessage.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_DisplayAiLordMessage.hpp"
#include "OpenSHC/Globals/Menu_DisplayAiLordMessage.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B860
    void Init::Constructor_MenuModal_DisplayAiLordMessage()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_DisplayAiLordMessage::ptr)(
            UI::Enums::MMT_DISPLAY_AI_LORD_MESSAGE, 0, 0, 0, 0, 64, COL_WHITE::instance.shortValue,
            UI::MenuModals::DisplayAiLordMessage_Func::MenuModalRenderFunction_DisplayAiLordMessage::get(),
            Menu_DisplayAiLordMessage::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_DisplayAiLordMessage::get());
    }

}
}
