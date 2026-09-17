#include "../DecoderState.func.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046D150
    int DecoderState::compressRLE(char* src, void* dst, int inputSize)
    {

        /*
        // Roughly this logic:

            *(int*)(dst + 4) = inputSize;
            char* runDst = dst + 8;
            int compressedSize = 8;
            while (size > 0) {
                if (src[1] == *src && src[2] == *src) {
                    int repeatedBytes = 0;
                    compressedSize += 3;
                    char currentByte = *src;
                    while (*src == currentByte) {
                        ++src;
                        ++repeatedBytes;
                        --size;
                        if (size <= 0 || 0x7fff <= repeatedBytes) break;
                    }
                    *(unsigned short*)runDst = (unsigned short)repeatedBytes - 1;
                    *(runDst + 2) = currentByte;
                    runDst += 3;
                    continue;
                }
                int numberOfBytes = 0;
                compressedSize = compressedSize + 2;
                char* forwardSrc = *src;
                while (forwardSrc[1] != *forwardSrc || forwardSrc[2] != *forwardSrc) {
                    ++forwardSrc;
                    ++numberOfBytes;
                    ++compressedSize;
                    --size;
                    if (size <= 0 || 0x7fff <= numberOfBytes) break;
                }
                *(unsigned short*)runDst = ((unsigned short)numberOfBytes - 1) | 0x8000; // sets also marker bit
                runDst += 2;
                memcpy(runDst, src, numberOfBytes);
                runDst += numberOfBytes;
                src += numberOfBytes;
            }
        */

        int compressedSize;

        // ESI = src
        // EDI = dst
        // EBX = size
        // EDX = output size
        __asm {

            mov     edi, dst
            mov     ebx, inputSize
            mov     [edi+4], ebx
            push    edi
            add     edi, 8
            mov     edx, 8
            mov     esi, src

        main_loop:
            cmp     ebx, 0
            jle     finish
            mov     al, [esi]
            cmp     [esi+1], al
            jne     literal
            cmp     [esi+2], al
            jne     literal
            mov     ecx, 0
            add     edx, 3
            mov     al, [esi]

        rle_loop:
            cmp     [esi], al
            jne     write_run
            inc     esi
            inc     ecx
            sub     ebx, 1
            cmp     ebx, 0
            jle     write_run
            cmp     ecx, 0x7fff
            jl      rle_loop

        write_run:
            mov     [edi+2], al
            mov     eax, ecx
            sub     eax, 1
            mov     [edi], ax
            add     edi, 3
            jmp     main_loop

        literal:
            mov     ecx, 0
            add     edx, 2
            push    esi

        literal_loop:
            mov     al, [esi]
            cmp     [esi+1], al
            jne     copy_literal
            cmp     [esi+2], al
            jne     copy_literal
            jmp     finish_literal

        copy_literal:
            inc     esi
            inc     ecx
            add     edx, 1
            sub     ebx, 1
            cmp     ebx, 0
            jle     finish_literal
            cmp     ecx, 0x7fff
            jl      literal_loop


        finish_literal:
            pop     esi
            mov     eax, ecx
            sub     eax, 1
            or      ax, 0x8000
            mov     [edi], ax
            inc     edi
            inc     edi
            rep movsb
            jmp     main_loop

        finish:
            mov     compressedSize, edx
            pop     edi
            mov     [edi], edx
        }

        return compressedSize;
    }

}
}
