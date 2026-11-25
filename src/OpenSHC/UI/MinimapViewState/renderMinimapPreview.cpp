#include "../MinimapViewState.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {

    // The minimap is 200 by 200 pixels.
    enum { MINIMAP_SIZE = 200 };

    // FUNCTION: STRONGHOLDCRUSADER 0x004B5280
    void MinimapViewState::renderMinimapPreview(int screenX, int screenY)
    {
        short* source = this->loadedMiniMap[0];
        MACRO_CALL_MEMBER(
            OpenSHC::UI::Rendering::PencilRenderCore_Func::setupPencilSurface, DAT_PencilRenderCore::ptr)();
        // Copies the 200x200 minimap to the pencil surface at (screenX, screenY), leaving colour 0 transparent.
        // Handwritten assembly in the original, transcribed from the binary.
        __asm {
            mov edi, DAT_PencilRenderCore::instance.surfacePtr
            mov eax, screenX
            add eax, eax
            add edi, eax
            mov eax, screenY
            mov edx, DAT_PencilRenderCore::instance.horizontalByteSize
            mul edx
            add edi, eax
            mov esi, source
            mov edx, MINIMAP_SIZE
        next_row:
            mov ecx, MINIMAP_SIZE
            mov ebx, 0
        next_pixel:
            mov ax, word ptr [esi + ebx]
            cmp ax, 0
            je transparent
            mov word ptr [edi + ebx], ax
        transparent:
            add ebx, 2
            dec ecx
            jne next_pixel
            add esi, MINIMAP_SIZE * 2
            add edi, DAT_PencilRenderCore::instance.horizontalByteSize
            dec edx
            jne next_row
        }
    }

}
}
