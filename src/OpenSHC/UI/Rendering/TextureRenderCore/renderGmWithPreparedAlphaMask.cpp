#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_BlendFilterArrays.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::ColorMode;
        using OpenSHC::Rendering::Enums::RenderTarget;

        // NOTE: The two drawing loops are hand-written assembly in the original: they materialise
        //   zero with xor/mov reg,0, use mul for the row offset, and mix 16- and 32-bit operands on
        //   the same register when reading the mask. Only the surface selection and the height
        //   clamp are ordinary C++.
        //
        //   The loop walks TGX tokens and takes a per-pixel alpha from the blue channel of the
        //   alpha surface prepared earlier, advancing that pointer in lockstep with the
        //   destination. alphaThresholdUnk is subtracted from it: at or below zero the pixel is
        //   left alone, at the maximum of 0x1f the source is copied verbatim, and in between the
        //   source and destination are blended through rows [alpha] and [0x20 - alpha] of
        //   DAT_BlendFilterArrays. There are two loops because the component masks differ between
        //   RGB555 and RGB565.

        // FUNCTION: STRONGHOLDCRUSADER 0x0044F170
        void TextureRenderCore::renderGmWithPreparedAlphaMask(
            int xPos, int yPos, int width, int height, ushort* imageSource, int alphaThresholdUnk)
        {
            short* _maskPtr;
            int _jumpLineByteWidth;
            int _lineByteWidth;
            int _heightStart;
            short* _dstFilter;
            short* _srcFilter;
            int _heightEnd;
            _maskPtr = (short*)AlphaAndButtonSurfaceObj::instance.surfacePtr;
            if (height <= 0) {
                return;
            }
            if (DAT_BlendFilterArrays::instance[0x20][0x1f][0] == 0) {
                MACRO_CALL(OpenSHC::UI::Rendering_Func::InitBlendFilterArraysUnk)();
            }
            _dstFilter = DAT_BlendFilterArrays::instance[0][0];
            _srcFilter = DAT_BlendFilterArrays::instance[0][0];
            if (this->drawBufferChoiceValue != OpenSHC::Rendering::Enums::RT_SCREEN_MENU) {
                DAT_TextureRenderCoreObject::instance.currentRenderSurface
                    = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                _heightStart = this->mapGameSurfaceHeightRange.start;
                _jumpLineByteWidth = (0xfd8 - width) * 2;
                _heightEnd = this->mapGameSurfaceHeightRange.end;
                _lineByteWidth = 0x1fb0;
            } else {
                DAT_TextureRenderCoreObject::instance.currentRenderSurface
                    = DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu;
                _lineByteWidth = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine;
                _heightStart = this->screenMenuSurfaceHeightRange.start;
                _heightEnd = this->screenMenuSurfaceHeightRange.end;
                _jumpLineByteWidth = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine - width * 2;
            }
            if (height + yPos > _heightEnd) {
                height = _heightEnd - yPos;
                if (height <= 0) {
                    return;
                }
            }
            if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_555) {
                __asm {
                    mov esi, imageSource
                    mov eax, this
                    mov edi, dword ptr [eax]TextureRenderCore.currentRenderSurface
                    mov eax, xPos
                    cmp eax, 0
                    jl a5done
                    add eax, eax
                    add edi, eax
                    mov eax, yPos
                    mov ebx, _heightStart
                    cmp eax, ebx
                    jge a5addRowOffset
                    sub ebx, eax
                    mov eax, ebx
                    cmp height, eax
                    jle a5done
                    sub height, eax
                a5skip:
                    mov bl, byte ptr [esi]
                    movzx ecx, bl
                    and bl, 0E0h
                    and cl, 1Fh
                    add esi, 1
                    cmp bl, 20h
                    je a5skip
                    cmp bl, 0
                    je a5skipStream
                    cmp bl, 40h
                    je a5skipRepeat
                    jmp a5skipNewline
                a5skipStream:
                    add ecx, 1
                    add ecx, ecx
                    add esi, ecx
                    jmp a5skip
                a5skipRepeat:
                    add esi, 2
                    jmp a5skip
                a5skipNewline:
                    mov ebx, width
                    add _maskPtr, ebx
                    add _maskPtr, ebx
                    sub eax, 1
                    jg a5skip
                    mov eax, _heightStart
                a5addRowOffset:
                    mov edx, _lineByteWidth
                    mul edx
                    add edi, eax
                    mov edx, height
                a5token:
                    mov al, byte ptr [esi]
                    movzx ecx, al
                    and al, 0E0h
                    and cl, 1Fh
                    add esi, 1
                    cmp al, 20h
                    je a5transparent
                    cmp al, 0
                    je a5stream
                    cmp al, 40h
                    je a5repeat
                    add edi, _jumpLineByteWidth
                    sub edx, 1
                    jg a5token
                    jmp a5done
                a5transparent:
                    add ecx, 1
                    add ecx, ecx
                    add edi, ecx
                    add _maskPtr, ecx
                    jmp a5token
                a5repeat:
                    xor eax, eax
                    add ecx, 1
                    push edx
                a5repeatLoop:
                    xor edx, edx
                    mov eax, _maskPtr
                    add _maskPtr, 2
                    mov dx, word ptr [eax]
                    and edx, 1Fh
                    sub edx, alphaThresholdUnk
                    jle a5repeatNext
                    cmp edx, 1Fh
                    jne a5repeatBlend
                    mov ax, word ptr [esi]
                    mov word ptr [edi], ax
                    jmp a5repeatNext
                a5repeatBlend:
                    push edx
                    shl edx, 9
                    add edx, _srcFilter
                    mov ax, word ptr [esi]
                    movzx ebx, ax
                    and bx, 1Fh
                    mov bx, word ptr [edx + ebx*8]
                    and ax, 0FFE0h
                    or ax, bx
                    mov bx, ax
                    shr bx, 5
                    and bx, 1Fh
                    mov bx, word ptr [edx + ebx*8 + 2]
                    and ax, 0FC1Fh
                    or ax, bx
                    mov bx, ax
                    shr bx, 0Ah
                    and bx, 1Fh
                    mov bx, word ptr [edx + ebx*8 + 4]
                    and ax, 3FFh
                    or ax, bx
                    pop edx
                    push ax
                    mov eax, 20h
                    sub eax, edx
                    shl eax, 9
                    add eax, _dstFilter
                    mov dx, word ptr [edi]
                    movzx ebx, dx
                    and bx, 1Fh
                    mov bx, word ptr [eax + ebx*8]
                    and dx, 0FFE0h
                    or dx, bx
                    mov bx, dx
                    shr bx, 5
                    and bx, 1Fh
                    mov bx, word ptr [eax + ebx*8 + 2]
                    and dx, 0FC1Fh
                    or dx, bx
                    mov bx, dx
                    shr bx, 0Ah
                    and bx, 1Fh
                    mov bx, word ptr [eax + ebx*8 + 4]
                    and dx, 83FFh
                    or dx, bx
                    pop ax
                    add dx, ax
                    mov word ptr [edi], dx
                a5repeatNext:
                    add edi, 2
                    sub ecx, 1
                    jne a5repeatLoop
                    pop edx
                    add esi, 2
                    jmp a5token
                a5stream:
                    add ecx, 1
                    push edx
                    xor ebx, ebx
                a5streamLoop:
                    xor edx, edx
                    mov eax, _maskPtr
                    add _maskPtr, 2
                    mov dx, word ptr [eax]
                    and edx, 1Fh
                    sub edx, alphaThresholdUnk
                    jle a5streamNext
                    cmp edx, 1Fh
                    jne a5streamBlend
                    mov ax, word ptr [esi]
                    mov word ptr [edi], ax
                    jmp a5streamNext
                a5streamBlend:
                    push edx
                    shl edx, 9
                    add edx, _srcFilter
                    mov ax, word ptr [esi]
                    mov bx, ax
                    and bx, 1Fh
                    mov bx, word ptr [edx + ebx*8]
                    and ax, 0FFE0h
                    or ax, bx
                    mov bx, ax
                    shr bx, 5
                    and bx, 1Fh
                    mov bx, word ptr [edx + ebx*8 + 2]
                    and ax, 0FC1Fh
                    or ax, bx
                    mov bx, ax
                    shr bx, 0Ah
                    and bx, 1Fh
                    mov bx, word ptr [edx + ebx*8 + 4]
                    and ax, 3FFh
                    or ax, bx
                    mov bx, word ptr [edi]
                    mov word ptr [edi], ax
                    pop edx
                    mov eax, 20h
                    sub eax, edx
                    shl eax, 9
                    add eax, _dstFilter
                    mov dx, bx
                    movzx ebx, dx
                    and bx, 1Fh
                    mov bx, word ptr [eax + ebx*8]
                    and dx, 0FFE0h
                    or dx, bx
                    mov bx, dx
                    shr bx, 5
                    and bx, 1Fh
                    mov bx, word ptr [eax + ebx*8 + 2]
                    and dx, 0FC1Fh
                    or dx, bx
                    mov bx, dx
                    shr bx, 0Ah
                    and bx, 1Fh
                    mov bx, word ptr [eax + ebx*8 + 4]
                    and dx, 83FFh
                    or dx, bx
                    add word ptr [edi], dx
                a5streamNext:
                    add esi, 2
                    add edi, 2
                    sub ecx, 1
                    jne a5streamLoop
                    pop edx
                    jmp a5token
                a5done:
                }
                return;
            }
            __asm {
                mov esi, imageSource
                mov eax, this
                mov edi, dword ptr [eax]TextureRenderCore.currentRenderSurface
                mov eax, xPos
                cmp eax, 0
                jl a6done
                add eax, eax
                add edi, eax
                mov eax, yPos
                mov ebx, _heightStart
                cmp eax, ebx
                jge a6addRowOffset
                sub ebx, eax
                mov eax, ebx
                cmp height, eax
                jle a6done
                sub height, eax
            a6skip:
                mov bl, byte ptr [esi]
                movzx ecx, bl
                and bl, 0E0h
                and cl, 1Fh
                add esi, 1
                cmp bl, 20h
                je a6skip
                cmp bl, 0
                je a6skipStream
                cmp bl, 40h
                je a6skipRepeat
                jmp a6skipNewline
            a6skipStream:
                add ecx, 1
                add ecx, ecx
                add esi, ecx
                jmp a6skip
            a6skipRepeat:
                add esi, 2
                jmp a6skip
            a6skipNewline:
                mov ebx, width
                add _maskPtr, ebx
                add _maskPtr, ebx
                sub eax, 1
                jg a6skip
                mov eax, _heightStart
            a6addRowOffset:
                mov edx, _lineByteWidth
                mul edx
                add edi, eax
                mov edx, height
            a6token:
                mov al, byte ptr [esi]
                movzx ecx, al
                and al, 0E0h
                and cl, 1Fh
                add esi, 1
                cmp al, 20h
                je a6transparent
                cmp al, 0
                je a6stream
                cmp al, 40h
                je a6repeat
                add edi, _jumpLineByteWidth
                sub edx, 1
                jg a6token
                jmp a6done
            a6transparent:
                add ecx, 1
                add ecx, ecx
                add edi, ecx
                add _maskPtr, ecx
                jmp a6token
            a6repeat:
                xor eax, eax
                add ecx, 1
                push edx
            a6repeatLoop:
                xor edx, edx
                mov eax, _maskPtr
                add _maskPtr, 2
                mov dx, word ptr [eax]
                and edx, 1Fh
                sub edx, alphaThresholdUnk
                jle a6repeatNext
                cmp edx, 1Fh
                jne a6repeatBlend
                mov ax, word ptr [esi]
                mov word ptr [edi], ax
                jmp a6repeatNext
            a6repeatBlend:
                push cx
                push edx
                shl edx, 9
                add edx, _srcFilter
                mov ax, word ptr [esi]
                movzx ebx, ax
                and bx, 1Fh
                mov cx, word ptr [edx + ebx*8]
                mov bx, ax
                shr bx, 5
                and bx, 3Fh
                or cx, word ptr [edx + ebx*8 + 2]
                mov bx, ax
                shr bx, 0Bh
                and bx, 1Fh
                or cx, word ptr [edx + ebx*8 + 4]
                pop edx
                mov eax, 20h
                sub eax, edx
                shl eax, 9
                add eax, _dstFilter
                mov dx, word ptr [edi]
                movzx ebx, dx
                and bx, 1Fh
                add cx, word ptr [eax + ebx*8]
                mov bx, dx
                shr bx, 5
                and bx, 3Fh
                add cx, word ptr [eax + ebx*8 + 2]
                mov bx, dx
                shr bx, 0Bh
                and bx, 1Fh
                add cx, word ptr [eax + ebx*8 + 4]
                mov word ptr [edi], cx
                pop cx
            a6repeatNext:
                add edi, 2
                sub ecx, 1
                jne a6repeatLoop
                pop edx
                add esi, 2
                jmp a6token
            a6stream:
                add ecx, 1
                push edx
                xor ebx, ebx
            a6streamLoop:
                xor edx, edx
                mov eax, _maskPtr
                add _maskPtr, 2
                mov dx, word ptr [eax]
                and edx, 1Fh
                sub edx, alphaThresholdUnk
                jle a6streamNext
                cmp edx, 1Fh
                jne a6streamBlend
                mov ax, word ptr [esi]
                mov word ptr [edi], ax
                jmp a6streamNext
            a6streamBlend:
                push cx
                push edx
                shl edx, 9
                add edx, _srcFilter
                mov ax, word ptr [esi]
                mov bx, ax
                and bx, 1Fh
                mov cx, word ptr [edx + ebx*8]
                mov bx, ax
                shr bx, 5
                and bx, 3Fh
                or cx, word ptr [edx + ebx*8 + 2]
                mov bx, ax
                shr bx, 0Bh
                and bx, 1Fh
                or cx, word ptr [edx + ebx*8 + 4]
                movzx bx, word ptr [edi]
                pop edx
                mov eax, 20h
                sub eax, edx
                shl eax, 9
                add eax, _dstFilter
                mov dx, bx
                and bx, 1Fh
                add cx, word ptr [eax + ebx*8]
                mov bx, dx
                shr bx, 5
                and bx, 3Fh
                add cx, word ptr [eax + ebx*8 + 2]
                mov bx, dx
                shr bx, 0Bh
                and bx, 1Fh
                add cx, word ptr [eax + ebx*8 + 4]
                mov word ptr [edi], cx
                pop cx
            a6streamNext:
                add esi, 2
                add edi, 2
                sub ecx, 1
                jne a6streamLoop
                pop edx
                jmp a6token
            a6done:
            }
        }

    }
}
}
