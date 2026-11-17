#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/GreatestLord.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/MenuModal_GreatestLord.hpp"
#include "OpenSHC/Globals/Menu_GreatestLord.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C240
    void Init::Constructor_MenuModal_GreatestLord()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_GreatestLord::ptr)(
            UI::Enums::MMT_GREATEST_LORD, -1, -1, 600, 408, 512, COL_BLACK::instance.shortValue,
            UI::MenuModals::GreatestLord_Func::MenuModalRenderFunction_GreatestLord::get(), Menu_GreatestLord::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_GreatestLord::get());
    }

}
}
