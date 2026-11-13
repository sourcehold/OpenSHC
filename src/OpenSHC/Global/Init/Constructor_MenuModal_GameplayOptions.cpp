#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/GameplayOptions.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_GameplayOptions.hpp"
#include "OpenSHC/Globals/Menu_GameplayOptions.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B620
    void Init::Constructor_MenuModal_GameplayOptions()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_GameplayOptions::ptr)(
            UI::Enums::MMT_GAMEPLAY_OPTIONS, -1, -1, 500, 357, 512, COL_WHITE::instance.shortValue,
            UI::MenuModals::GameplayOptions_Func::MenuModalRenderFunction_GameplayOptions::get(),
            Menu_GameplayOptions::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_GameplayOptions::get());
    }

}
}
