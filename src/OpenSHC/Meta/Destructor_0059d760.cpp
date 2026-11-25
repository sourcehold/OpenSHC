#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D760
void Meta::Destructor_0059d760()
{
    ((void(__fastcall*)(GameStateStructures*))MACRO_CALL(Global_Func::DoNothing))(DAT_GameState::ptr);
}

}
