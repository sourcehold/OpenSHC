#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/SkirmishConnectionOptions.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/MenuModal_SkirmishConnectionOptions.hpp"
#include "OpenSHC/Globals/Menu_SkirmishConnectionOptions.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BE20
    void Init::Constructor_MenuModal_SkirmishConnectionOptions()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_SkirmishConnectionOptions::ptr)(
            UI::Enums::MMT_SKIRMISH_CONNECTION_OPTIONS, -1, -1, 408, 200, 512, COL_BLACK::instance.shortValue,
            UI::MenuModals::SkirmishConnectionOptions_Func::MenuModalRenderFunction_SkirmishConnectionOptions::get(),
            Menu_SkirmishConnectionOptions::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_SkirmishConnectionOptions::get());
    }

}
}
