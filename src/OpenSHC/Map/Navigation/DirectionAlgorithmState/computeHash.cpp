#include "../DirectionAlgorithmState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x0046CD30
        uint DirectionAlgorithmState::computeHash(int byteCount, int* address)
        {
            // Equivalent operation for each complete word (unsigned wraparound):
            // hash += static_cast<uint>(*address++);
            // hash = (hash << 1) | (hash >> 31);
            // The original has an assembly-shaped, sixteen-word unrolled loop.
            // Keep it explicit like IO/DecoderState's native codec routines.
            uint hash = 0;
            __asm {
                mov esi, address
                mov edx, byteCount
                mov ecx, 0

            block_loop:
                cmp edx, 64
                jl trailing_words
                mov eax, [esi + 0]
                mov ebx, [esi + 4]
                add ecx, eax
                rol ecx, 1
                add ecx, ebx
                rol ecx, 1
                mov eax, [esi + 8]
                mov ebx, [esi + 12]
                add ecx, eax
                rol ecx, 1
                add ecx, ebx
                rol ecx, 1
                mov eax, [esi + 16]
                mov ebx, [esi + 20]
                add ecx, eax
                rol ecx, 1
                add ecx, ebx
                rol ecx, 1
                mov eax, [esi + 24]
                mov ebx, [esi + 28]
                add ecx, eax
                rol ecx, 1
                add ecx, ebx
                rol ecx, 1
                mov eax, [esi + 32]
                mov ebx, [esi + 36]
                add ecx, eax
                rol ecx, 1
                add ecx, ebx
                rol ecx, 1
                mov eax, [esi + 40]
                mov ebx, [esi + 44]
                add ecx, eax
                rol ecx, 1
                add ecx, ebx
                rol ecx, 1
                mov eax, [esi + 48]
                mov ebx, [esi + 52]
                add ecx, eax
                rol ecx, 1
                add ecx, ebx
                rol ecx, 1
                mov eax, [esi + 56]
                mov ebx, [esi + 60]
                add ecx, eax
                rol ecx, 1
                add ecx, ebx
                rol ecx, 1
                add esi, 64
                sub edx, 64
                jmp block_loop

            trailing_words:
                cmp edx, 3
                jle finished
                mov eax, [esi]
                add ecx, eax
                rol ecx, 1
                add esi, 4
                sub edx, 4
                jmp trailing_words

            finished:
                mov hash, ecx
            }
            return hash;
        }

    } // namespace Navigation
} // namespace Map
} // namespace OpenSHC
