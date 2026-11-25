#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00468F20
        void PencilRenderCore::drawCurrentPixel()
        {
            // The asm below names DAT_PencilRenderCore, which inline asm can only do once C++ code has instantiated
            // it; sizeof does that without generating any code.
            (void)sizeof(DAT_PencilRenderCore::instance);
            int const x = this->currentX;
            int const y = this->currentY;
            int const color = this->drawColor;
            // Sets the pixel at (currentX, currentY) to the colour, on the global pencil's surface, not on this one's.
            // Handwritten assembly in the original, transcribed from the binary.
            __asm {
                mov edi, DAT_PencilRenderCore::instance.surfacePtr
                mov eax, x
                add eax, eax
                add edi, eax
                mov eax, y
                mov edx, DAT_PencilRenderCore::instance.horizontalByteSize
                mul edx
                add edi, eax
                mov cx, word ptr color
                mov word ptr [edi], cx
            }
        }

    }
}
}
