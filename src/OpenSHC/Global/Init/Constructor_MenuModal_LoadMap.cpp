#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/LoadMap.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_LoadMap.hpp"
#include "OpenSHC/Globals/Menu_LoadMap.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B4A0
    void Init::Constructor_MenuModal_LoadMap()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_LoadMap::ptr)(UI::Enums::MMT_LOAD_MAP,
            -1, -1, 700, 397, 512, COL_WHITE::instance.shortValue,
            UI::MenuModals::LoadMap_Func::MenuModalRenderFunction_LoadMap::get(), Menu_LoadMap::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_LoadMap::get());
    }

}
}
