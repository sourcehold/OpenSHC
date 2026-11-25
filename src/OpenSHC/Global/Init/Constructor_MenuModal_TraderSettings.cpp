#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/TraderSettings.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/MenuModal_TraderSettings.hpp"
#include "OpenSHC/Globals/Menu_TraderSettings.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B960
    void Init::Constructor_MenuModal_TraderSettings()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_TraderSettings::ptr)(
            UI::Enums::MMT_TRADER_SETTINGS, -1, -1, 600, 390, 512, 6,
            UI::MenuModals::TraderSettings_Func::MenuModalRenderFunction_TraderSettings::get(),
            Menu_TraderSettings::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_TraderSettings::get());
    }

}
}
