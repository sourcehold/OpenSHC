#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/DAT_BlendFilterArrays.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::ColorMode;
        using OpenSHC::Rendering::Enums::RenderTarget;

        // NOTE: The four drawing loops are hand-written assembly in the original: they materialise
        //   zero with mov reg,0, compare with cmp reg,0 rather than test, load the same token byte
        //   twice into two registers, and use mul for the row offset. Only the surface selection,
        //   the blend filter setup and the height clamp are ordinary C++, which is why the
        //   ebx/esi/edi saves sit in the prologue but the this pointer is spilled for the asm.
        //
        //   Each loop walks TGX tokens and blends the source pixel over the destination through a
        //   pair of 512-byte filter rows of DAT_BlendFilterArrays, picked by blendStrengthUnk:
        //   row [blendStrengthUnk] weights the destination and row [0x20 - blendStrengthUnk] the
        //   source, each entry holding the pre-scaled blue, green and red contribution of one
        //   component value. There are four loops because the component masks differ between
        //   RGB555 and RGB565, and because the zoomed-out surface stores only every second column,
        //   so those two loops step the destination by a running column offset and skip odd
        //   columns with test ebx,1.

        // FUNCTION: STRONGHOLDCRUSADER 0x0044E630
        void TextureRenderCore::renderInterfaceOrBuildingOccupationArea(
            int xPos, int yPos, int width, int height, ushort* imageSource, int blendStrengthUnk)
        {
            int _heightStart;
            int _columnOffset;
            short* _dstFilter;
            short* _srcFilter;
            int _heightEnd;
            if (height <= 0) {
                return;
            }
            if (DAT_BlendFilterArrays::instance[0x20][0x1f][0] == 0) {
                MACRO_CALL(OpenSHC::UI::Rendering_Func::InitBlendFilterArraysUnk)();
            }
            _dstFilter = (short*)((char*)DAT_BlendFilterArrays::instance + blendStrengthUnk * 0x200);
            _srcFilter = (short*)((char*)DAT_BlendFilterArrays::instance + (0x4000 - blendStrengthUnk * 0x200));
            if (DAT_TextureRenderCoreObject::instance.isZoom2 == 0) {
                if (this->drawBufferChoiceValue != OpenSHC::Rendering::Enums::RT_SCREEN_MENU) {
                    DAT_TextureRenderCoreObject::instance.currentRenderSurface
                        = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                    width = (0xfd8 - width) * 2;
                    _heightStart = this->mapGameSurfaceHeightRange.start;
                    _heightEnd = this->mapGameSurfaceHeightRange.end;
                    blendStrengthUnk = 0x1fb0;
                } else {
                    DAT_TextureRenderCoreObject::instance.currentRenderSurface
                        = DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu;
                    width = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine - width * 2;
                    _heightStart = this->screenMenuSurfaceHeightRange.start;
                    _heightEnd = this->screenMenuSurfaceHeightRange.end;
                    blendStrengthUnk = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine;
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
                        movzx ecx, byte ptr [esi]
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
                        sub eax, 1
                        cmp eax, 0
                        jg a5skip
                        mov eax, _heightStart
                    a5addRowOffset:
                        mov edx, blendStrengthUnk
                        mul edx
                        add edi, eax
                        mov edx, height
                    a5token:
                        mov ecx, 0
                        mov al, byte ptr [esi]
                        mov cl, byte ptr [esi]
                        and al, 0E0h
                        and cl, 1Fh
                        add esi, 1
                        cmp al, 20h
                        je a5transparent
                        cmp al, 0
                        je a5stream
                        cmp al, 40h
                        je a5repeat
                        add edi, width
                        sub edx, 1
                        cmp edx, 0
                        jg a5token
                        jmp a5done
                    a5transparent:
                        add ecx, 1
                        add ecx, ecx
                        add edi, ecx
                        jmp a5token
                    a5repeat:
                        mov eax, 0
                        mov ax, word ptr [esi]
                        add esi, 2
                        add ecx, 1
                        push edx
                        mov edx, _srcFilter
                        mov ebx, 0
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
                    a5repeatLoop:
                        mov dx, word ptr [edi]
                        push ax
                        mov eax, _dstFilter
                        mov ebx, 0
                        mov bx, dx
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
                        add edi, 2
                        sub ecx, 1
                        jne a5repeatLoop
                        pop edx
                        jmp a5token
                    a5stream:
                        add ecx, 1
                        push edx
                        mov ebx, 0
                    a5streamLoop:
                        mov ax, word ptr [esi]
                        mov edx, _srcFilter
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
                        mov dx, word ptr [edi]
                        mov word ptr [edi], ax
                        mov eax, _dstFilter
                        mov ebx, 0
                        mov bx, dx
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
                    sub eax, 1
                    jg a6skip
                    mov eax, _heightStart
                a6addRowOffset:
                    mov edx, blendStrengthUnk
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
                    add edi, width
                    sub edx, 1
                    jg a6token
                    jmp a6done
                a6transparent:
                    add ecx, 1
                    add ecx, ecx
                    add edi, ecx
                    jmp a6token
                a6repeat:
                    movzx eax, word ptr [esi]
                    add esi, 2
                    push esi
                    add ecx, 1
                    push edx
                    mov esi, _srcFilter
                    movzx ebx, ax
                    and bx, 1Fh
                    mov dx, word ptr [esi + ebx*8]
                    mov bx, ax
                    shr bx, 5
                    and bx, 3Fh
                    or dx, word ptr [esi + ebx*8 + 2]
                    mov bx, ax
                    shr bx, 0Bh
                    and bx, 1Fh
                    or dx, word ptr [esi + ebx*8 + 4]
                    mov ax, dx
                    mov esi, _dstFilter
                a6repeatLoop:
                    mov dx, word ptr [edi]
                    push ax
                    movzx ebx, dx
                    and bx, 1Fh
                    mov ax, word ptr [esi + ebx*8]
                    mov bx, dx
                    shr bx, 5
                    and bx, 3Fh
                    or ax, word ptr [esi + ebx*8 + 2]
                    mov bx, dx
                    shr bx, 0Bh
                    and bx, 1Fh
                    or ax, word ptr [esi + ebx*8 + 4]
                    mov dx, ax
                    pop ax
                    add dx, ax
                    mov word ptr [edi], dx
                    add edi, 2
                    sub ecx, 1
                    jne a6repeatLoop
                    pop edx
                    pop esi
                    jmp a6token
                a6stream:
                    add ecx, 1
                    push edx
                    xor ebx, ebx
                a6streamLoop:
                    mov ax, word ptr [esi]
                    mov edx, _srcFilter
                    push cx
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
                    mov dx, word ptr [edi]
                    mov eax, _dstFilter
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
                    add esi, 2
                    add edi, 2
                    pop cx
                    sub ecx, 1
                    jne a6streamLoop
                    pop edx
                    jmp a6token
                a6done:
                }
                return;
            }
            DAT_TextureRenderCoreObject::instance.currentRenderSurface
                = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
            width = 0x1fb0;
            blendStrengthUnk = 0x1fb0;
            _heightStart = this->mapGameSurfaceHeightRange.start;
            _heightEnd = this->mapGameSurfaceHeightRange.end;
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
                    jl b5done
                    and eax, 0FFFFFFFEh
                    add edi, eax
                    mov eax, yPos
                    mov ebx, _heightStart
                    cmp eax, ebx
                    jge b5addRowOffset
                    sub ebx, eax
                    mov eax, ebx
                    cmp height, eax
                    jle b5done
                    sub height, eax
                b5skip:
                    mov bl, byte ptr [esi]
                    movzx ecx, bl
                    and bl, 0E0h
                    and cl, 1Fh
                    add esi, 1
                    cmp bl, 20h
                    je b5skip
                    cmp bl, 0
                    je b5skipStream
                    cmp bl, 40h
                    je b5skipRepeat
                    jmp b5skipNewline
                b5skipStream:
                    add ecx, 1
                    add ecx, ecx
                    add esi, ecx
                    jmp b5skip
                b5skipRepeat:
                    add esi, 2
                    jmp b5skip
                b5skipNewline:
                    sub eax, 1
                    jg b5skip
                    mov eax, _heightStart
                b5addRowOffset:
                    mov edx, blendStrengthUnk
                    mov ecx, eax
                    shr eax, 1
                    mul edx
                    add edi, eax
                    xor eax, eax
                    xor ebx, ebx
                    mov _columnOffset, ebx
                    mov edx, height
                b5token:
                    mov al, byte ptr [esi]
                    movzx ecx, al
                    and al, 0E0h
                    and cl, 1Fh
                    add esi, 1
                    cmp al, 20h
                    je b5transparent
                    cmp al, 0
                    je b5stream
                    cmp al, 40h
                    je b5repeat
                    add edi, width
                    sub edx, 1
                    jle b5done
                b5rowSkip:
                    mov bl, byte ptr [esi]
                    movzx ecx, bl
                    and bl, 0E0h
                    and cl, 1Fh
                    add esi, 1
                    cmp bl, 20h
                    je b5rowSkip
                    cmp bl, 0
                    je b5rowSkipStream
                    cmp bl, 40h
                    je b5rowSkipRepeat
                    jmp b5rowSkipDone
                b5rowSkipStream:
                    add ecx, 1
                    add ecx, ecx
                    add esi, ecx
                    jmp b5rowSkip
                b5rowSkipRepeat:
                    add esi, 2
                    jmp b5rowSkip
                b5rowSkipDone:
                    xor eax, eax
                    xor ebx, ebx
                    mov _columnOffset, ebx
                    sub edx, 1
                    jg b5token
                    jmp b5done
                b5transparent:
                    add ecx, 1
                    add _columnOffset, ecx
                    jmp b5token
                b5repeat:
                    movzx eax, word ptr [esi]
                    add esi, 2
                    push edx
                    mov edx, _srcFilter
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
                    add ecx, 1
                    mov ebx, _columnOffset
                    add _columnOffset, ecx
                b5repeatLoop:
                    test ebx, 1
                    jne b5repeatNext
                    push edx
                    push ebx
                    mov dx, word ptr [edi + ebx]
                    push ax
                    mov eax, _dstFilter
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
                    pop ebx
                    mov word ptr [edi + ebx], dx
                    pop edx
                b5repeatNext:
                    add ebx, 1
                    sub ecx, 1
                    jne b5repeatLoop
                    jmp b5token
                b5stream:
                    add ecx, 1
                    mov ebx, _columnOffset
                    add _columnOffset, ecx
                b5streamLoop:
                    test ebx, 1
                    jne b5streamNext
                    push edx
                    push ebx
                    mov ax, word ptr [esi]
                    mov edx, _srcFilter
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
                    pop ebx
                    mov dx, word ptr [edi + ebx]
                    mov word ptr [edi + ebx], ax
                    push ebx
                    mov eax, _dstFilter
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
                    pop ebx
                    add word ptr [edi + ebx], dx
                    pop edx
                b5streamNext:
                    add ebx, 1
                    add esi, 2
                    sub ecx, 1
                    jne b5streamLoop
                    jmp b5token
                b5done:
                }
                return;
            }
            __asm {
                mov esi, imageSource
                mov eax, this
                mov edi, dword ptr [eax]TextureRenderCore.currentRenderSurface
                mov eax, xPos
                cmp eax, 0
                jl b6done
                and eax, 0FFFFFFFEh
                add edi, eax
                mov eax, yPos
                mov ebx, _heightStart
                cmp eax, ebx
                jge b6addRowOffset
                sub ebx, eax
                mov eax, ebx
                cmp height, eax
                jle b6done
                sub height, eax
            b6skip:
                mov bl, byte ptr [esi]
                movzx ecx, bl
                and bl, 0E0h
                and cl, 1Fh
                add esi, 1
                cmp bl, 20h
                je b6skip
                cmp bl, 0
                je b6skipStream
                cmp bl, 40h
                je b6skipRepeat
                jmp b6skipNewline
            b6skipStream:
                add ecx, 1
                add ecx, ecx
                add esi, ecx
                jmp b6skip
            b6skipRepeat:
                add esi, 2
                jmp b6skip
            b6skipNewline:
                sub eax, 1
                jg b6skip
                mov eax, _heightStart
            b6addRowOffset:
                mov edx, blendStrengthUnk
                mov ecx, eax
                shr eax, 1
                mul edx
                add edi, eax
                xor eax, eax
                xor ebx, ebx
                mov _columnOffset, ebx
                mov edx, height
            b6token:
                mov al, byte ptr [esi]
                movzx ecx, al
                and al, 0E0h
                and cl, 1Fh
                add esi, 1
                cmp al, 20h
                je b6transparent
                cmp al, 0
                je b6stream
                cmp al, 40h
                je b6repeat
                add edi, width
                sub edx, 1
                jle b6done
            b6rowSkip:
                mov bl, byte ptr [esi]
                movzx ecx, bl
                and bl, 0E0h
                and cl, 1Fh
                add esi, 1
                cmp bl, 20h
                je b6rowSkip
                cmp bl, 0
                je b6rowSkipStream
                cmp bl, 40h
                je b6rowSkipRepeat
                jmp b6rowSkipDone
            b6rowSkipStream:
                add ecx, 1
                add ecx, ecx
                add esi, ecx
                jmp b6rowSkip
            b6rowSkipRepeat:
                add esi, 2
                jmp b6rowSkip
            b6rowSkipDone:
                xor eax, eax
                xor ebx, ebx
                mov _columnOffset, ebx
                sub edx, 1
                jg b6token
                jmp b6done
            b6transparent:
                add ecx, 1
                add _columnOffset, ecx
                jmp b6token
            b6repeat:
                movzx eax, word ptr [esi]
                add esi, 2
                push edx
                mov edx, _srcFilter
                movzx ebx, ax
                and bx, 1Fh
                mov bx, word ptr [edx + ebx*8]
                and ax, 0FFE0h
                or ax, bx
                mov bx, ax
                shr bx, 5
                and bx, 3Fh
                mov bx, word ptr [edx + ebx*8 + 2]
                and ax, 0F81Fh
                or ax, bx
                mov bx, ax
                shr bx, 0Bh
                and bx, 1Fh
                mov bx, word ptr [edx + ebx*8 + 4]
                and ax, 7FFh
                or ax, bx
                pop edx
                add ecx, 1
                mov ebx, _columnOffset
                add _columnOffset, ecx
            b6repeatLoop:
                test ebx, 1
                jne b6repeatNext
                push edx
                push ebx
                mov dx, word ptr [edi + ebx]
                push ax
                mov eax, _dstFilter
                movzx ebx, dx
                and bx, 1Fh
                mov bx, word ptr [eax + ebx*8]
                and dx, 0FFE0h
                or dx, bx
                mov bx, dx
                shr bx, 5
                and bx, 3Fh
                mov bx, word ptr [eax + ebx*8 + 2]
                and dx, 0F81Fh
                or dx, bx
                mov bx, dx
                shr bx, 0Bh
                and bx, 1Fh
                mov bx, word ptr [eax + ebx*8 + 4]
                and dx, 7FFh
                or dx, bx
                pop ax
                add dx, ax
                pop ebx
                mov word ptr [edi + ebx], dx
                pop edx
            b6repeatNext:
                add ebx, 1
                sub ecx, 1
                jne b6repeatLoop
                jmp b6token
            b6stream:
                add ecx, 1
                mov ebx, _columnOffset
                add _columnOffset, ecx
            b6streamLoop:
                test ebx, 1
                jne b6streamNext
                push edx
                push ebx
                mov ax, word ptr [esi]
                mov edx, _srcFilter
                mov bx, ax
                and bx, 1Fh
                mov bx, word ptr [edx + ebx*8]
                and ax, 0FFE0h
                or ax, bx
                mov bx, ax
                shr bx, 5
                and bx, 3Fh
                mov bx, word ptr [edx + ebx*8 + 2]
                and ax, 0F81Fh
                or ax, bx
                mov bx, ax
                shr bx, 0Bh
                and bx, 1Fh
                mov bx, word ptr [edx + ebx*8 + 4]
                and ax, 7FFh
                or ax, bx
                pop ebx
                mov dx, word ptr [edi + ebx]
                mov word ptr [edi + ebx], ax
                push ebx
                mov eax, _dstFilter
                movzx ebx, dx
                and bx, 1Fh
                mov bx, word ptr [eax + ebx*8]
                and dx, 0FFE0h
                or dx, bx
                mov bx, dx
                shr bx, 5
                and bx, 3Fh
                mov bx, word ptr [eax + ebx*8 + 2]
                and dx, 0F81Fh
                or dx, bx
                mov bx, dx
                shr bx, 0Bh
                and bx, 1Fh
                mov bx, word ptr [eax + ebx*8 + 4]
                and dx, 7FFh
                or dx, bx
                pop ebx
                add word ptr [edi + ebx], dx
                pop edx
            b6streamNext:
                add ebx, 1
                add esi, 2
                sub ecx, 1
                jne b6streamLoop
                jmp b6token
            b6done:
            }
        }

    }
}
}
