#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D6B0
void Meta::Destructor_0059d6b0()
{
    ((void(__fastcall*)(TileMapState*))MACRO_CALL(Global_Func::DoNothing))(DAT_TileMapState::ptr);
}

}
