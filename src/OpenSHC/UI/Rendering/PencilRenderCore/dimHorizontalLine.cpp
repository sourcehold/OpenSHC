#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/Rendering/ColorMode.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // Every bit but the lowest of each colour channel, so that halving a pixel shifts no bit into the channel
        // below: red starts at bit 11 in RGB565 and at bit 10 in RGB555.
        enum {
            HALVING_MASK_RGB565 = 65535 & ~((1 << 11) | (1 << 5) | 1),
            HALVING_MASK_RGB555 = 32767 & ~((1 << 10) | (1 << 5) | 1)
        };

        // FUNCTION: STRONGHOLDCRUSADER 0x00468EA0
        void PencilRenderCore::dimHorizontalLine()
        {
            // The asm below names DAT_PencilRenderCore, which inline asm can only do once C++ code has instantiated
            // it; sizeof does that without generating any code.
            (void)sizeof(DAT_PencilRenderCore::instance);
            int const startX = this->drawStartX;
            int const startY = this->drawStartY;
            int const endX = this->drawEndX;
            int halvingMask;
            if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_555) {
                halvingMask = HALVING_MASK_RGB555;
            } else {
                halvingMask = HALVING_MASK_RGB565;
            }
            // Halves the brightness of row startY from startX to endX, on the global pencil's surface, not on this
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
                mov eax, startX
                mov ebx, endX
                mov dx, word ptr halvingMask
            next_pixel:
                cmp eax, ebx
                jg done
                mov cx, word ptr [edi]
                and cx, dx
                shr cx, 1
                mov word ptr [edi], cx
                add edi, 2
                add eax, 1
                jmp next_pixel
            done:
            }
        }

    }
}
}
