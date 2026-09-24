#include "OpenSHC/IO/DecoderState.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"

#include "OpenSHC/Globals/DAT_DecoderState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047E800
    void GameSynchronyState::decompressTooLongPacketData(byte* source, byte* destination)
    {
        size_t const size = MACRO_CALL_MEMBER(OpenSHC::IO::DecoderState_Func::decompressRLE, DAT_DecoderState::ptr)(
            (char*)source, (char*)this->DAT_PacketDecodingDestination);
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
            size, this->DAT_PacketDecodingDestination, destination);
    }

}
}
