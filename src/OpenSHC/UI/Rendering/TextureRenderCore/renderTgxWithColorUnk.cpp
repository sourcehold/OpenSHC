#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::Enums::RenderTarget;

        // NOTE: The drawing loop is hand-written assembly in the original: it materialises zero
        //   with mov ecx,0, compares with cmp reg,0 rather than test, loads the same token byte
        //   twice into two registers, and uses mul for the line offset. The surface selection and
        //   the height clamp above it are ordinary C++, which is why the ebx/edi saves appear in
        //   the middle of the function rather than in the prologue.
        //
        //   The loop walks TGX tokens: transparent runs skip pixels, a stream or a repeat run
        //   fills that many pixels with fillColorUnk, and a newline advances to the next row.

        // FUNCTION: STRONGHOLDCRUSADER 0x0044F6F0
        void TextureRenderCore::renderTgxWithColorUnk(
            int xPos, int yPos, int width, int height, ushort* imageSource, ushort fillColorUnk)
        {
            int _lineByteWidth;
            int _heightStart;
            int _heightEnd;
            if (this->drawBufferChoiceValue != OpenSHC::Rendering::Enums::RT_SCREEN_MENU) {
                DAT_TextureRenderCoreObject::instance.currentRenderSurface
                    = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                width = (0xfd8 - width) * 2;
                _heightStart = this->mapGameSurfaceHeightRange.start;
                _lineByteWidth = 0x1fb0;
                _heightEnd = this->mapGameSurfaceHeightRange.end;
            } else {
                DAT_TextureRenderCoreObject::instance.currentRenderSurface
                    = DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu;
                _lineByteWidth = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine;
                width = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine + width * -2;
                _heightStart = this->screenMenuSurfaceHeightRange.start;
                _heightEnd = this->screenMenuSurfaceHeightRange.end;
            }
            if (_heightEnd < height + yPos) {
                height = _heightEnd - yPos;
                if (height <= 0) {
                    return;
                }
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
                add edi, width
                sub edx, 1
                cmp edx, 0
                jg drawTokenLoop
                jmp done
            drawTransparent:
                add ecx, 1
                add ecx, ecx
                add edi, ecx
                jmp drawTokenLoop
            drawStream:
                add esi, 2
                add ecx, 1
            streamLoop:
                mov ax, word ptr fillColorUnk
                mov word ptr [edi], ax
                add edi, 2
                sub ecx, 1
                jne streamLoop
                jmp drawTokenLoop
            drawRepeat:
                add ecx, 1
            repeatLoop:
                mov ax, word ptr fillColorUnk
                mov word ptr [edi], ax
                add esi, 2
                add edi, 2
                sub ecx, 1
                jne repeatLoop
                jmp drawTokenLoop
            done:
            }
        }

    }
}
}
