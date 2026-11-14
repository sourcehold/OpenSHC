#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_ResourceManager.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C8C0
    void Init::Constructor_ResourceManager()
    {
        MACRO_CALL_MEMBER(IO::ResourceManager_Func::Constructor_ResourceManager, DAT_ResourceManager::ptr)();
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d5b0::get());
    }

}
}
