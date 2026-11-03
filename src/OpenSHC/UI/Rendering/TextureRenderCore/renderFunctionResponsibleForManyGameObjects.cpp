#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // Handlers for TGX runs of 1..32 pixels, filled with label addresses of the function below on first use.
        // The original keeps them in PTR_ARRAY_00c9a510 / PTR_ARRAY_00d7d250; ours point into our own code.
        static void* s_tgxRepeatedPixelHandlers[32];
        static void* s_tgxStreamPixelHandlers[32];

        // Draws a TGX-compressed RGB565 image onto the current render surface (map surface rows are 4056 pixels).
        // The two loops are handwritten assembly in the original, transcribed here from the binary. A TGX token byte
        // holds the run type in its top three bits and the run length minus one in the low five:
        //   0x00 stream    copy the next length pixels from the image,
        //   0x20 skip      leave length pixels transparent,
        //   0x40 repeat    fill length pixels with the one colour that follows,
        //   0x80 new line  advance to the next surface row.
        // Stream and repeat runs dispatch through the two handler tables, one handler per length.
        // The zoomed-out path (isZoom2) draws the image at half size: every other row and every other column.
        // Only the C++ parts are compiled; MSVC does not optimise a function containing __asm, which matches the
        // original's unoptimised-looking prologue.
        //
        // NOTE: the original reads currentRenderSurface through the global instance inside the asm. Inline asm
        // cannot name a resolver global, so it goes through this (one extra instruction; a local cost 2.4 points).

        // FUNCTION: STRONGHOLDCRUSADER 0x0044D3D0
        void TextureRenderCore::renderFunctionResponsibleForManyGameObjects(
            int drawX, int drawY, int imageWidth, int imageHeight, ushort* imageAddress)
        {
            // The asm blocks address these by frame slot. MSVC lays out the locals of this unoptimised function by a
            // hash of their names first and declaration order second, so both the names and the order below are
            // what put every local in the original's slot (measured).
            int oddColumn;
            int lineStride;
            int heightMax;
            int heightStart;
            int lineTail;
            void** streamRunHandlers = s_tgxStreamPixelHandlers;
            void** repeatedPixelHandlers = s_tgxRepeatedPixelHandlers;
            if (imageHeight <= 0)
                return;

            if (DAT_TextureRenderCoreObject::instance.isZoom2 == 0) {
                switch (this->drawBufferChoiceValue) {
                case OpenSHC::Rendering::Enums::RT_MAP_GAME:
                    DAT_TextureRenderCoreObject::instance.currentRenderSurface
                        = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                    lineTail = 4056 * 2 - imageWidth * 2;
                    lineStride = 4056 * 2;
                    heightStart = this->mapGameSurfaceHeightRange.start;
                    heightMax = this->mapGameSurfaceHeightRange.end;
                    break;
                case OpenSHC::Rendering::Enums::RT_BUTTON_AND_ALPHA:
                    DAT_TextureRenderCoreObject::instance.currentRenderSurface
                        = AlphaAndButtonSurfaceObj::instance.surfacePtr;
                    lineTail = AlphaAndButtonSurfaceObj::instance.currentImageWidth * 2 - imageWidth * 2;
                    lineStride = AlphaAndButtonSurfaceObj::instance.currentImageWidth * 2;
                    heightStart = 0;
                    heightMax = imageHeight;
                    break;
                default:
                    DAT_TextureRenderCoreObject::instance.currentRenderSurface
                        = DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu;
                    lineTail = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine - imageWidth * 2;
                    lineStride = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine;
                    heightStart = this->screenMenuSurfaceHeightRange.start;
                    heightMax = this->screenMenuSurfaceHeightRange.end;
                    break;
                }
                if (drawY + imageHeight > heightMax) {
                    imageHeight = imageHeight - (drawY + imageHeight - heightMax);
                    if (imageHeight <= 0)
                        return;
                }
                // clang-format off
                __asm {
                        mov edi, repeatedPixelHandlers
                        mov eax, 0
                        cmp dword ptr [edi], eax
                        je L_44e169
                L_44d4f6:
                        mov esi, imageAddress
                        mov edi, this
                        mov edi, dword ptr [edi]TextureRenderCore.currentRenderSurface
                        mov eax, drawX
                        cmp eax, 0
                        jl L_44e372
                        add eax, eax
                        add edi, eax
                        mov eax, drawY
                        mov ebx, heightStart
                        cmp eax, ebx
                        jge L_44d55e
                        sub ebx, eax
                        mov eax, ebx
                        cmp imageHeight, eax
                        jle L_44e372
                        sub imageHeight, eax
                L_44d529:
                        mov bl, byte ptr [esi]
                        movzx ecx, bl
                        and bl, 0xe0
                        and cl, 0x1f
                        add esi, 1
                        cmp bl, 0x20
                        je L_44d529
                        cmp bl, 0
                        je L_44d548
                        cmp bl, 0x40
                        je L_44d551
                        jmp L_44d556
                L_44d548:
                        add ecx, 1
                        add ecx, ecx
                        add esi, ecx
                        jmp L_44d529
                L_44d551:
                        add esi, 2
                        jmp L_44d529
                L_44d556:
                        sub eax, 1
                        jg L_44d529
                        mov eax, heightStart
                L_44d55e:
                        mov edx, lineStride
                        mul edx
                        add edi, eax
                        mov edx, imageHeight
                L_44d568:
                        mov al, byte ptr [esi]
                        movzx ecx, al
                        and al, 0xe0
                        and cl, 0x1f
                        add esi, 1
                        cmp al, 0x20
                        je L_44d58e
                        cmp al, 0
                        je L_44d5ab
                        cmp al, 0x40
                        je L_44d597
                        add edi, lineTail
                        sub edx, 1
                        jg L_44d568
                        jmp L_44e372
                L_44d58e:
                        add ecx, 1
                        add ecx, ecx
                        add edi, ecx
                        jmp L_44d568
                L_44d597:
                        movzx eax, word ptr [esi]
                        mov ebx, eax
                        shl ebx, 0x10
                        add eax, ebx
                        add esi, 2
                        jmp s_tgxRepeatedPixelHandlers[ecx*4]
                L_44d5ab:
                        jmp s_tgxStreamPixelHandlers[ecx*4]
                L_44d5b2:
                        mov ax, word ptr [esi]
                        mov word ptr [edi], ax
                        add esi, 2
                        add edi, 2
                        jmp L_44d568
                L_44d5c0:
                        mov eax, dword ptr [esi]
                        mov dword ptr [edi], eax
                        add esi, 4
                        add edi, 4
                        jmp L_44d568
                L_44d5cc:
                        mov eax, dword ptr [esi]
                        mov bx, word ptr [esi + 4]
                        mov dword ptr [edi], eax
                        mov word ptr [edi + 4], bx
                        add esi, 6
                        add edi, 6
                        jmp L_44d568
                L_44d5e0:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        add esi, 8
                        add edi, 8
                        jmp L_44d568
                L_44d5f5:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov cx, word ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov word ptr [edi + 8], cx
                        add esi, 0xa
                        add edi, 0xa
                        jmp L_44d568
                L_44d612:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        add esi, 0xc
                        add edi, 0xc
                        jmp L_44d568
                L_44d62d:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov ax, word ptr [esi + 0xc]
                        mov word ptr [edi + 0xc], ax
                        add esi, 0xe
                        add edi, 0xe
                        jmp L_44d568
                L_44d650:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 0xc]
                        mov dword ptr [edi + 0xc], eax
                        add esi, 0x10
                        add edi, 0x10
                        jmp L_44d568
                L_44d671:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 0xc]
                        mov bx, word ptr [esi + 0x10]
                        mov dword ptr [edi + 0xc], eax
                        mov word ptr [edi + 0x10], bx
                        add esi, 0x12
                        add edi, 0x12
                        jmp L_44d568
                L_44d69a:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 0xc]
                        mov ebx, dword ptr [esi + 0x10]
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], ebx
                        add esi, 0x14
                        add edi, 0x14
                        jmp L_44d568
                L_44d6c1:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 0xc]
                        mov ebx, dword ptr [esi + 0x10]
                        mov cx, word ptr [esi + 0x14]
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], ebx
                        mov word ptr [edi + 0x14], cx
                        add esi, 0x16
                        add edi, 0x16
                        jmp L_44d568
                L_44d6f0:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 0xc]
                        mov ebx, dword ptr [esi + 0x10]
                        mov ecx, dword ptr [esi + 0x14]
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], ebx
                        mov dword ptr [edi + 0x14], ecx
                        add esi, 0x18
                        add edi, 0x18
                        jmp L_44d568
                L_44d71d:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 0xc]
                        mov ebx, dword ptr [esi + 0x10]
                        mov ecx, dword ptr [esi + 0x14]
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], ebx
                        mov dword ptr [edi + 0x14], ecx
                        mov ax, word ptr [esi + 0x18]
                        mov word ptr [edi + 0x18], ax
                        add esi, 0x1a
                        add edi, 0x1a
                        jmp L_44d568
                L_44d752:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 0xc]
                        mov ebx, dword ptr [esi + 0x10]
                        mov ecx, dword ptr [esi + 0x14]
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], ebx
                        mov dword ptr [edi + 0x14], ecx
                        mov eax, dword ptr [esi + 0x18]
                        mov dword ptr [edi + 0x18], eax
                        add esi, 0x1c
                        add edi, 0x1c
                        jmp L_44d568
                L_44d785:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 0xc]
                        mov ebx, dword ptr [esi + 0x10]
                        mov ecx, dword ptr [esi + 0x14]
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], ebx
                        mov dword ptr [edi + 0x14], ecx
                        mov eax, dword ptr [esi + 0x18]
                        mov bx, word ptr [esi + 0x1c]
                        mov dword ptr [edi + 0x18], eax
                        mov word ptr [edi + 0x1c], bx
                        add esi, 0x1e
                        add edi, 0x1e
                        jmp L_44d568
                L_44d7c0:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 0xc]
                        mov ebx, dword ptr [esi + 0x10]
                        mov ecx, dword ptr [esi + 0x14]
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], ebx
                        mov dword ptr [edi + 0x14], ecx
                        mov eax, dword ptr [esi + 0x18]
                        mov ebx, dword ptr [esi + 0x1c]
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], ebx
                        add esi, 0x20
                        add edi, 0x20
                        jmp L_44d568
                L_44d7f9:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 0xc]
                        mov ebx, dword ptr [esi + 0x10]
                        mov ecx, dword ptr [esi + 0x14]
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], ebx
                        mov dword ptr [edi + 0x14], ecx
                        mov eax, dword ptr [esi + 0x18]
                        mov ebx, dword ptr [esi + 0x1c]
                        mov cx, word ptr [esi + 0x20]
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], ebx
                        mov word ptr [edi + 0x20], cx
                        add esi, 0x22
                        add edi, 0x22
                        jmp L_44d568
                L_44d83a:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 0xc]
                        mov ebx, dword ptr [esi + 0x10]
                        mov ecx, dword ptr [esi + 0x14]
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], ebx
                        mov dword ptr [edi + 0x14], ecx
                        mov eax, dword ptr [esi + 0x18]
                        mov ebx, dword ptr [esi + 0x1c]
                        mov ecx, dword ptr [esi + 0x20]
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], ebx
                        mov dword ptr [edi + 0x20], ecx
                        add esi, 0x24
                        add edi, 0x24
                        jmp L_44d568
                L_44d879:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 0xc]
                        mov ebx, dword ptr [esi + 0x10]
                        mov ecx, dword ptr [esi + 0x14]
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], ebx
                        mov dword ptr [edi + 0x14], ecx
                        mov eax, dword ptr [esi + 0x18]
                        mov ebx, dword ptr [esi + 0x1c]
                        mov ecx, dword ptr [esi + 0x20]
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], ebx
                        mov dword ptr [edi + 0x20], ecx
                        mov ax, word ptr [esi + 0x24]
                        mov word ptr [edi + 0x24], ax
                        add esi, 0x26
                        add edi, 0x26
                        jmp L_44d568
                L_44d8c0:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 0xc]
                        mov ebx, dword ptr [esi + 0x10]
                        mov ecx, dword ptr [esi + 0x14]
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], ebx
                        mov dword ptr [edi + 0x14], ecx
                        mov eax, dword ptr [esi + 0x18]
                        mov ebx, dword ptr [esi + 0x1c]
                        mov ecx, dword ptr [esi + 0x20]
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], ebx
                        mov dword ptr [edi + 0x20], ecx
                        mov eax, dword ptr [esi + 0x24]
                        mov dword ptr [edi + 0x24], eax
                        add esi, 0x28
                        add edi, 0x28
                        jmp L_44d568
                L_44d905:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 0xc]
                        mov ebx, dword ptr [esi + 0x10]
                        mov ecx, dword ptr [esi + 0x14]
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], ebx
                        mov dword ptr [edi + 0x14], ecx
                        mov eax, dword ptr [esi + 0x18]
                        mov ebx, dword ptr [esi + 0x1c]
                        mov ecx, dword ptr [esi + 0x20]
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], ebx
                        mov dword ptr [edi + 0x20], ecx
                        mov eax, dword ptr [esi + 0x24]
                        mov bx, word ptr [esi + 0x28]
                        mov dword ptr [edi + 0x24], eax
                        mov word ptr [edi + 0x28], bx
                        add esi, 0x2a
                        add edi, 0x2a
                        jmp L_44d568
                L_44d952:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 0xc]
                        mov ebx, dword ptr [esi + 0x10]
                        mov ecx, dword ptr [esi + 0x14]
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], ebx
                        mov dword ptr [edi + 0x14], ecx
                        mov eax, dword ptr [esi + 0x18]
                        mov ebx, dword ptr [esi + 0x1c]
                        mov ecx, dword ptr [esi + 0x20]
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], ebx
                        mov dword ptr [edi + 0x20], ecx
                        mov eax, dword ptr [esi + 0x24]
                        mov ebx, dword ptr [esi + 0x28]
                        mov dword ptr [edi + 0x24], eax
                        mov dword ptr [edi + 0x28], ebx
                        add esi, 0x2c
                        add edi, 0x2c
                        jmp L_44d568
                L_44d99d:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 0xc]
                        mov ebx, dword ptr [esi + 0x10]
                        mov ecx, dword ptr [esi + 0x14]
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], ebx
                        mov dword ptr [edi + 0x14], ecx
                        mov eax, dword ptr [esi + 0x18]
                        mov ebx, dword ptr [esi + 0x1c]
                        mov ecx, dword ptr [esi + 0x20]
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], ebx
                        mov dword ptr [edi + 0x20], ecx
                        mov eax, dword ptr [esi + 0x24]
                        mov ebx, dword ptr [esi + 0x28]
                        mov cx, word ptr [esi + 0x2c]
                        mov dword ptr [edi + 0x24], eax
                        mov dword ptr [edi + 0x28], ebx
                        mov word ptr [edi + 0x2c], cx
                        add esi, 0x2e
                        add edi, 0x2e
                        jmp L_44d568
                L_44d9f0:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 0xc]
                        mov ebx, dword ptr [esi + 0x10]
                        mov ecx, dword ptr [esi + 0x14]
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], ebx
                        mov dword ptr [edi + 0x14], ecx
                        mov eax, dword ptr [esi + 0x18]
                        mov ebx, dword ptr [esi + 0x1c]
                        mov ecx, dword ptr [esi + 0x20]
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], ebx
                        mov dword ptr [edi + 0x20], ecx
                        mov eax, dword ptr [esi + 0x24]
                        mov ebx, dword ptr [esi + 0x28]
                        mov ecx, dword ptr [esi + 0x2c]
                        mov dword ptr [edi + 0x24], eax
                        mov dword ptr [edi + 0x28], ebx
                        mov dword ptr [edi + 0x2c], ecx
                        add esi, 0x30
                        add edi, 0x30
                        jmp L_44d568
                L_44da41:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 0xc]
                        mov ebx, dword ptr [esi + 0x10]
                        mov ecx, dword ptr [esi + 0x14]
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], ebx
                        mov dword ptr [edi + 0x14], ecx
                        mov eax, dword ptr [esi + 0x18]
                        mov ebx, dword ptr [esi + 0x1c]
                        mov ecx, dword ptr [esi + 0x20]
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], ebx
                        mov dword ptr [edi + 0x20], ecx
                        mov eax, dword ptr [esi + 0x24]
                        mov ebx, dword ptr [esi + 0x28]
                        mov ecx, dword ptr [esi + 0x2c]
                        mov dword ptr [edi + 0x24], eax
                        mov dword ptr [edi + 0x28], ebx
                        mov dword ptr [edi + 0x2c], ecx
                        mov ax, word ptr [esi + 0x30]
                        mov word ptr [edi + 0x30], ax
                        add esi, 0x32
                        add edi, 0x32
                        jmp L_44d568
                L_44da9a:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 0xc]
                        mov ebx, dword ptr [esi + 0x10]
                        mov ecx, dword ptr [esi + 0x14]
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], ebx
                        mov dword ptr [edi + 0x14], ecx
                        mov eax, dword ptr [esi + 0x18]
                        mov ebx, dword ptr [esi + 0x1c]
                        mov ecx, dword ptr [esi + 0x20]
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], ebx
                        mov dword ptr [edi + 0x20], ecx
                        mov eax, dword ptr [esi + 0x24]
                        mov ebx, dword ptr [esi + 0x28]
                        mov ecx, dword ptr [esi + 0x2c]
                        mov dword ptr [edi + 0x24], eax
                        mov dword ptr [edi + 0x28], ebx
                        mov dword ptr [edi + 0x2c], ecx
                        mov eax, dword ptr [esi + 0x30]
                        mov dword ptr [edi + 0x30], eax
                        add esi, 0x34
                        add edi, 0x34
                        jmp L_44d568
                L_44daf1:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 0xc]
                        mov ebx, dword ptr [esi + 0x10]
                        mov ecx, dword ptr [esi + 0x14]
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], ebx
                        mov dword ptr [edi + 0x14], ecx
                        mov eax, dword ptr [esi + 0x18]
                        mov ebx, dword ptr [esi + 0x1c]
                        mov ecx, dword ptr [esi + 0x20]
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], ebx
                        mov dword ptr [edi + 0x20], ecx
                        mov eax, dword ptr [esi + 0x24]
                        mov ebx, dword ptr [esi + 0x28]
                        mov ecx, dword ptr [esi + 0x2c]
                        mov dword ptr [edi + 0x24], eax
                        mov dword ptr [edi + 0x28], ebx
                        mov dword ptr [edi + 0x2c], ecx
                        mov eax, dword ptr [esi + 0x30]
                        mov bx, word ptr [esi + 0x34]
                        mov dword ptr [edi + 0x30], eax
                        mov word ptr [edi + 0x34], bx
                        add esi, 0x36
                        add edi, 0x36
                        jmp L_44d568
                L_44db50:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 0xc]
                        mov ebx, dword ptr [esi + 0x10]
                        mov ecx, dword ptr [esi + 0x14]
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], ebx
                        mov dword ptr [edi + 0x14], ecx
                        mov eax, dword ptr [esi + 0x18]
                        mov ebx, dword ptr [esi + 0x1c]
                        mov ecx, dword ptr [esi + 0x20]
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], ebx
                        mov dword ptr [edi + 0x20], ecx
                        mov eax, dword ptr [esi + 0x24]
                        mov ebx, dword ptr [esi + 0x28]
                        mov ecx, dword ptr [esi + 0x2c]
                        mov dword ptr [edi + 0x24], eax
                        mov dword ptr [edi + 0x28], ebx
                        mov dword ptr [edi + 0x2c], ecx
                        mov eax, dword ptr [esi + 0x30]
                        mov ebx, dword ptr [esi + 0x34]
                        mov dword ptr [edi + 0x30], eax
                        mov dword ptr [edi + 0x34], ebx
                        add esi, 0x38
                        add edi, 0x38
                        jmp L_44d568
                L_44dbad:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 0xc]
                        mov ebx, dword ptr [esi + 0x10]
                        mov ecx, dword ptr [esi + 0x14]
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], ebx
                        mov dword ptr [edi + 0x14], ecx
                        mov eax, dword ptr [esi + 0x18]
                        mov ebx, dword ptr [esi + 0x1c]
                        mov ecx, dword ptr [esi + 0x20]
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], ebx
                        mov dword ptr [edi + 0x20], ecx
                        mov eax, dword ptr [esi + 0x24]
                        mov ebx, dword ptr [esi + 0x28]
                        mov ecx, dword ptr [esi + 0x2c]
                        mov dword ptr [edi + 0x24], eax
                        mov dword ptr [edi + 0x28], ebx
                        mov dword ptr [edi + 0x2c], ecx
                        mov eax, dword ptr [esi + 0x30]
                        mov ebx, dword ptr [esi + 0x34]
                        mov cx, word ptr [esi + 0x38]
                        mov dword ptr [edi + 0x30], eax
                        mov dword ptr [edi + 0x34], ebx
                        mov word ptr [edi + 0x38], cx
                        add esi, 0x3a
                        add edi, 0x3a
                        jmp L_44d568
                L_44dc12:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 0xc]
                        mov ebx, dword ptr [esi + 0x10]
                        mov ecx, dword ptr [esi + 0x14]
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], ebx
                        mov dword ptr [edi + 0x14], ecx
                        mov eax, dword ptr [esi + 0x18]
                        mov ebx, dword ptr [esi + 0x1c]
                        mov ecx, dword ptr [esi + 0x20]
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], ebx
                        mov dword ptr [edi + 0x20], ecx
                        mov eax, dword ptr [esi + 0x24]
                        mov ebx, dword ptr [esi + 0x28]
                        mov ecx, dword ptr [esi + 0x2c]
                        mov dword ptr [edi + 0x24], eax
                        mov dword ptr [edi + 0x28], ebx
                        mov dword ptr [edi + 0x2c], ecx
                        mov eax, dword ptr [esi + 0x30]
                        mov ebx, dword ptr [esi + 0x34]
                        mov ecx, dword ptr [esi + 0x38]
                        mov dword ptr [edi + 0x30], eax
                        mov dword ptr [edi + 0x34], ebx
                        mov dword ptr [edi + 0x38], ecx
                        add esi, 0x3c
                        add edi, 0x3c
                        jmp L_44d568
                L_44dc75:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 0xc]
                        mov ebx, dword ptr [esi + 0x10]
                        mov ecx, dword ptr [esi + 0x14]
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], ebx
                        mov dword ptr [edi + 0x14], ecx
                        mov eax, dword ptr [esi + 0x18]
                        mov ebx, dword ptr [esi + 0x1c]
                        mov ecx, dword ptr [esi + 0x20]
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], ebx
                        mov dword ptr [edi + 0x20], ecx
                        mov eax, dword ptr [esi + 0x24]
                        mov ebx, dword ptr [esi + 0x28]
                        mov ecx, dword ptr [esi + 0x2c]
                        mov dword ptr [edi + 0x24], eax
                        mov dword ptr [edi + 0x28], ebx
                        mov dword ptr [edi + 0x2c], ecx
                        mov eax, dword ptr [esi + 0x30]
                        mov ebx, dword ptr [esi + 0x34]
                        mov ecx, dword ptr [esi + 0x38]
                        mov dword ptr [edi + 0x30], eax
                        mov dword ptr [edi + 0x34], ebx
                        mov dword ptr [edi + 0x38], ecx
                        mov ax, word ptr [esi + 0x3c]
                        mov word ptr [edi + 0x3c], ax
                        add esi, 0x3e
                        add edi, 0x3e
                        jmp L_44d568
                L_44dce0:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 0xc]
                        mov ebx, dword ptr [esi + 0x10]
                        mov ecx, dword ptr [esi + 0x14]
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], ebx
                        mov dword ptr [edi + 0x14], ecx
                        mov eax, dword ptr [esi + 0x18]
                        mov ebx, dword ptr [esi + 0x1c]
                        mov ecx, dword ptr [esi + 0x20]
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], ebx
                        mov dword ptr [edi + 0x20], ecx
                        mov eax, dword ptr [esi + 0x24]
                        mov ebx, dword ptr [esi + 0x28]
                        mov ecx, dword ptr [esi + 0x2c]
                        mov dword ptr [edi + 0x24], eax
                        mov dword ptr [edi + 0x28], ebx
                        mov dword ptr [edi + 0x2c], ecx
                        mov eax, dword ptr [esi + 0x30]
                        mov ebx, dword ptr [esi + 0x34]
                        mov ecx, dword ptr [esi + 0x38]
                        mov dword ptr [edi + 0x30], eax
                        mov dword ptr [edi + 0x34], ebx
                        mov dword ptr [edi + 0x38], ecx
                        mov eax, dword ptr [esi + 0x3c]
                        mov dword ptr [edi + 0x3c], eax
                        add esi, 0x40
                        add edi, 0x40
                        jmp L_44d568
                L_44dd49:
                        mov word ptr [edi], ax
                        add edi, 2
                        jmp L_44d568
                L_44dd54:
                        mov dword ptr [edi], eax
                        add edi, 4
                        jmp L_44d568
                L_44dd5e:
                        mov dword ptr [edi], eax
                        mov word ptr [edi + 4], ax
                        add edi, 6
                        jmp L_44d568
                L_44dd6c:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        add edi, 8
                        jmp L_44d568
                L_44dd79:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov word ptr [edi + 8], ax
                        add edi, 0xa
                        jmp L_44d568
                L_44dd8a:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        add edi, 0xc
                        jmp L_44d568
                L_44dd9a:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov word ptr [edi + 0xc], ax
                        add edi, 0xe
                        jmp L_44d568
                L_44ddae:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 0xc], eax
                        add edi, 0x10
                        jmp L_44d568
                L_44ddc1:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 0xc], eax
                        mov word ptr [edi + 0x10], ax
                        add edi, 0x12
                        jmp L_44d568
                L_44ddd8:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], eax
                        add edi, 0x14
                        jmp L_44d568
                L_44ddee:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], eax
                        mov word ptr [edi + 0x14], ax
                        add edi, 0x16
                        jmp L_44d568
                L_44de08:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], eax
                        mov dword ptr [edi + 0x14], eax
                        add edi, 0x18
                        jmp L_44d568
                L_44de21:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], eax
                        mov dword ptr [edi + 0x14], eax
                        mov word ptr [edi + 0x18], ax
                        add edi, 0x1a
                        jmp L_44d568
                L_44de3e:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], eax
                        mov dword ptr [edi + 0x14], eax
                        mov dword ptr [edi + 0x18], eax
                        add edi, 0x1c
                        jmp L_44d568
                L_44de5a:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], eax
                        mov dword ptr [edi + 0x14], eax
                        mov dword ptr [edi + 0x18], eax
                        mov word ptr [edi + 0x1c], ax
                        add edi, 0x1e
                        jmp L_44d568
                L_44de7a:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], eax
                        mov dword ptr [edi + 0x14], eax
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], eax
                        add edi, 0x20
                        jmp L_44d568
                L_44de99:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], eax
                        mov dword ptr [edi + 0x14], eax
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], eax
                        mov word ptr [edi + 0x20], ax
                        add edi, 0x22
                        jmp L_44d568
                L_44debc:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], eax
                        mov dword ptr [edi + 0x14], eax
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], eax
                        mov dword ptr [edi + 0x20], eax
                        add edi, 0x24
                        jmp L_44d568
                L_44dede:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], eax
                        mov dword ptr [edi + 0x14], eax
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], eax
                        mov dword ptr [edi + 0x20], eax
                        mov word ptr [edi + 0x24], ax
                        add edi, 0x26
                        jmp L_44d568
                L_44df04:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], eax
                        mov dword ptr [edi + 0x14], eax
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], eax
                        mov dword ptr [edi + 0x20], eax
                        mov dword ptr [edi + 0x24], eax
                        add edi, 0x28
                        jmp L_44d568
                L_44df29:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], eax
                        mov dword ptr [edi + 0x14], eax
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], eax
                        mov dword ptr [edi + 0x20], eax
                        mov dword ptr [edi + 0x24], eax
                        mov word ptr [edi + 0x28], ax
                        add edi, 0x2a
                        jmp L_44d568
                L_44df52:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], eax
                        mov dword ptr [edi + 0x14], eax
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], eax
                        mov dword ptr [edi + 0x20], eax
                        mov dword ptr [edi + 0x24], eax
                        mov dword ptr [edi + 0x28], eax
                        add edi, 0x2c
                        jmp L_44d568
                L_44df7a:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], eax
                        mov dword ptr [edi + 0x14], eax
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], eax
                        mov dword ptr [edi + 0x20], eax
                        mov dword ptr [edi + 0x24], eax
                        mov dword ptr [edi + 0x28], eax
                        mov word ptr [edi + 0x2c], ax
                        add edi, 0x2e
                        jmp L_44d568
                L_44dfa6:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], eax
                        mov dword ptr [edi + 0x14], eax
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], eax
                        mov dword ptr [edi + 0x20], eax
                        mov dword ptr [edi + 0x24], eax
                        mov dword ptr [edi + 0x28], eax
                        mov dword ptr [edi + 0x2c], eax
                        add edi, 0x30
                        jmp L_44d568
                L_44dfd1:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], eax
                        mov dword ptr [edi + 0x14], eax
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], eax
                        mov dword ptr [edi + 0x20], eax
                        mov dword ptr [edi + 0x24], eax
                        mov dword ptr [edi + 0x28], eax
                        mov dword ptr [edi + 0x2c], eax
                        mov word ptr [edi + 0x30], ax
                        add edi, 0x32
                        jmp L_44d568
                L_44e000:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], eax
                        mov dword ptr [edi + 0x14], eax
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], eax
                        mov dword ptr [edi + 0x20], eax
                        mov dword ptr [edi + 0x24], eax
                        mov dword ptr [edi + 0x28], eax
                        mov dword ptr [edi + 0x2c], eax
                        mov dword ptr [edi + 0x30], eax
                        add edi, 0x34
                        jmp L_44d568
                L_44e02e:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], eax
                        mov dword ptr [edi + 0x14], eax
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], eax
                        mov dword ptr [edi + 0x20], eax
                        mov dword ptr [edi + 0x24], eax
                        mov dword ptr [edi + 0x28], eax
                        mov dword ptr [edi + 0x2c], eax
                        mov dword ptr [edi + 0x30], eax
                        mov word ptr [edi + 0x34], ax
                        add edi, 0x36
                        jmp L_44d568
                L_44e060:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], eax
                        mov dword ptr [edi + 0x14], eax
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], eax
                        mov dword ptr [edi + 0x20], eax
                        mov dword ptr [edi + 0x24], eax
                        mov dword ptr [edi + 0x28], eax
                        mov dword ptr [edi + 0x2c], eax
                        mov dword ptr [edi + 0x30], eax
                        mov dword ptr [edi + 0x34], eax
                        add edi, 0x38
                        jmp L_44d568
                L_44e091:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], eax
                        mov dword ptr [edi + 0x14], eax
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], eax
                        mov dword ptr [edi + 0x20], eax
                        mov dword ptr [edi + 0x24], eax
                        mov dword ptr [edi + 0x28], eax
                        mov dword ptr [edi + 0x2c], eax
                        mov dword ptr [edi + 0x30], eax
                        mov dword ptr [edi + 0x34], eax
                        mov word ptr [edi + 0x38], ax
                        add edi, 0x3a
                        jmp L_44d568
                L_44e0c6:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], eax
                        mov dword ptr [edi + 0x14], eax
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], eax
                        mov dword ptr [edi + 0x20], eax
                        mov dword ptr [edi + 0x24], eax
                        mov dword ptr [edi + 0x28], eax
                        mov dword ptr [edi + 0x2c], eax
                        mov dword ptr [edi + 0x30], eax
                        mov dword ptr [edi + 0x34], eax
                        mov dword ptr [edi + 0x38], eax
                        add edi, 0x3c
                        jmp L_44d568
                L_44e0fa:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], eax
                        mov dword ptr [edi + 0x14], eax
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], eax
                        mov dword ptr [edi + 0x20], eax
                        mov dword ptr [edi + 0x24], eax
                        mov dword ptr [edi + 0x28], eax
                        mov dword ptr [edi + 0x2c], eax
                        mov dword ptr [edi + 0x30], eax
                        mov dword ptr [edi + 0x34], eax
                        mov dword ptr [edi + 0x38], eax
                        mov word ptr [edi + 0x3c], ax
                        add edi, 0x3e
                        jmp L_44d568
                L_44e132:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 0xc], eax
                        mov dword ptr [edi + 0x10], eax
                        mov dword ptr [edi + 0x14], eax
                        mov dword ptr [edi + 0x18], eax
                        mov dword ptr [edi + 0x1c], eax
                        mov dword ptr [edi + 0x20], eax
                        mov dword ptr [edi + 0x24], eax
                        mov dword ptr [edi + 0x28], eax
                        mov dword ptr [edi + 0x2c], eax
                        mov dword ptr [edi + 0x30], eax
                        mov dword ptr [edi + 0x34], eax
                        mov dword ptr [edi + 0x38], eax
                        mov dword ptr [edi + 0x3c], eax
                        add edi, 0x40
                        jmp L_44d568
                L_44e169:
                        mov edi, repeatedPixelHandlers
                        mov eax, offset L_44dd49
                        mov dword ptr [edi], eax
                        mov eax, offset L_44dd54
                        mov dword ptr [edi + 4], eax
                        mov eax, offset L_44dd5e
                        mov dword ptr [edi + 8], eax
                        mov eax, offset L_44dd6c
                        mov dword ptr [edi + 0xc], eax
                        mov eax, offset L_44dd79
                        mov dword ptr [edi + 0x10], eax
                        mov eax, offset L_44dd8a
                        mov dword ptr [edi + 0x14], eax
                        mov eax, offset L_44dd9a
                        mov dword ptr [edi + 0x18], eax
                        mov eax, offset L_44ddae
                        mov dword ptr [edi + 0x1c], eax
                        mov eax, offset L_44ddc1
                        mov dword ptr [edi + 0x20], eax
                        mov eax, offset L_44ddd8
                        mov dword ptr [edi + 0x24], eax
                        mov eax, offset L_44ddee
                        mov dword ptr [edi + 0x28], eax
                        mov eax, offset L_44de08
                        mov dword ptr [edi + 0x2c], eax
                        mov eax, offset L_44de21
                        mov dword ptr [edi + 0x30], eax
                        mov eax, offset L_44de3e
                        mov dword ptr [edi + 0x34], eax
                        mov eax, offset L_44de5a
                        mov dword ptr [edi + 0x38], eax
                        mov eax, offset L_44de7a
                        mov dword ptr [edi + 0x3c], eax
                        mov eax, offset L_44de99
                        mov dword ptr [edi + 0x40], eax
                        mov eax, offset L_44debc
                        mov dword ptr [edi + 0x44], eax
                        mov eax, offset L_44dede
                        mov dword ptr [edi + 0x48], eax
                        mov eax, offset L_44df04
                        mov dword ptr [edi + 0x4c], eax
                        mov eax, offset L_44df29
                        mov dword ptr [edi + 0x50], eax
                        mov eax, offset L_44df52
                        mov dword ptr [edi + 0x54], eax
                        mov eax, offset L_44df7a
                        mov dword ptr [edi + 0x58], eax
                        mov eax, offset L_44dfa6
                        mov dword ptr [edi + 0x5c], eax
                        mov eax, offset L_44dfd1
                        mov dword ptr [edi + 0x60], eax
                        mov eax, offset L_44e000
                        mov dword ptr [edi + 0x64], eax
                        mov eax, offset L_44e02e
                        mov dword ptr [edi + 0x68], eax
                        mov eax, offset L_44e060
                        mov dword ptr [edi + 0x6c], eax
                        mov eax, offset L_44e091
                        mov dword ptr [edi + 0x70], eax
                        mov eax, offset L_44e0c6
                        mov dword ptr [edi + 0x74], eax
                        mov eax, offset L_44e0fa
                        mov dword ptr [edi + 0x78], eax
                        mov eax, offset L_44e132
                        mov dword ptr [edi + 0x7c], eax
                        mov edi, streamRunHandlers
                        mov eax, offset L_44d5b2
                        mov dword ptr [edi], eax
                        mov eax, offset L_44d5c0
                        mov dword ptr [edi + 4], eax
                        mov eax, offset L_44d5cc
                        mov dword ptr [edi + 8], eax
                        mov eax, offset L_44d5e0
                        mov dword ptr [edi + 0xc], eax
                        mov eax, offset L_44d5f5
                        mov dword ptr [edi + 0x10], eax
                        mov eax, offset L_44d612
                        mov dword ptr [edi + 0x14], eax
                        mov eax, offset L_44d62d
                        mov dword ptr [edi + 0x18], eax
                        mov eax, offset L_44d650
                        mov dword ptr [edi + 0x1c], eax
                        mov eax, offset L_44d671
                        mov dword ptr [edi + 0x20], eax
                        mov eax, offset L_44d69a
                        mov dword ptr [edi + 0x24], eax
                        mov eax, offset L_44d6c1
                        mov dword ptr [edi + 0x28], eax
                        mov eax, offset L_44d6f0
                        mov dword ptr [edi + 0x2c], eax
                        mov eax, offset L_44d71d
                        mov dword ptr [edi + 0x30], eax
                        mov eax, offset L_44d752
                        mov dword ptr [edi + 0x34], eax
                        mov eax, offset L_44d785
                        mov dword ptr [edi + 0x38], eax
                        mov eax, offset L_44d7c0
                        mov dword ptr [edi + 0x3c], eax
                        mov eax, offset L_44d7f9
                        mov dword ptr [edi + 0x40], eax
                        mov eax, offset L_44d83a
                        mov dword ptr [edi + 0x44], eax
                        mov eax, offset L_44d879
                        mov dword ptr [edi + 0x48], eax
                        mov eax, offset L_44d8c0
                        mov dword ptr [edi + 0x4c], eax
                        mov eax, offset L_44d905
                        mov dword ptr [edi + 0x50], eax
                        mov eax, offset L_44d952
                        mov dword ptr [edi + 0x54], eax
                        mov eax, offset L_44d99d
                        mov dword ptr [edi + 0x58], eax
                        mov eax, offset L_44d9f0
                        mov dword ptr [edi + 0x5c], eax
                        mov eax, offset L_44da41
                        mov dword ptr [edi + 0x60], eax
                        mov eax, offset L_44da9a
                        mov dword ptr [edi + 0x64], eax
                        mov eax, offset L_44daf1
                        mov dword ptr [edi + 0x68], eax
                        mov eax, offset L_44db50
                        mov dword ptr [edi + 0x6c], eax
                        mov eax, offset L_44dbad
                        mov dword ptr [edi + 0x70], eax
                        mov eax, offset L_44dc12
                        mov dword ptr [edi + 0x74], eax
                        mov eax, offset L_44dc75
                        mov dword ptr [edi + 0x78], eax
                        mov eax, offset L_44dce0
                        mov dword ptr [edi + 0x7c], eax
                        jmp L_44d4f6
                L_44e372:
                }
                // clang-format on
            } else {
                DAT_TextureRenderCoreObject::instance.currentRenderSurface
                    = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                lineTail = 4056 * 2;
                lineStride = 4056 * 2;
                heightStart = this->mapGameSurfaceHeightRange.start;
                if (drawY + imageHeight > this->mapGameSurfaceHeightRange.end) {
                    imageHeight = imageHeight - (drawY + imageHeight - this->mapGameSurfaceHeightRange.end);
                    if (imageHeight <= 0)
                        return;
                }
                // clang-format off
                __asm {
                        mov esi, imageAddress
                        mov edi, this
                        mov edi, dword ptr [edi]TextureRenderCore.currentRenderSurface
                        mov eax, drawX
                        cmp eax, 0
                        jl L_44e4fd
                        and eax, 0xfffffffe
                        add edi, eax
                        mov eax, drawY
                        mov ebx, heightStart
                        cmp eax, ebx
                        jge L_44e430
                        sub ebx, eax
                        mov eax, ebx
                        cmp imageHeight, eax
                        jle L_44e4fd
                        sub imageHeight, eax
                L_44e3fb:
                        mov bl, byte ptr [esi]
                        movzx ecx, bl
                        and bl, 0xe0
                        and cl, 0x1f
                        add esi, 1
                        cmp bl, 0x20
                        je L_44e3fb
                        cmp bl, 0
                        je L_44e41a
                        cmp bl, 0x40
                        je L_44e423
                        jmp L_44e428
                L_44e41a:
                        add ecx, 1
                        add ecx, ecx
                        add esi, ecx
                        jmp L_44e3fb
                L_44e423:
                        add esi, 2
                        jmp L_44e3fb
                L_44e428:
                        sub eax, 1
                        jg L_44e3fb
                        mov eax, heightStart
                L_44e430:
                        mov edx, lineStride
                        mov ecx, eax
                        shr eax, 1
                        mul edx
                        add edi, eax
                        xor eax, eax
                        xor ebx, ebx
                        mov oddColumn, ebx
                        mov edx, imageHeight
                L_44e445:
                        mov al, byte ptr [esi]
                        movzx ecx, al
                        and al, 0xe0
                        and cl, 0x1f
                        add esi, 1
                        cmp al, 0x20
                        je L_44e4a5
                        cmp al, 0
                        je L_44e4d5
                        cmp al, 0x40
                        je L_44e4ad
                        add edi, lineTail
                        sub edx, 1
                        jle L_44e4fd
                L_44e46a:
                        mov bl, byte ptr [esi]
                        movzx ecx, bl
                        and bl, 0xe0
                        and cl, 0x1f
                        add esi, 1
                        cmp bl, 0x20
                        je L_44e46a
                        cmp bl, 0
                        je L_44e489
                        cmp bl, 0x40
                        je L_44e492
                        jmp L_44e497
                L_44e489:
                        add ecx, 1
                        add ecx, ecx
                        add esi, ecx
                        jmp L_44e46a
                L_44e492:
                        add esi, 2
                        jmp L_44e46a
                L_44e497:
                        xor eax, eax
                        xor ebx, ebx
                        mov oddColumn, ebx
                        sub edx, 1
                        jg L_44e445
                        jmp L_44e4fd
                L_44e4a5:
                        add ecx, 1
                        add oddColumn, ecx
                        jmp L_44e445
                L_44e4ad:
                        movzx eax, word ptr [esi]
                        add esi, 2
                        add ecx, 1
                        mov ebx, oddColumn
                        add oddColumn, ecx
                L_44e4bc:
                        test ebx, 1
                        jne L_44e4c8
                        mov word ptr [edi + ebx], ax
                L_44e4c8:
                        add ebx, 1
                        sub ecx, 1
                        jne L_44e4bc
                        jmp L_44e445
                L_44e4d5:
                        add ecx, 1
                        mov ebx, oddColumn
                        add oddColumn, ecx
                L_44e4de:
                        test ebx, 1
                        jne L_44e4ed
                        mov ax, word ptr [esi]
                        mov word ptr [edi + ebx], ax
                L_44e4ed:
                        add ebx, 1
                        add esi, 2
                        sub ecx, 1
                        jne L_44e4de
                        jmp L_44e445
                L_44e4fd:
                }
                // clang-format on
            }
        }

    }
}
}
