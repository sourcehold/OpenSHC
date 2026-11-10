#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // The pattern's colours in RGB565 (red << 11 | green << 5 | blue); black is 0.
        enum {
            PATTERN_GREY = (15 << 11) | (30 << 5) | 15,
            PATTERN_WHITE = (31 << 11) | (63 << 5) | 31,
            PATTERN_DARK_GREY = (7 << 11) | (14 << 5) | 7
        };

        // FUNCTION: STRONGHOLDCRUSADER 0x00468F70
        void PencilRenderCore::drawPixelPattern4x4(int drawX, int drawY)
        {
            // The asm below names DAT_PencilRenderCore, which inline asm can only do once C++ code has instantiated
            // it; sizeof does that without generating any code.
            (void)sizeof(DAT_PencilRenderCore::instance);
            // A 4x4 pattern at (drawX, drawY), on the global pencil's surface, not on this one's, two pixels per store,
            // the left one in the low word. Handwritten assembly in the original, transcribed from the binary.
            __asm {
                mov edi, DAT_PencilRenderCore::instance.surfacePtr
                mov eax, drawX
                add eax, eax
                add edi, eax
                mov eax, drawY
                mov edx, DAT_PencilRenderCore::instance.horizontalByteSize
                mul edx
                add edi, eax
                mov ecx, 0
                mov edx, DAT_PencilRenderCore::instance.horizontalByteSize
                mov eax, PATTERN_GREY + PATTERN_WHITE * 65536
                mov ebx, PATTERN_DARK_GREY * 65536
                mov dword ptr [edi + ecx], eax
                mov dword ptr [edi + ecx + 4], ebx
                add ecx, edx
                mov eax, PATTERN_GREY + PATTERN_GREY * 65536
                mov dword ptr [edi + ecx], eax
                mov dword ptr [edi + ecx + 4], ebx
                add ecx, edx
                mov eax, PATTERN_DARK_GREY + PATTERN_DARK_GREY * 65536
                mov dword ptr [edi + ecx], eax
                mov dword ptr [edi + ecx + 4], ebx
                add ecx, edx
                mov eax, 0
                mov dword ptr [edi + ecx], eax
                mov dword ptr [edi + ecx + 4], eax
            }
        }

    }
}
}
