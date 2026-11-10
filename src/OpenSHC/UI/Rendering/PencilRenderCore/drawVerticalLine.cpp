#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00468E40
        void PencilRenderCore::drawVerticalLine()
        {
            // The asm below names DAT_PencilRenderCore, which inline asm can only do once C++ code has instantiated
            // it; sizeof does that without generating any code.
            (void)sizeof(DAT_PencilRenderCore::instance);
            int const startX = this->drawStartX;
            int const startY = this->drawStartY;
            int const endY = this->drawEndY;
            int const color = this->drawColor;
            // Fills column startX from startY to endY with the colour, on the global pencil's surface, not on this
            // one's. Handwritten assembly in the original, transcribed from the binary.
            __asm {
                mov edi, DAT_PencilRenderCore::instance.surfacePtr
                mov eax, startX
                add eax, eax
                add edi, eax
                mov eax, startY
                mov edx, DAT_PencilRenderCore::instance.horizontalByteSize
                mul edx
                add edi, eax
                mov eax, startY
                mov ebx, endY
                mov cx, word ptr color
                mov edx, DAT_PencilRenderCore::instance.horizontalByteSize
            next_pixel:
                cmp eax, ebx
                jg done
                mov word ptr [edi], cx
                add edi, edx
                add eax, 1
                jmp next_pixel
            done:
            }
        }

    }
}
}
