#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x00488480
void Synchrony::MemCopyFromParameter(char* dest, size_t size, undefined4 playerID)
{
    char message[1000];
    char* const received = (char*)MACRO_CALL(OpenSHC::OS_Func::_malloc)(size);
    MACRO_CALL_MEMBER(
        Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter, DAT_GameSynchronyState::ptr)(
        received, size, Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
    for (int i = 0; i < (int)size; ++i) {
        if (received[i] != dest[i]) {
            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(
                message, s_ID_d_OF_d_M_d_S_d_005a72d8, playerID, i, (int)received[i], (int)dest[i]);
        }
        dest[i] = received[i];
    }
    MACRO_CALL(OpenSHC::OS_Func::_free_base)(received);
}

}
