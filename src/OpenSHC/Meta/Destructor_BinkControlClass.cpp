#include "../Meta.func.hpp"

#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"

#include "OpenSHC/Globals/DAT_BinkControlState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D790
void Meta::Destructor_BinkControlClass()
{
    MACRO_CALL_MEMBER(Rendering::Bink::BinkControlClass_Func::stopAllBinkPlaybackThunk, DAT_BinkControlState::ptr)();
}

}
