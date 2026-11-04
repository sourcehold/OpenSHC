#include "../MinimapViewState.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {

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
            mov edx, 200
        nextRow:
            mov ecx, 200
            mov ebx, 0
        nextPixel:
            mov ax, word ptr [esi + ebx]
            cmp ax, 0
            je transparent
            mov word ptr [edi + ebx], ax
        transparent:
            add ebx, 2
            dec ecx
            jne nextPixel
            add esi, 400
            add edi, DAT_PencilRenderCore::instance.horizontalByteSize
            dec edx
            jne nextRow
        }
    }

}
}
