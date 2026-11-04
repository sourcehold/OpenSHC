#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_ResourceManager.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D5B0
void Meta::Destructor_0059d5b0()
{
    ((void(__fastcall*)(ResourceManager*))MACRO_CALL(Global_Func::DoNothing))(DAT_ResourceManager::ptr);
}

}
