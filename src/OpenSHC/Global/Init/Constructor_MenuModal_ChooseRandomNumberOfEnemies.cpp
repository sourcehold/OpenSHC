#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/ChooseRandomNumberOfEnemies.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_ChooseRandomNumberOfEnemies.hpp"
#include "OpenSHC/Globals/Menu_ChooseRandomNumberOfEnemies.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C2C0
    void Init::Constructor_MenuModal_ChooseRandomNumberOfEnemies()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_ChooseRandomNumberOfEnemies::ptr)(
            UI::Enums::MMT_CHOOSE_RANDOM_NUMBER_OF_ENEMIES, -1, -1, 600, 400, 512, COL_WHITE::instance.shortValue,
            UI::MenuModals::ChooseRandomNumberOfEnemies_Func::MenuModalRenderFunction_ChooseRandomNumberOfEnemies::
                get(),
            Menu_ChooseRandomNumberOfEnemies::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_ChooseRandomNumberOfEnemies::get());
    }

}
}
