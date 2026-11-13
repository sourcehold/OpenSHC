#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/TacticalPowerBar.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModa_TacticalPowerBar.hpp"
#include "OpenSHC/Globals/Menu_TacticalPowerBar.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C340
    void Init::Constructor_MenuModal_TacticalPowerBar()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModa_TacticalPowerBar::ptr)(
            UI::Enums::MMT_TACTICAL_POWER_BAR, 745, 50, 55, 320, 4096, COL_WHITE::instance.shortValue,
            UI::MenuModals::TacticalPowerBar_Func::MenuModalRenderFunction_TacticalPowerBar::get(),
            Menu_TacticalPowerBar::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_TacticalPowerBar::get());
    }

}
}
