#include "../DecoderState.func.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046D200
    int DecoderState::decompressRLE(char* src, char* dst)
    {
        /*
        // Roughly this logic:

            int uncompressedSizeCounted = 0;
            int uncompressedSizeWritten = *(int*)((int)src + 4);
            src += 8;
            while (0 < uncompressedSizeWritten) {
                if ((*(unsigned short*)src & 0x8000) == 0) {
                    char const currentByte = *(src + 2);
                    int numberOfBytes = (*(unsigned short*)src & 0x7fff) + 1;
                    uncompressedSizeCounted += numberOfBytes;
                    src += 3;
                    uncompressedSizeWritten -= numberOfBytes;
                    memset(dst, currentByte, numberOfBytes);
                    dst += numberOfBytes;
                } else {
                    int numberOfBytes = (*(unsigned short*)src & 0x7fff) + 1;
                    uncompressedSizeCounted += numberOfBytes;
                    uncompressedSizeWritten -= numberOfBytes;
                    src += 2;
                    memcpy(dst, src, numberOfBytes);
                    src += numberOfBytes;
                    dst += numberOfBytes;
                }
            }
            return uncompressedSizeCounted;
        */

        int uncompressedSizeCounted;

        // ESI = src
        // EDI = dst
        // EBX = written size
        // EDX = counting size
        __asm {

            mov     esi, src
            mov     edx, 0
            mov     ebx, [esi + 4]
            add     esi, 8
            mov     edi, dst

        main_loop:
            cmp     ebx, 0
            jle     finish

                // check_type:
            mov     ax, [esi]
            and     ax, 0x8000
            cmp     ax, 0
            jnz     uncompress_literal

                // uncompress_rle:
            mov     cx, [ESI]
            mov     al, [ESI + 0x2]
            and     ecx, 0x7fff
            inc     ecx
            add     edx, ecx
            add     esi, 0x3
            sub     ebx, ecx
            rep stosb
            jmp     main_loop

        uncompress_literal:
            mov     cx, [ESI]
            and     ecx, 0x7fff
            inc     ecx
            add     edx, ecx
            add     esi, 0x2
            sub     ebx, ecx
            rep movsb
            jmp     main_loop

        finish:
            mov     uncompressedSizeCounted, edx
        }

        return uncompressedSizeCounted;
    }

}
}
