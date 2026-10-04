#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/Rendering/ColorMode.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::ColorMode;
        using OpenSHC::Rendering::Enums::RenderTarget;

        // NOTE: The drawing loop is hand-written assembly in the original: it materialises zero
        //   with mov ecx,0 and mov edx,0, compares with cmp reg,0 rather than test, loads the same
        //   token byte twice into two registers, uses mul for the line offset, and pushes the row
        //   counter on the stack around every token arm. The surface selection, the height clamp
        //   and the colour-mode shift selection above it are ordinary C++, which is why the
        //   ebx/esi/edi saves are interleaved with those loads instead of sitting in the prologue.
        //
        //   The loop walks TGX tokens and blends fillColorUnk over the destination pixel per
        //   channel. The alpha comes from the green channel of the source pixel scaled by
        //   blendStrengthUnk; an alpha of 0x1f means fully opaque and takes a plain store loop.
        //   The red shift lives in the width parameter slot and the green shift in a local,
        //   both selected from colorBitMode (5/0xa for RGB555, 6/0xb for RGB565).

        // FUNCTION: STRONGHOLDCRUSADER 0x0044F850
        void TextureRenderCore::renderTgxWithColorAndBlendingUnk(
            int xPos, int yPos, int width, int height, ushort* imageSource, ushort fillColorUnk, int blendStrengthUnk)
        {
            int _greenShift;
            int _jumpLineByteWidth;
            int _lineByteWidth;
            int _heightStart;
            int _heightEnd;
            blendStrengthUnk = 0x20 - blendStrengthUnk;
            if (this->drawBufferChoiceValue != OpenSHC::Rendering::Enums::RT_SCREEN_MENU) {
                DAT_TextureRenderCoreObject::instance.currentRenderSurface
                    = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                _jumpLineByteWidth = (0xfd8 - width) * 2;
                _lineByteWidth = 0x1fb0;
                _heightStart = this->mapGameSurfaceHeightRange.start;
                _heightEnd = this->mapGameSurfaceHeightRange.end;
            } else {
                DAT_TextureRenderCoreObject::instance.currentRenderSurface
                    = DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu;
                _lineByteWidth = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine;
                _jumpLineByteWidth = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine - width * 2;
                _heightStart = this->screenMenuSurfaceHeightRange.start;
                _heightEnd = this->screenMenuSurfaceHeightRange.end;
            }
            if (height + yPos > _heightEnd) {
                height = _heightEnd - yPos;
                if (height <= 0) {
                    return;
                }
            }
            if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_555) {
                _greenShift = 5;
                width = 0xa;
            } else {
                _greenShift = 6;
                width = 0xb;
            }
            __asm {
                mov esi, imageSource
                mov eax, this
                mov edi, dword ptr [eax]TextureRenderCore.currentRenderSurface
                mov eax, xPos
                cmp eax, 0
                jl done
                add eax, eax
                add edi, eax
                mov eax, yPos
                mov ebx, _heightStart
                cmp eax, ebx
                jge addYOffset
                sub ebx, eax
                mov eax, ebx
                cmp height, eax
                jle done
                sub height, eax
            skipTokenLoop:
                mov ecx, 0
                mov bl, byte ptr [esi]
                mov cl, byte ptr [esi]
                and bl, 0E0h
                and cl, 1Fh
                add esi, 1
                cmp bl, 20h
                je skipTokenLoop
                cmp bl, 0
                je skipStream
                cmp bl, 40h
                je skipRepeat
                jmp skipNextLine
            skipStream:
                add ecx, 1
                add ecx, ecx
                add esi, ecx
                jmp skipTokenLoop
            skipRepeat:
                add esi, 2
                jmp skipTokenLoop
            skipNextLine:
                sub eax, 1
                cmp eax, 0
                jg skipTokenLoop
                mov eax, _heightStart
            addYOffset:
                mov edx, _lineByteWidth
                mul edx
                add edi, eax
                mov edx, height
            drawTokenLoop:
                push edx
                mov ecx, 0
                mov al, byte ptr [esi]
                mov cl, byte ptr [esi]
                and al, 0E0h
                and cl, 1Fh
                add esi, 1
                cmp al, 20h
                je drawTransparent
                cmp al, 0
                je drawRepeat
                cmp al, 40h
                je drawStream
                pop edx
                add edi, _jumpLineByteWidth
                sub edx, 1
                cmp edx, 0
                jg drawTokenLoop
                jmp done
            drawTransparent:
                add ecx, 1
                add ecx, ecx
                add edi, ecx
                pop edx
                jmp drawTokenLoop
            drawStream:
                mov edx, 0
                mov dx, word ptr [esi]
                add esi, 2
                add ecx, 1
                mov bx, word ptr fillColorUnk
                push cx
                mov cx, word ptr _greenShift
                shr dx, cl
                and dx, 1Fh
                pop cx
                mov eax, blendStrengthUnk
                mul dx
                shr ax, 5
                mov dx, ax
                cmp dx, 1Fh
                je streamOpaque
            streamBlend:
                push bx
                push cx
                mov ax, bx
                push bx
                and ax, 1Fh
                mov cx, word ptr [edi]
                and cx, 1Fh
                sub ax, cx
                imul ax, dx
                shr ax, 5
                mov bx, word ptr [edi]
                and bx, 1Fh
                add ax, bx
                and ax, 1Fh
                pop bx
                push ax
                mov ax, bx
                push bx
                mov cx, word ptr _greenShift
                shr ax, cl
                and ax, 1Fh
                mov bx, word ptr [edi]
                shr bx, cl
                and bx, 1Fh
                sub ax, bx
                imul ax, dx
                shr ax, 5
                mov bx, word ptr [edi]
                shr bx, cl
                and bx, 1Fh
                add ax, bx
                and ax, 1Fh
                shl ax, cl
                pop bx
                push ax
                mov ax, bx
                mov cx, word ptr width
                shr ax, cl
                and ax, 1Fh
                mov bx, word ptr [edi]
                shr bx, cl
                and bx, 1Fh
                sub ax, bx
                imul ax, dx
                shr ax, 5
                mov bx, word ptr [edi]
                shr bx, cl
                and bx, 1Fh
                add ax, bx
                and ax, 1Fh
                shl ax, cl
                mov bx, ax
                pop ax
                add bx, ax
                pop ax
                add bx, ax
                pop cx
                mov word ptr [edi], bx
                pop bx
                add edi, 2
                sub ecx, 1
                jne streamBlend
                pop edx
                jmp drawTokenLoop
            streamOpaque:
                mov word ptr [edi], bx
                add edi, 2
                sub ecx, 1
                jne streamOpaque
                pop edx
                jmp drawTokenLoop
            drawRepeat:
                add ecx, 1
            repeatPixel:
                mov dx, word ptr [esi]
                push cx
                mov cx, word ptr _greenShift
                shr dx, cl
                and dx, 1Fh
                pop cx
                mov eax, blendStrengthUnk
                mul dx
                shr ax, 5
                mov dx, ax
                mov ax, word ptr fillColorUnk
                cmp dx, 1Fh
                je repeatOpaque
                mov bx, ax
                push cx
                mov ax, bx
                push bx
                and ax, 1Fh
                mov cx, word ptr [edi]
                and cx, 1Fh
                sub ax, cx
                imul ax, dx
                shr ax, 5
                mov bx, word ptr [edi]
                and bx, 1Fh
                add ax, bx
                and ax, 1Fh
                pop bx
                push ax
                mov ax, bx
                push bx
                mov cx, word ptr _greenShift
                shr ax, cl
                and ax, 1Fh
                mov bx, word ptr [edi]
                shr bx, cl
                and bx, 1Fh
                sub ax, bx
                imul ax, dx
                shr ax, 5
                mov bx, word ptr [edi]
                shr bx, cl
                and bx, 1Fh
                add ax, bx
                and ax, 1Fh
                shl ax, cl
                pop bx
                push ax
                mov ax, bx
                mov cx, word ptr width
                shr ax, cl
                and ax, 1Fh
                mov bx, word ptr [edi]
                shr bx, cl
                and bx, 1Fh
                sub ax, bx
                imul ax, dx
                shr ax, 5
                mov bx, word ptr [edi]
                shr bx, cl
                and bx, 1Fh
                add ax, bx
                and ax, 1Fh
                shl ax, cl
                mov bx, ax
                pop ax
                add bx, ax
                pop ax
                add bx, ax
                pop cx
                mov word ptr [edi], bx
                add esi, 2
                add edi, 2
                sub ecx, 1
                jne repeatPixel
                pop edx
                jmp drawTokenLoop
            repeatOpaque:
                mov word ptr [edi], ax
                add esi, 2
                add edi, 2
                sub ecx, 1
                jne repeatPixel
                pop edx
                jmp drawTokenLoop
            done:
            }
        }

    }
}
}
