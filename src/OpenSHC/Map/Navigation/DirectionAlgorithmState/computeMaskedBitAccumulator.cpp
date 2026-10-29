#include "../DirectionAlgorithmState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          The original is hand-written assembly (like computeHash), equivalent to:
            uint hash = 0;
            while (byteCount > 3) {
                hash += *address++ & mask;
                hash = (hash << 1) | (hash >> 31);
                byteCount -= 4;
            }
            return hash;
        */
        // FUNCTION: STRONGHOLDCRUSADER 0x0046CDF0
        uint DirectionAlgorithmState::computeMaskedBitAccumulator(int byteCount, uint* address, uint mask)
        {
            uint hash = 0;
            __asm {
                mov esi, address
                mov edx, byteCount
                mov ebx, mask
                mov ecx, 0

            word_loop:
                cmp edx, 3
                jle finished
                mov eax, [esi]
                and eax, ebx
                add ecx, eax
                rol ecx, 1
                add esi, 4
                sub edx, 4
                jmp word_loop

            finished:
                mov hash, ecx
            }
            return hash;
        }

    }
}
}
