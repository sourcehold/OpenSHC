#include "../DecoderState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x00473C10
    int DecoderState::encodeData(int sizeUncompressed, undefined* src, undefined* dst)
    {
        this->sizeUncompressed = sizeUncompressed;
        MACRO_CALL_MEMBER(DecoderState_Func::doImplode, this)(
            (int*)&this->crc32, &this->sizeCompressed, src, dst + 0xc, sizeUncompressed);
        MACRO_CALL_MEMBER(LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(4, &this->sizeUncompressed, dst);
        MACRO_CALL_MEMBER(LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(4, &this->sizeCompressed, dst + 4);
        MACRO_CALL_MEMBER(LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(4, &this->crc32, dst + 8);
        return this->sizeCompressed + 0xc;
    }

}
}
