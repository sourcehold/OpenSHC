#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/Roundtable.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_Roundtable.hpp"
#include "OpenSHC/Globals/Menu_Roundtable.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C140
    void Init::Constructor_MenuModal_Roundtable()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_Roundtable::ptr)(
            UI::Enums::MMT_ROUNDTABLE, 4, 4, 792, 432, 4608, COL_WHITE::instance.shortValue,
            UI::MenuModals::Roundtable_Func::MenuModalRenderFunction_Roundtable::get(), Menu_Roundtable::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_Roundtable::get());
    }

}
}
