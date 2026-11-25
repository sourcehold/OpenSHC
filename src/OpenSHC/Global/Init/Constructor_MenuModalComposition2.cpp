#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"

#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CA80
    void Init::Constructor_MenuModalComposition2()
    {
        MACRO_CALL_MEMBER(
            UI::MenuModalComposition_Func::Constructor_MenuModalComposition, DAT_MenuModalComposition2::ptr)(1);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d690::get());
    }

}
}
