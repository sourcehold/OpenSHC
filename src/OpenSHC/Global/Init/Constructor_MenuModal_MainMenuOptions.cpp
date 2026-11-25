#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/OptionsMenu.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_MainMenuOptions.hpp"
#include "OpenSHC/Globals/Menu_MainMenuOptions.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B5E0
    void Init::Constructor_MenuModal_MainMenuOptions()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_MainMenuOptions::ptr)(
            UI::Enums::MMT_MAIN_MENU_OPTIONS, -1, -1, 500, 357, 512, COL_WHITE::instance.shortValue,
            UI::MenuModals::OptionsMenu_Func::MenuModalRenderFunction_OptionsMenu::get(), Menu_MainMenuOptions::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_MainMenuOptions::get());
    }

}
}
