#include "OpenSHC/IO/LowLevelMemory.func.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046AE50
    void LowLevelMemory::copyStringUntilFirstDot(char* source, char* destination)
    {
        __asm
        {
            mov edi, destination
            mov esi, source
        
         loop_start:
            mov al, [esi]
            
            cmp al, '.'
            je loop_end
            cmp al, 0
            je loop_end
        
            mov [edi], al
        
            add esi, 1
            add edi, 1
        
            jmp loop_start
         loop_end:
        }
    }

}
}
