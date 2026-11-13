#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/EnterTitleOnGameStart.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_EnterTitleOnGameStart.hpp"
#include "OpenSHC/Globals/Menu_EnterTitleOnGameStart.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B6A0
    void Init::Constructor_MenuModal_EnterTitleOnGameStart()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_EnterTitleOnGameStart::ptr)(
            UI::Enums::MMT_ENTER_TITLE_ON_GAME_START, -1, 100, 500, 200, 512, COL_WHITE::instance.shortValue,
            UI::MenuModals::EnterTitleOnGameStart_Func::MenuModalRenderFunction_EnterTitleOnGameStart::get(),
            Menu_EnterTitleOnGameStart::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_EnterTitleOnGameStart::get());
    }

}
}
