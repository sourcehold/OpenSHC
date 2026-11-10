#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D770
void Meta::Destructor_0059d770()
{
    ((void(__fastcall*)(MenuTextInputState*))MACRO_CALL(Global_Func::DoNothing))(DAT_MenuTextInputState::ptr);
}

}
