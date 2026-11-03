#include "../MinimapViewState.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Rendering::PencilRenderCore;

    // Inline assembly cannot name a resolver global, so the copy loop reaches the pencil through this.
    static PencilRenderCore* const s_pencilRenderCore = &DAT_PencilRenderCore::instance;

    // FUNCTION: STRONGHOLDCRUSADER 0x004B5280
    void MinimapViewState::renderMinimapPreview(int screenX, int screenY)
    {
        short* source = this->loadedMiniMap[0];
        MACRO_CALL_MEMBER(
            OpenSHC::UI::Rendering::PencilRenderCore_Func::setupPencilSurface, DAT_PencilRenderCore::ptr)();
        // Copies the 200x200 minimap to the pencil surface at (screenX, screenY), leaving colour 0 transparent.
        // Handwritten assembly in the original, transcribed from the binary.
        __asm {
            mov ecx, s_pencilRenderCore
            mov edi, dword ptr [ecx]PencilRenderCore.surfacePtr
            mov eax, screenX
            add eax, eax
            add edi, eax
            mov eax, screenY
            mov edx, dword ptr [ecx]PencilRenderCore.horizontalByteSize
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
            mov eax, s_pencilRenderCore
            add edi, dword ptr [eax]PencilRenderCore.horizontalByteSize
            dec edx
            jne nextRow
        }
    }

}
}
