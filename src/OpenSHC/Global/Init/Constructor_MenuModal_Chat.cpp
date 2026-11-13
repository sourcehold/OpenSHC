#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/Chat.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/MenuModal_Chat.hpp"
#include "OpenSHC/Globals/Menu_Chat.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BD60
    void Init::Constructor_MenuModal_Chat()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_Chat::ptr)(UI::Enums::MMT_CHAT, 16, 16,
            768, 224, 512, COL_BLACK::instance.shortValue,
            UI::MenuModals::Chat_Func::MenuModalRenderFunction_Chat::get(), Menu_Chat::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_Chat::get());
    }

}
}
