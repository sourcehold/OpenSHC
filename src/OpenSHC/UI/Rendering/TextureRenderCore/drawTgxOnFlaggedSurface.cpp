#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::Enums::RenderTarget;

        // NOTE: The drawing loop is hand-written assembly in the original: it materialises zero
        //   with mov ecx,0 and mov eax,0, compares with cmp reg,0 rather than test, loads the same
        //   token byte twice into two registers, and uses mul for the line offset. The surface
        //   selection and the height clamp above it are ordinary C++, which is why the
        //   ebx/esi/edi saves are interleaved with those loads instead of sitting in the prologue.
        //
        //   The loop walks TGX tokens and clips every run against renderingRect_16c854 on both
        //   sides: ebx tracks the current x, and a run crossing left or right is split so that
        //   only the visible part is copied.

        // FUNCTION: STRONGHOLDCRUSADER 0x00454A60
        void TextureRenderCore::drawTgxOnFlaggedSurface(
            int xPos, int yPos, int gfxWidth, int gfxHeight, ushort* tgxSourcePtr)
        {
            int _byteWidth;
            int _left;
            int _right;
            int _top;
            int _bottom;
            _top = this->renderingRect_16c854.top;
            _left = this->renderingRect_16c854.left;
            _bottom = this->renderingRect_16c854.bottom;
            _right = this->renderingRect_16c854.right;
            switch (this->currentRenderSurfaceIdentifierUnk_0x8) {
            case OpenSHC::Rendering::Enums::RT_MAP_GAME:
                DAT_TextureRenderCoreObject::instance.currentRenderSurface
                    = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                gfxWidth = (0xfd8 - gfxWidth) * 2;
                _byteWidth = 0x1fb0;
                break;
            case OpenSHC::Rendering::Enums::RT_SCREEN_MENU:
                DAT_TextureRenderCoreObject::instance.currentRenderSurface
                    = DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu;
                gfxWidth = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine + gfxWidth * -2;
                _byteWidth = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine;
                break;
            }
            if (gfxHeight + yPos > _bottom) {
                gfxHeight = _bottom - yPos;
                if (gfxHeight <= 0) {
                    return;
                }
            }
            __asm {
                mov esi, tgxSourcePtr
                mov eax, this
                mov edi, dword ptr [eax]TextureRenderCore.currentRenderSurface
                mov eax, xPos
                add eax, eax
                add edi, eax
                mov eax, yPos
                mov ebx, _top
                cmp eax, ebx
                jge addYOffset
                sub ebx, eax
                mov eax, ebx
                cmp gfxHeight, eax
                jle done
                sub gfxHeight, eax
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
                mov eax, _top
            addYOffset:
                mov edx, _byteWidth
                mul edx
                add edi, eax
                mov edx, gfxHeight
                mov ebx, xPos
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
                mov ebx, xPos
                add edi, gfxWidth
                sub edx, 1
                cmp edx, 0
                jg drawTokenLoop
                jmp done
            drawTransparent:
                add ecx, 1
                add ebx, ecx
                add ecx, ecx
                add edi, ecx
                jmp drawTokenLoop
            drawStream:
                mov eax, 0
                add ecx, 1
                cmp ebx, _right
                jl streamClip
            streamAdvance:
                add ebx, ecx
                add ecx, ecx
                add edi, ecx
                add esi, 2
                jmp drawTokenLoop
            streamClip:
                cmp ebx, _left
                jge streamRight
                mov eax, ecx
                add eax, ebx
                cmp eax, _left
                jle streamAdvance
                mov eax, _left
                sub eax, ebx
                sub ecx, eax
                add ebx, eax
                add eax, eax
                add edi, eax
            streamRight:
                mov eax, ecx
                add eax, ebx
                cmp eax, _right
                jl streamCopy
                push edx
                mov edx, eax
                sub edx, _right
                sub ecx, edx
                mov ax, word ptr [esi]
            streamClipLoop:
                mov word ptr [edi], ax
                add edi, 2
                add ebx, 1
                sub ecx, 1
                jne streamClipLoop
                add ebx, edx
                add edx, edx
                add edi, edx
                pop edx
                add esi, 2
                jmp drawTokenLoop
            streamCopy:
                mov ax, word ptr [esi]
            streamCopyLoop:
                mov word ptr [edi], ax
                add edi, 2
                add ebx, 1
                sub ecx, 1
                jne streamCopyLoop
                add esi, 2
                jmp drawTokenLoop
            drawRepeat:
                add ecx, 1
                cmp ebx, _right
                jl repeatClip
            repeatAdvance:
                add ebx, ecx
                add ecx, ecx
                add esi, ecx
                add edi, ecx
                jmp drawTokenLoop
            repeatClip:
                cmp ebx, _left
                jge repeatRight
                mov eax, ecx
                add eax, ebx
                cmp eax, _left
                jle repeatAdvance
                mov eax, _left
                sub eax, ebx
                sub ecx, eax
                add ebx, eax
                add eax, eax
                add esi, eax
                add edi, eax
            repeatRight:
                mov eax, ecx
                add eax, ebx
                cmp eax, _right
                jl repeatCopy
                push edx
                mov edx, eax
                sub edx, _right
                sub ecx, edx
            repeatClipLoop:
                mov ax, word ptr [esi]
                mov word ptr [edi], ax
                add esi, 2
                add edi, 2
                add ebx, 1
                sub ecx, 1
                jne repeatClipLoop
                add ebx, edx
                add edx, edx
                add esi, edx
                add edi, edx
                pop edx
                jmp drawTokenLoop
            repeatCopy:
                mov ax, word ptr [esi]
                mov word ptr [edi], ax
                add esi, 2
                add edi, 2
                add ebx, 1
                sub ecx, 1
                jne repeatCopy
                jmp drawTokenLoop
            done:
            }
        }

    }
}
}
