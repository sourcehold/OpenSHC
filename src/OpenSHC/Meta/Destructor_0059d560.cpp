#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D560
void Meta::Destructor_0059d560()
{
    ((void(__fastcall*)(TextManager*))MACRO_CALL(Global_Func::DoNothing))(DAT_TextManagerObject::ptr);
}

}
