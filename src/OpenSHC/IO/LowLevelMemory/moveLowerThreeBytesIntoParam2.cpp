#include "../LowLevelMemory.func.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046A830
    void LowLevelMemory::moveLowerThreeBytesIntoParam2(void* src, void* dst)
    {
        /*
            short param1 = ((short*)src)[0];
            byte param2 = ((char*)src)[2];
            ((short*)dst)[0] = param1;
            ((char*)dst)[2] = param2;
        */

        __asm {
            mov edi, [dst]
            mov esi, [src]

            mov ax, word ptr [esi]
            mov bl, byte ptr [esi + 2]
            mov word ptr [edi], ax
            mov byte ptr [edi + 2], bl
        }
    }

}
}
