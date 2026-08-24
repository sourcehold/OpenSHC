#include "OpenSHC/IO/DecoderState.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"

#include "OpenSHC/Globals/DAT_DecoderState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Synchrony {

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */

    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */

    // FUNCTION: STRONGHOLDCRUSADER 0x0047E800
    void GameSynchronyState::decompressTooLongPacketData(byte* source, byte* destination)

    {
        size_t _size;

        _size = MACRO_CALL_MEMBER(OpenSHC::IO::DecoderState_Func::decompressRLE, DAT_DecoderState::ptr)(
            (char*)source, (char*)((int)(this->DAT_PacketDecodingDestination)));
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
            _size, (void*)((int)(this->DAT_PacketDecodingDestination)), destination);
        return;
    }

}
}
