#include "../LowLevelMemory.func.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046AE80
    void LowLevelMemory::putFileNameAndAppendFileExtension(char* sourceName, char* dest, char* extension)
    {
        /*
            for (char _charHolder = *sourceName; _charHolder != '.' && _charHolder != '\0'; ++sourceName) {
                *dest = _charHolder;
                ++dest;
            }
            *dest = '.';
            do {
                ++dest;
                *dest = *extension;
                ++extension;
            } while (*dest != '\0');
        */

        __asm
        {
            mov edi, dest
            mov esi, sourceName
        
        name_loop_start:
            mov al, [esi]
        
            cmp al, '.'
            je name_loop_end
            cmp al, 0
            je name_loop_end
        
            mov [edi], al
        
            add esi, 1
            add edi, 1
        
            jmp name_loop_start
        name_loop_end:

            mov al, '.'
            mov [edi], al
            add edi, 1
            mov esi, extension
        
        extension_loop_start:
            mov al, [esi]
            mov [edi], al
        
            cmp al, 0
            je extension_loop_end
        
            add esi, 1
            add edi, 1
        
            jmp extension_loop_start
        extension_loop_end:
        }
    }

}
}
