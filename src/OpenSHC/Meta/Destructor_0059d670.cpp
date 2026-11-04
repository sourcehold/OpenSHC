#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D670
void Meta::Destructor_0059d670()
{
    ((void(__fastcall*)(MinimapViewState*))MACRO_CALL(Global_Func::DoNothing))(DAT_MinimapViewState::ptr);
}

}
