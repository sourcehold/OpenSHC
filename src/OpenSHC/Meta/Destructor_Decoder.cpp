#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_DecoderState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D610
void Meta::Destructor_Decoder()
{
    ((void(__fastcall*)(DecoderState*))MACRO_CALL(Global_Func::DoNothing))(DAT_DecoderState::ptr);
}

}
