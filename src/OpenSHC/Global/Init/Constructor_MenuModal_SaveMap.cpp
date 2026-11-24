#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/SaveMap.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_SaveMap.hpp"
#include "OpenSHC/Globals/Menu_SaveMap.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B4E0
    void Init::Constructor_MenuModal_SaveMap()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_SaveMap::ptr)(UI::Enums::MMT_SAVE_MAP,
            -1, -1, 700, 397, 512, COL_WHITE::instance.shortValue,
            UI::MenuModals::SaveMap_Func::MenuModalRenderFunction_SaveMap::get(), Menu_SaveMap::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_SaveMap::get());
    }

}
}
