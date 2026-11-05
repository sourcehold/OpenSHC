#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D7A0
void Meta::Destructor_0059d7a0()
{
    ((void(__fastcall*)(SoundSystem*))MACRO_CALL(Global_Func::DoNothing))(DAT_SoundSystemState::ptr);
}

}
