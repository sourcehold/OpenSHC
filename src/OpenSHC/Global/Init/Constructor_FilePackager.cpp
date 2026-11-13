#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/IO/FilePackager.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/FilePackagerObj.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C960
    void Init::Constructor_FilePackager()
    {
        MACRO_CALL_MEMBER(IO::FilePackager_Func::Constructor_FilePackager, FilePackagerObj::ptr)();
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d600::get());
    }

}
}
