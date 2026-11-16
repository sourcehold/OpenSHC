#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/BuildingAvailability.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/MenuModal_BuildingAvailability.hpp"
#include "OpenSHC/Globals/Menu_BuildingAvailability.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BBA0
    void Init::Constructor_MenuModal_BuildingAvailability()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_BuildingAvailability::ptr)(
            UI::Enums::MMT_BUILDING_AVAILABILITY, -1, -1, 700, 540, 512, 6,
            UI::MenuModals::BuildingAvailability_Func::MenuModalRenderFunction_BuildingAvailability::get(),
            Menu_BuildingAvailability::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_BuildingAvailability::get());
    }

}
}
