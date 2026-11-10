#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_ScrollingHandler.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D520
void Meta::Destructor_ScrollingHandler()
{
    ((void(__fastcall*)(ScrollingHandler*))MACRO_CALL(Global_Func::DoNothing))(DAT_ScrollingHandler::ptr);
}

}
