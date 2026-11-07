#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"

#include "OpenSHC/Globals/DAT_BlendFilterArrays.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // The pixel loops are handwritten assembly in the original, transcribed here from the binary.

        // FUNCTION: STRONGHOLDCRUSADER 0x0044F020
        void TextureRenderCore::renderBlendedBlackBox(
            int drawX, int drawY, int drawXEnd, int drawYEnd, int blendStrengthUnk)
        {
            // darkens the box, both ends included, on the pencil surface; black pixels stay black
            // bytes from the end of one row of the box to the start of the next
            int const lineJump = DAT_PencilRenderCore::instance.horizontalByteSize - 2 + (drawX - drawXEnd) * 2;
            // strengths above 32 count down again: 33 is 31, 64 and above are 0
            if (blendStrengthUnk > 64) {
                blendStrengthUnk = 64;
            }
            if (blendStrengthUnk > 32) {
                blendStrengthUnk = 64 - blendStrengthUnk;
            }
            // built on first use: the full-strength table's last entry is 0 until then
            if (DAT_BlendFilterArrays::instance[32][31][0] == 0) {
                MACRO_CALL(OpenSHC::UI::Rendering_Func::InitBlendFilterArraysUnk)();
            }
            // the strength's table row; MSVC gives it the parameter's stack slot, as in the original
            short* const blendTable = DAT_BlendFilterArrays::instance[blendStrengthUnk][0];
            if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_555) {
                // clang-format off
                __asm {
                    mov edi, DAT_PencilRenderCore::instance.surfacePtr
                    mov eax, drawX
                    add eax, eax
                    add edi, eax
                    mov eax, drawY
                    mov edx, DAT_PencilRenderCore::instance.horizontalByteSize
                    mul edx
                    add edi, eax
                row_555:
                    mov ecx, drawX
                    mov esi, blendTable
                pixel_555:
                    cmp ecx, drawXEnd
                    jg row_end_555
                    mov dx, word ptr [edi]
                    cmp dx, 0
                    je next_555
                    movzx ebx, dx
                    and bx, 0x1f
                    mov ax, word ptr [esi + ebx*8]
                    mov bx, dx
                    shr bx, 5
                    and bx, 0x1f
                    or ax, word ptr [esi + ebx*8 + 2]
                    shr dx, 10
                    and edx, 0x1f
                    or ax, word ptr [esi + edx*8 + 4]
                    mov word ptr [edi], ax
                next_555:
                    add edi, 2
                    add ecx, 1
                    jmp pixel_555
                row_end_555:
                    add drawY, 1
                    add edi, lineJump
                    mov eax, drawY
                    cmp eax, drawYEnd
                    jle row_555
                }
                // clang-format on
            } else {
                // clang-format off
                __asm {
                    mov edi, DAT_PencilRenderCore::instance.surfacePtr
                    mov eax, drawX
                    add eax, eax
                    add edi, eax
                    mov eax, drawY
                    mov edx, DAT_PencilRenderCore::instance.horizontalByteSize
                    mul edx
                    add edi, eax
                row_565:
                    mov ecx, drawX
                    mov esi, blendTable
                pixel_565:
                    cmp ecx, drawXEnd
                    jg row_end_565
                    mov dx, word ptr [edi]
                    cmp dx, 0
                    je next_565
                    movzx ebx, dx
                    and bx, 0x1f
                    mov ax, word ptr [esi + ebx*8]
                    mov bx, dx
                    shr bx, 5
                    and bx, 0x3f
                    or ax, word ptr [esi + ebx*8 + 2]
                    shr dx, 11
                    and edx, 0x1f
                    or ax, word ptr [esi + edx*8 + 4]
                    mov word ptr [edi], ax
                next_565:
                    add edi, 2
                    add ecx, 1
                    jmp pixel_565
                row_end_565:
                    add drawY, 1
                    add edi, lineJump
                    mov eax, drawY
                    cmp eax, drawYEnd
                    jle row_565
                }
                // clang-format on
            }
        }

    }
}
}
