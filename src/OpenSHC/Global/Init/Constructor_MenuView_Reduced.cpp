#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_00b974bc.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A170
    void Init::Constructor_MenuView_Reduced()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView_Reduced, DAT_00b974bc::ptr)(
            UI::Enums::MVT_NO_VIEW);
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_0059cd30));
        return;
    }

}
}
