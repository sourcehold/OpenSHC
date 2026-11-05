#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/FilePackagerObj.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D600
void Meta::Destructor_0059d600()
{
    ((void(__fastcall*)(FilePackager*))MACRO_CALL(Global_Func::DoNothing))(FilePackagerObj::ptr);
}

}
