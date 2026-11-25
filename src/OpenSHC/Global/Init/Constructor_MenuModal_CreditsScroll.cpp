#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/CreditsScroll.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/MenuModal_CreditsScroll.hpp"
#include "OpenSHC/Globals/Menu_Credits.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BDA0
    void Init::Constructor_MenuModal_CreditsScroll()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_CreditsScroll::ptr)(
            UI::Enums::MMT_CREDITS_SCROLL, 400, 0, 400, 600, 64, COL_BLACK::instance.shortValue,
            UI::MenuModals::CreditsScroll_Func::MenuModalRenderFunction_CreditsScroll::get(), Menu_Credits::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_CreditsScroll::get());
    }

}
}
