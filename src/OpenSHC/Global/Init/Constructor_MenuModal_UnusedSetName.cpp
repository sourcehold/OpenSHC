#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/UnusedSetName.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_UnusedSetName.hpp"
#include "OpenSHC/Globals/Menu_UnusedSetName.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B8E0
    void Init::Constructor_MenuModal_UnusedSetName()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_UnusedSetName::ptr)(
            UI::Enums::MMT_UNUSED_SET_NAME, -1, -1, 500, 150, 16, COL_WHITE::instance.shortValue,
            UI::MenuModals::UnusedSetName_Func::MenuModalRenderFunction_UnusedSetName::get(), Menu_UnusedSetName::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_UnusedSetName::get());
    }

}
}
