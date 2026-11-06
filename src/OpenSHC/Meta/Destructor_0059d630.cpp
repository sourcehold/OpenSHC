#include "../Meta.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D630
void Meta::Destructor_0059d630() { MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::freeMemoryAt, DAT_SFXState::ptr)(); }

}
