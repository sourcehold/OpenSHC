#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"

#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CA60
    void Init::Constructor_MenuModalComposition1()
    {
        MACRO_CALL_MEMBER(
            UI::MenuModalComposition_Func::Constructor_MenuModalComposition, DAT_MenuModalComposition1::ptr)(0);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d680::get());
    }

}
}
