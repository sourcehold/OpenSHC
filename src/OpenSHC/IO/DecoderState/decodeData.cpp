#include "../DecoderState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x00473C70
    dword DecoderState::decodeData(void* source, void* destination)
    {
        void* sourcePtr = source;
        MACRO_CALL_MEMBER(LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
            4, sourcePtr, &this->sizeUncompressed);
        MACRO_CALL_MEMBER(LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
            4, (void*)((int)sourcePtr + 4), &this->sizeCompressed);
        MACRO_CALL_MEMBER(LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
            4, (void*)((int)sourcePtr + 8), &source);
        MACRO_CALL_MEMBER(DecoderState_Func::doExplode, this)((int*)&this->crc32, (undefined*)((int)sourcePtr + 12),
            this->sizeCompressed, (undefined*)destination, this->sizeUncompressed);
        /* source became hash */
        if (source != (void*)this->crc32) {
            return 0;
        }
        return this->sizeUncompressed;
    }

}
}
