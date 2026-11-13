#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"

#include "OpenSHC/Globals/DAT_MenuModalComposition3.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CAA0
    void Init::Constructor_MenuModalComposition3()
    {
        MACRO_CALL_MEMBER(
            UI::MenuModalComposition_Func::Constructor_MenuModalComposition, DAT_MenuModalComposition3::ptr)(2);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d6a0::get());
    }

}
}
