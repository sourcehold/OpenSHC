#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/IO/DecoderState.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_DecoderState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C980
    void Init::Constructor_DecoderState()
    {
        MACRO_CALL_MEMBER(IO::DecoderState_Func::Constructor_DecoderState, DAT_DecoderState::ptr)();
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_Decoder::get());
    }

}
}
