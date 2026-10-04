#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"

#include "OpenSHC/Globals/DAT_BlendFilterArrays.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::ColorMode;

        /*
          Used surface perpared through PencilRenderCore. --TheRedDaemon

          The two pixel loops are hand-written assembly in the original: they compare with
          cmp dx,0 rather than test, re-test the column bound at the top of the loop with an
          unconditional jmp back, and mix 16- and 32-bit operands on the same register when
          extracting the red component. The blend strength is folded into a pointer to one
          512-byte filter row of DAT_BlendFilterArrays and kept in the parameter slot.
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0044F020
        void TextureRenderCore::renderBlendedBlackBox(
            int drawX, int drawY, int drawXEnd, int drawYEnd, int blendStrengthUnk)
        {
            int _rowAdvance;
            short* _surfacePtr;
            int _horizontalByteSize;
            _rowAdvance = DAT_PencilRenderCore::instance.horizontalByteSize + (drawX - drawXEnd) * 2 - 2;
            if (0x40 < blendStrengthUnk) {
                blendStrengthUnk = 0x40;
            }
            if (0x20 < blendStrengthUnk) {
                blendStrengthUnk = 0x40 - blendStrengthUnk;
            }
            if (DAT_BlendFilterArrays::instance[0x20][0x1f][0] == 0) {
                MACRO_CALL(OpenSHC::UI::Rendering_Func::InitBlendFilterArraysUnk)();
            }
            blendStrengthUnk = (int)((char*)DAT_BlendFilterArrays::instance + blendStrengthUnk * 0x200);
            _surfacePtr = (short*)DAT_PencilRenderCore::instance.surfacePtr;
            _horizontalByteSize = DAT_PencilRenderCore::instance.horizontalByteSize;
            if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_555) {
                __asm {
                    mov edi, _surfacePtr
                    mov eax, drawX
                    add eax, eax
                    add edi, eax
                    mov eax, drawY
                    mov edx, _horizontalByteSize
                    mul edx
                    add edi, eax
                a5row:
                    mov ecx, drawX
                    mov esi, blendStrengthUnk
                a5column:
                    cmp ecx, drawXEnd
                    jg a5rowEnd
                    mov dx, word ptr [edi]
                    cmp dx, 0
                    je a5next
                    movzx ebx, dx
                    and bx, 1Fh
                    mov ax, word ptr [esi + ebx*8]
                    mov bx, dx
                    shr bx, 5
                    and bx, 1Fh
                    or ax, word ptr [esi + ebx*8 + 2]
                    shr dx, 0Ah
                    and edx, 1Fh
                    or ax, word ptr [esi + edx*8 + 4]
                    mov word ptr [edi], ax
                a5next:
                    add edi, 2
                    add ecx, 1
                    jmp a5column
                a5rowEnd:
                    add drawY, 1
                    add edi, _rowAdvance
                    mov eax, drawY
                    cmp eax, drawYEnd
                    jle a5row
                }
                return;
            }
            __asm {
                mov edi, _surfacePtr
                mov eax, drawX
                add eax, eax
                add edi, eax
                mov eax, drawY
                mov edx, _horizontalByteSize
                mul edx
                add edi, eax
            a6row:
                mov ecx, drawX
                mov esi, blendStrengthUnk
            a6column:
                cmp ecx, drawXEnd
                jg a6rowEnd
                mov dx, word ptr [edi]
                cmp dx, 0
                je a6next
                movzx ebx, dx
                and bx, 1Fh
                mov ax, word ptr [esi + ebx*8]
                mov bx, dx
                shr bx, 5
                and bx, 3Fh
                or ax, word ptr [esi + ebx*8 + 2]
                shr dx, 0Bh
                and edx, 1Fh
                or ax, word ptr [esi + edx*8 + 4]
                mov word ptr [edi], ax
            a6next:
                add edi, 2
                add ecx, 1
                jmp a6column
            a6rowEnd:
                add drawY, 1
                add edi, _rowAdvance
                mov eax, drawY
                cmp eax, drawYEnd
                jle a6row
            }
        }

    }
}
}
