#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CC80
    void Init::Constructor_BinkControlClass()
    {
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_BinkControlClass::get());
    }

}
}
