#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/TGX_RepeatRunHandlers.hpp"
#include "OpenSHC/Globals/TGX_StreamRunHandlers.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // Draws a TGX-compressed RGB565 image onto the current render surface (map surface rows are 4056 pixels).
        // The two loops are handwritten assembly in the original, transcribed here from the binary. A TGX token byte
        // holds the run type in its top three bits and the run length minus one in the low five:
        //   0x00 stream    copy the next length pixels from the image,
        //   0x20 skip      leave length pixels transparent,
        //   0x40 repeat    fill length pixels with the one color that follows,
        //   0x80 new line  advance to the next surface row.
        // Stream and repeat runs dispatch through the two handler tables, one handler per length; the function fills
        // them with its own label addresses on first use. The zoomed-out path (isZoom2) draws the image at half size:
        // every other row and every other column.

        // A TGX token byte's run type (top three bits) and run length minus one (low five bits).
        enum { TGX_STREAM = 0, TGX_SKIP = 32, TGX_REPEAT = 64, TGX_TYPE_MASK = 224, TGX_LENGTH_MASK = 31 };

        // FUNCTION: STRONGHOLDCRUSADER 0x0044D3D0
        void TextureRenderCore::renderFunctionResponsibleForManyGameObjects(
            int drawX, int drawY, int imageWidth, int imageHeight, ushort* imageAddress)
        {
            // Declared up front because the switch assigns them; declaration order (and names) decide the frame slots.
            int oddColumn;
            int lineStride;
            int heightMax;
            int heightStart;
            int lineTail;
            void** repeatedPixelHandlers = TGX_RepeatRunHandlers::instance;
            void** streamRunHandlers = TGX_StreamRunHandlers::instance;
            if (imageHeight <= 0) {
                return;
            }

            if (!DAT_TextureRenderCoreObject::instance.isZoom2) {
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
                    imageHeight -= drawY + imageHeight - heightMax;
                    if (imageHeight <= 0) {
                        return;
                    }
                }
                // clang-format off
                __asm {
                        mov edi, repeatedPixelHandlers
                        mov eax, 0
                        cmp dword ptr [edi], eax
                        je fill_tables
                draw_start:
                        mov esi, imageAddress
                        mov edi, DAT_TextureRenderCoreObject::instance.currentRenderSurface
                        mov eax, drawX
                        cmp eax, 0
                        jl done
                        add eax, eax
                        add edi, eax
                        mov eax, drawY
                        mov ebx, heightStart
                        cmp eax, ebx
                        jge row_start
                        sub ebx, eax
                        mov eax, ebx
                        cmp imageHeight, eax
                        jle done
                        sub imageHeight, eax
                skip_rows_above_top:
                        mov bl, byte ptr [esi]
                        movzx ecx, bl
                        and bl, TGX_TYPE_MASK
                        and cl, TGX_LENGTH_MASK
                        add esi, 1
                        cmp bl, TGX_SKIP
                        je skip_rows_above_top
                        cmp bl, TGX_STREAM
                        je skip_rows_stream
                        cmp bl, TGX_REPEAT
                        je skip_rows_repeat
                        jmp skip_rows_new_line
                skip_rows_stream:
                        add ecx, 1
                        add ecx, ecx
                        add esi, ecx
                        jmp skip_rows_above_top
                skip_rows_repeat:
                        add esi, 2
                        jmp skip_rows_above_top
                skip_rows_new_line:
                        sub eax, 1
                        jg skip_rows_above_top
                        mov eax, heightStart
                row_start:
                        mov edx, lineStride
                        mul edx
                        add edi, eax
                        mov edx, imageHeight
                token_loop:
                        mov al, byte ptr [esi]
                        movzx ecx, al
                        and al, TGX_TYPE_MASK
                        and cl, TGX_LENGTH_MASK
                        add esi, 1
                        cmp al, TGX_SKIP
                        je token_skip
                        cmp al, TGX_STREAM
                        je token_stream
                        cmp al, TGX_REPEAT
                        je token_repeat
                        add edi, lineTail
                        sub edx, 1
                        jg token_loop
                        jmp done
                token_skip:
                        add ecx, 1
                        add ecx, ecx
                        add edi, ecx
                        jmp token_loop
                token_repeat:
                        movzx eax, word ptr [esi]
                        mov ebx, eax
                        shl ebx, 16
                        add eax, ebx
                        add esi, 2
                        jmp TGX_RepeatRunHandlers::instance[ecx*4]
                token_stream:
                        jmp TGX_StreamRunHandlers::instance[ecx*4]
                stream_run_1:
                        mov ax, word ptr [esi]
                        mov word ptr [edi], ax
                        add esi, 2
                        add edi, 2
                        jmp token_loop
                stream_run_2:
                        mov eax, dword ptr [esi]
                        mov dword ptr [edi], eax
                        add esi, 4
                        add edi, 4
                        jmp token_loop
                stream_run_3:
                        mov eax, dword ptr [esi]
                        mov bx, word ptr [esi + 4]
                        mov dword ptr [edi], eax
                        mov word ptr [edi + 4], bx
                        add esi, 6
                        add edi, 6
                        jmp token_loop
                stream_run_4:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        add esi, 8
                        add edi, 8
                        jmp token_loop
                stream_run_5:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov cx, word ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov word ptr [edi + 8], cx
                        add esi, 10
                        add edi, 10
                        jmp token_loop
                stream_run_6:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        add esi, 12
                        add edi, 12
                        jmp token_loop
                stream_run_7:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov ax, word ptr [esi + 12]
                        mov word ptr [edi + 12], ax
                        add esi, 14
                        add edi, 14
                        jmp token_loop
                stream_run_8:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 12]
                        mov dword ptr [edi + 12], eax
                        add esi, 16
                        add edi, 16
                        jmp token_loop
                stream_run_9:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 12]
                        mov bx, word ptr [esi + 16]
                        mov dword ptr [edi + 12], eax
                        mov word ptr [edi + 16], bx
                        add esi, 18
                        add edi, 18
                        jmp token_loop
                stream_run_10:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 12]
                        mov ebx, dword ptr [esi + 16]
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], ebx
                        add esi, 20
                        add edi, 20
                        jmp token_loop
                stream_run_11:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 12]
                        mov ebx, dword ptr [esi + 16]
                        mov cx, word ptr [esi + 20]
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], ebx
                        mov word ptr [edi + 20], cx
                        add esi, 22
                        add edi, 22
                        jmp token_loop
                stream_run_12:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 12]
                        mov ebx, dword ptr [esi + 16]
                        mov ecx, dword ptr [esi + 20]
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], ebx
                        mov dword ptr [edi + 20], ecx
                        add esi, 24
                        add edi, 24
                        jmp token_loop
                stream_run_13:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 12]
                        mov ebx, dword ptr [esi + 16]
                        mov ecx, dword ptr [esi + 20]
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], ebx
                        mov dword ptr [edi + 20], ecx
                        mov ax, word ptr [esi + 24]
                        mov word ptr [edi + 24], ax
                        add esi, 26
                        add edi, 26
                        jmp token_loop
                stream_run_14:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 12]
                        mov ebx, dword ptr [esi + 16]
                        mov ecx, dword ptr [esi + 20]
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], ebx
                        mov dword ptr [edi + 20], ecx
                        mov eax, dword ptr [esi + 24]
                        mov dword ptr [edi + 24], eax
                        add esi, 28
                        add edi, 28
                        jmp token_loop
                stream_run_15:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 12]
                        mov ebx, dword ptr [esi + 16]
                        mov ecx, dword ptr [esi + 20]
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], ebx
                        mov dword ptr [edi + 20], ecx
                        mov eax, dword ptr [esi + 24]
                        mov bx, word ptr [esi + 28]
                        mov dword ptr [edi + 24], eax
                        mov word ptr [edi + 28], bx
                        add esi, 30
                        add edi, 30
                        jmp token_loop
                stream_run_16:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 12]
                        mov ebx, dword ptr [esi + 16]
                        mov ecx, dword ptr [esi + 20]
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], ebx
                        mov dword ptr [edi + 20], ecx
                        mov eax, dword ptr [esi + 24]
                        mov ebx, dword ptr [esi + 28]
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], ebx
                        add esi, 32
                        add edi, 32
                        jmp token_loop
                stream_run_17:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 12]
                        mov ebx, dword ptr [esi + 16]
                        mov ecx, dword ptr [esi + 20]
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], ebx
                        mov dword ptr [edi + 20], ecx
                        mov eax, dword ptr [esi + 24]
                        mov ebx, dword ptr [esi + 28]
                        mov cx, word ptr [esi + 32]
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], ebx
                        mov word ptr [edi + 32], cx
                        add esi, 34
                        add edi, 34
                        jmp token_loop
                stream_run_18:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 12]
                        mov ebx, dword ptr [esi + 16]
                        mov ecx, dword ptr [esi + 20]
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], ebx
                        mov dword ptr [edi + 20], ecx
                        mov eax, dword ptr [esi + 24]
                        mov ebx, dword ptr [esi + 28]
                        mov ecx, dword ptr [esi + 32]
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], ebx
                        mov dword ptr [edi + 32], ecx
                        add esi, 36
                        add edi, 36
                        jmp token_loop
                stream_run_19:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 12]
                        mov ebx, dword ptr [esi + 16]
                        mov ecx, dword ptr [esi + 20]
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], ebx
                        mov dword ptr [edi + 20], ecx
                        mov eax, dword ptr [esi + 24]
                        mov ebx, dword ptr [esi + 28]
                        mov ecx, dword ptr [esi + 32]
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], ebx
                        mov dword ptr [edi + 32], ecx
                        mov ax, word ptr [esi + 36]
                        mov word ptr [edi + 36], ax
                        add esi, 38
                        add edi, 38
                        jmp token_loop
                stream_run_20:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 12]
                        mov ebx, dword ptr [esi + 16]
                        mov ecx, dword ptr [esi + 20]
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], ebx
                        mov dword ptr [edi + 20], ecx
                        mov eax, dword ptr [esi + 24]
                        mov ebx, dword ptr [esi + 28]
                        mov ecx, dword ptr [esi + 32]
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], ebx
                        mov dword ptr [edi + 32], ecx
                        mov eax, dword ptr [esi + 36]
                        mov dword ptr [edi + 36], eax
                        add esi, 40
                        add edi, 40
                        jmp token_loop
                stream_run_21:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 12]
                        mov ebx, dword ptr [esi + 16]
                        mov ecx, dword ptr [esi + 20]
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], ebx
                        mov dword ptr [edi + 20], ecx
                        mov eax, dword ptr [esi + 24]
                        mov ebx, dword ptr [esi + 28]
                        mov ecx, dword ptr [esi + 32]
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], ebx
                        mov dword ptr [edi + 32], ecx
                        mov eax, dword ptr [esi + 36]
                        mov bx, word ptr [esi + 40]
                        mov dword ptr [edi + 36], eax
                        mov word ptr [edi + 40], bx
                        add esi, 42
                        add edi, 42
                        jmp token_loop
                stream_run_22:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 12]
                        mov ebx, dword ptr [esi + 16]
                        mov ecx, dword ptr [esi + 20]
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], ebx
                        mov dword ptr [edi + 20], ecx
                        mov eax, dword ptr [esi + 24]
                        mov ebx, dword ptr [esi + 28]
                        mov ecx, dword ptr [esi + 32]
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], ebx
                        mov dword ptr [edi + 32], ecx
                        mov eax, dword ptr [esi + 36]
                        mov ebx, dword ptr [esi + 40]
                        mov dword ptr [edi + 36], eax
                        mov dword ptr [edi + 40], ebx
                        add esi, 44
                        add edi, 44
                        jmp token_loop
                stream_run_23:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 12]
                        mov ebx, dword ptr [esi + 16]
                        mov ecx, dword ptr [esi + 20]
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], ebx
                        mov dword ptr [edi + 20], ecx
                        mov eax, dword ptr [esi + 24]
                        mov ebx, dword ptr [esi + 28]
                        mov ecx, dword ptr [esi + 32]
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], ebx
                        mov dword ptr [edi + 32], ecx
                        mov eax, dword ptr [esi + 36]
                        mov ebx, dword ptr [esi + 40]
                        mov cx, word ptr [esi + 44]
                        mov dword ptr [edi + 36], eax
                        mov dword ptr [edi + 40], ebx
                        mov word ptr [edi + 44], cx
                        add esi, 46
                        add edi, 46
                        jmp token_loop
                stream_run_24:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 12]
                        mov ebx, dword ptr [esi + 16]
                        mov ecx, dword ptr [esi + 20]
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], ebx
                        mov dword ptr [edi + 20], ecx
                        mov eax, dword ptr [esi + 24]
                        mov ebx, dword ptr [esi + 28]
                        mov ecx, dword ptr [esi + 32]
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], ebx
                        mov dword ptr [edi + 32], ecx
                        mov eax, dword ptr [esi + 36]
                        mov ebx, dword ptr [esi + 40]
                        mov ecx, dword ptr [esi + 44]
                        mov dword ptr [edi + 36], eax
                        mov dword ptr [edi + 40], ebx
                        mov dword ptr [edi + 44], ecx
                        add esi, 48
                        add edi, 48
                        jmp token_loop
                stream_run_25:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 12]
                        mov ebx, dword ptr [esi + 16]
                        mov ecx, dword ptr [esi + 20]
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], ebx
                        mov dword ptr [edi + 20], ecx
                        mov eax, dword ptr [esi + 24]
                        mov ebx, dword ptr [esi + 28]
                        mov ecx, dword ptr [esi + 32]
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], ebx
                        mov dword ptr [edi + 32], ecx
                        mov eax, dword ptr [esi + 36]
                        mov ebx, dword ptr [esi + 40]
                        mov ecx, dword ptr [esi + 44]
                        mov dword ptr [edi + 36], eax
                        mov dword ptr [edi + 40], ebx
                        mov dword ptr [edi + 44], ecx
                        mov ax, word ptr [esi + 48]
                        mov word ptr [edi + 48], ax
                        add esi, 50
                        add edi, 50
                        jmp token_loop
                stream_run_26:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 12]
                        mov ebx, dword ptr [esi + 16]
                        mov ecx, dword ptr [esi + 20]
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], ebx
                        mov dword ptr [edi + 20], ecx
                        mov eax, dword ptr [esi + 24]
                        mov ebx, dword ptr [esi + 28]
                        mov ecx, dword ptr [esi + 32]
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], ebx
                        mov dword ptr [edi + 32], ecx
                        mov eax, dword ptr [esi + 36]
                        mov ebx, dword ptr [esi + 40]
                        mov ecx, dword ptr [esi + 44]
                        mov dword ptr [edi + 36], eax
                        mov dword ptr [edi + 40], ebx
                        mov dword ptr [edi + 44], ecx
                        mov eax, dword ptr [esi + 48]
                        mov dword ptr [edi + 48], eax
                        add esi, 52
                        add edi, 52
                        jmp token_loop
                stream_run_27:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 12]
                        mov ebx, dword ptr [esi + 16]
                        mov ecx, dword ptr [esi + 20]
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], ebx
                        mov dword ptr [edi + 20], ecx
                        mov eax, dword ptr [esi + 24]
                        mov ebx, dword ptr [esi + 28]
                        mov ecx, dword ptr [esi + 32]
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], ebx
                        mov dword ptr [edi + 32], ecx
                        mov eax, dword ptr [esi + 36]
                        mov ebx, dword ptr [esi + 40]
                        mov ecx, dword ptr [esi + 44]
                        mov dword ptr [edi + 36], eax
                        mov dword ptr [edi + 40], ebx
                        mov dword ptr [edi + 44], ecx
                        mov eax, dword ptr [esi + 48]
                        mov bx, word ptr [esi + 52]
                        mov dword ptr [edi + 48], eax
                        mov word ptr [edi + 52], bx
                        add esi, 54
                        add edi, 54
                        jmp token_loop
                stream_run_28:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 12]
                        mov ebx, dword ptr [esi + 16]
                        mov ecx, dword ptr [esi + 20]
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], ebx
                        mov dword ptr [edi + 20], ecx
                        mov eax, dword ptr [esi + 24]
                        mov ebx, dword ptr [esi + 28]
                        mov ecx, dword ptr [esi + 32]
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], ebx
                        mov dword ptr [edi + 32], ecx
                        mov eax, dword ptr [esi + 36]
                        mov ebx, dword ptr [esi + 40]
                        mov ecx, dword ptr [esi + 44]
                        mov dword ptr [edi + 36], eax
                        mov dword ptr [edi + 40], ebx
                        mov dword ptr [edi + 44], ecx
                        mov eax, dword ptr [esi + 48]
                        mov ebx, dword ptr [esi + 52]
                        mov dword ptr [edi + 48], eax
                        mov dword ptr [edi + 52], ebx
                        add esi, 56
                        add edi, 56
                        jmp token_loop
                stream_run_29:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 12]
                        mov ebx, dword ptr [esi + 16]
                        mov ecx, dword ptr [esi + 20]
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], ebx
                        mov dword ptr [edi + 20], ecx
                        mov eax, dword ptr [esi + 24]
                        mov ebx, dword ptr [esi + 28]
                        mov ecx, dword ptr [esi + 32]
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], ebx
                        mov dword ptr [edi + 32], ecx
                        mov eax, dword ptr [esi + 36]
                        mov ebx, dword ptr [esi + 40]
                        mov ecx, dword ptr [esi + 44]
                        mov dword ptr [edi + 36], eax
                        mov dword ptr [edi + 40], ebx
                        mov dword ptr [edi + 44], ecx
                        mov eax, dword ptr [esi + 48]
                        mov ebx, dword ptr [esi + 52]
                        mov cx, word ptr [esi + 56]
                        mov dword ptr [edi + 48], eax
                        mov dword ptr [edi + 52], ebx
                        mov word ptr [edi + 56], cx
                        add esi, 58
                        add edi, 58
                        jmp token_loop
                stream_run_30:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 12]
                        mov ebx, dword ptr [esi + 16]
                        mov ecx, dword ptr [esi + 20]
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], ebx
                        mov dword ptr [edi + 20], ecx
                        mov eax, dword ptr [esi + 24]
                        mov ebx, dword ptr [esi + 28]
                        mov ecx, dword ptr [esi + 32]
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], ebx
                        mov dword ptr [edi + 32], ecx
                        mov eax, dword ptr [esi + 36]
                        mov ebx, dword ptr [esi + 40]
                        mov ecx, dword ptr [esi + 44]
                        mov dword ptr [edi + 36], eax
                        mov dword ptr [edi + 40], ebx
                        mov dword ptr [edi + 44], ecx
                        mov eax, dword ptr [esi + 48]
                        mov ebx, dword ptr [esi + 52]
                        mov ecx, dword ptr [esi + 56]
                        mov dword ptr [edi + 48], eax
                        mov dword ptr [edi + 52], ebx
                        mov dword ptr [edi + 56], ecx
                        add esi, 60
                        add edi, 60
                        jmp token_loop
                stream_run_31:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 12]
                        mov ebx, dword ptr [esi + 16]
                        mov ecx, dword ptr [esi + 20]
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], ebx
                        mov dword ptr [edi + 20], ecx
                        mov eax, dword ptr [esi + 24]
                        mov ebx, dword ptr [esi + 28]
                        mov ecx, dword ptr [esi + 32]
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], ebx
                        mov dword ptr [edi + 32], ecx
                        mov eax, dword ptr [esi + 36]
                        mov ebx, dword ptr [esi + 40]
                        mov ecx, dword ptr [esi + 44]
                        mov dword ptr [edi + 36], eax
                        mov dword ptr [edi + 40], ebx
                        mov dword ptr [edi + 44], ecx
                        mov eax, dword ptr [esi + 48]
                        mov ebx, dword ptr [esi + 52]
                        mov ecx, dword ptr [esi + 56]
                        mov dword ptr [edi + 48], eax
                        mov dword ptr [edi + 52], ebx
                        mov dword ptr [edi + 56], ecx
                        mov ax, word ptr [esi + 60]
                        mov word ptr [edi + 60], ax
                        add esi, 62
                        add edi, 62
                        jmp token_loop
                stream_run_32:
                        mov eax, dword ptr [esi]
                        mov ebx, dword ptr [esi + 4]
                        mov ecx, dword ptr [esi + 8]
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], ebx
                        mov dword ptr [edi + 8], ecx
                        mov eax, dword ptr [esi + 12]
                        mov ebx, dword ptr [esi + 16]
                        mov ecx, dword ptr [esi + 20]
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], ebx
                        mov dword ptr [edi + 20], ecx
                        mov eax, dword ptr [esi + 24]
                        mov ebx, dword ptr [esi + 28]
                        mov ecx, dword ptr [esi + 32]
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], ebx
                        mov dword ptr [edi + 32], ecx
                        mov eax, dword ptr [esi + 36]
                        mov ebx, dword ptr [esi + 40]
                        mov ecx, dword ptr [esi + 44]
                        mov dword ptr [edi + 36], eax
                        mov dword ptr [edi + 40], ebx
                        mov dword ptr [edi + 44], ecx
                        mov eax, dword ptr [esi + 48]
                        mov ebx, dword ptr [esi + 52]
                        mov ecx, dword ptr [esi + 56]
                        mov dword ptr [edi + 48], eax
                        mov dword ptr [edi + 52], ebx
                        mov dword ptr [edi + 56], ecx
                        mov eax, dword ptr [esi + 60]
                        mov dword ptr [edi + 60], eax
                        add esi, 64
                        add edi, 64
                        jmp token_loop
                repeat_run_1:
                        mov word ptr [edi], ax
                        add edi, 2
                        jmp token_loop
                repeat_run_2:
                        mov dword ptr [edi], eax
                        add edi, 4
                        jmp token_loop
                repeat_run_3:
                        mov dword ptr [edi], eax
                        mov word ptr [edi + 4], ax
                        add edi, 6
                        jmp token_loop
                repeat_run_4:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        add edi, 8
                        jmp token_loop
                repeat_run_5:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov word ptr [edi + 8], ax
                        add edi, 10
                        jmp token_loop
                repeat_run_6:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        add edi, 12
                        jmp token_loop
                repeat_run_7:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov word ptr [edi + 12], ax
                        add edi, 14
                        jmp token_loop
                repeat_run_8:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 12], eax
                        add edi, 16
                        jmp token_loop
                repeat_run_9:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 12], eax
                        mov word ptr [edi + 16], ax
                        add edi, 18
                        jmp token_loop
                repeat_run_10:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], eax
                        add edi, 20
                        jmp token_loop
                repeat_run_11:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], eax
                        mov word ptr [edi + 20], ax
                        add edi, 22
                        jmp token_loop
                repeat_run_12:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], eax
                        mov dword ptr [edi + 20], eax
                        add edi, 24
                        jmp token_loop
                repeat_run_13:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], eax
                        mov dword ptr [edi + 20], eax
                        mov word ptr [edi + 24], ax
                        add edi, 26
                        jmp token_loop
                repeat_run_14:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], eax
                        mov dword ptr [edi + 20], eax
                        mov dword ptr [edi + 24], eax
                        add edi, 28
                        jmp token_loop
                repeat_run_15:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], eax
                        mov dword ptr [edi + 20], eax
                        mov dword ptr [edi + 24], eax
                        mov word ptr [edi + 28], ax
                        add edi, 30
                        jmp token_loop
                repeat_run_16:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], eax
                        mov dword ptr [edi + 20], eax
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], eax
                        add edi, 32
                        jmp token_loop
                repeat_run_17:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], eax
                        mov dword ptr [edi + 20], eax
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], eax
                        mov word ptr [edi + 32], ax
                        add edi, 34
                        jmp token_loop
                repeat_run_18:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], eax
                        mov dword ptr [edi + 20], eax
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], eax
                        mov dword ptr [edi + 32], eax
                        add edi, 36
                        jmp token_loop
                repeat_run_19:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], eax
                        mov dword ptr [edi + 20], eax
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], eax
                        mov dword ptr [edi + 32], eax
                        mov word ptr [edi + 36], ax
                        add edi, 38
                        jmp token_loop
                repeat_run_20:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], eax
                        mov dword ptr [edi + 20], eax
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], eax
                        mov dword ptr [edi + 32], eax
                        mov dword ptr [edi + 36], eax
                        add edi, 40
                        jmp token_loop
                repeat_run_21:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], eax
                        mov dword ptr [edi + 20], eax
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], eax
                        mov dword ptr [edi + 32], eax
                        mov dword ptr [edi + 36], eax
                        mov word ptr [edi + 40], ax
                        add edi, 42
                        jmp token_loop
                repeat_run_22:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], eax
                        mov dword ptr [edi + 20], eax
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], eax
                        mov dword ptr [edi + 32], eax
                        mov dword ptr [edi + 36], eax
                        mov dword ptr [edi + 40], eax
                        add edi, 44
                        jmp token_loop
                repeat_run_23:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], eax
                        mov dword ptr [edi + 20], eax
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], eax
                        mov dword ptr [edi + 32], eax
                        mov dword ptr [edi + 36], eax
                        mov dword ptr [edi + 40], eax
                        mov word ptr [edi + 44], ax
                        add edi, 46
                        jmp token_loop
                repeat_run_24:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], eax
                        mov dword ptr [edi + 20], eax
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], eax
                        mov dword ptr [edi + 32], eax
                        mov dword ptr [edi + 36], eax
                        mov dword ptr [edi + 40], eax
                        mov dword ptr [edi + 44], eax
                        add edi, 48
                        jmp token_loop
                repeat_run_25:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], eax
                        mov dword ptr [edi + 20], eax
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], eax
                        mov dword ptr [edi + 32], eax
                        mov dword ptr [edi + 36], eax
                        mov dword ptr [edi + 40], eax
                        mov dword ptr [edi + 44], eax
                        mov word ptr [edi + 48], ax
                        add edi, 50
                        jmp token_loop
                repeat_run_26:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], eax
                        mov dword ptr [edi + 20], eax
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], eax
                        mov dword ptr [edi + 32], eax
                        mov dword ptr [edi + 36], eax
                        mov dword ptr [edi + 40], eax
                        mov dword ptr [edi + 44], eax
                        mov dword ptr [edi + 48], eax
                        add edi, 52
                        jmp token_loop
                repeat_run_27:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], eax
                        mov dword ptr [edi + 20], eax
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], eax
                        mov dword ptr [edi + 32], eax
                        mov dword ptr [edi + 36], eax
                        mov dword ptr [edi + 40], eax
                        mov dword ptr [edi + 44], eax
                        mov dword ptr [edi + 48], eax
                        mov word ptr [edi + 52], ax
                        add edi, 54
                        jmp token_loop
                repeat_run_28:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], eax
                        mov dword ptr [edi + 20], eax
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], eax
                        mov dword ptr [edi + 32], eax
                        mov dword ptr [edi + 36], eax
                        mov dword ptr [edi + 40], eax
                        mov dword ptr [edi + 44], eax
                        mov dword ptr [edi + 48], eax
                        mov dword ptr [edi + 52], eax
                        add edi, 56
                        jmp token_loop
                repeat_run_29:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], eax
                        mov dword ptr [edi + 20], eax
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], eax
                        mov dword ptr [edi + 32], eax
                        mov dword ptr [edi + 36], eax
                        mov dword ptr [edi + 40], eax
                        mov dword ptr [edi + 44], eax
                        mov dword ptr [edi + 48], eax
                        mov dword ptr [edi + 52], eax
                        mov word ptr [edi + 56], ax
                        add edi, 58
                        jmp token_loop
                repeat_run_30:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], eax
                        mov dword ptr [edi + 20], eax
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], eax
                        mov dword ptr [edi + 32], eax
                        mov dword ptr [edi + 36], eax
                        mov dword ptr [edi + 40], eax
                        mov dword ptr [edi + 44], eax
                        mov dword ptr [edi + 48], eax
                        mov dword ptr [edi + 52], eax
                        mov dword ptr [edi + 56], eax
                        add edi, 60
                        jmp token_loop
                repeat_run_31:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], eax
                        mov dword ptr [edi + 20], eax
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], eax
                        mov dword ptr [edi + 32], eax
                        mov dword ptr [edi + 36], eax
                        mov dword ptr [edi + 40], eax
                        mov dword ptr [edi + 44], eax
                        mov dword ptr [edi + 48], eax
                        mov dword ptr [edi + 52], eax
                        mov dword ptr [edi + 56], eax
                        mov word ptr [edi + 60], ax
                        add edi, 62
                        jmp token_loop
                repeat_run_32:
                        mov dword ptr [edi], eax
                        mov dword ptr [edi + 4], eax
                        mov dword ptr [edi + 8], eax
                        mov dword ptr [edi + 12], eax
                        mov dword ptr [edi + 16], eax
                        mov dword ptr [edi + 20], eax
                        mov dword ptr [edi + 24], eax
                        mov dword ptr [edi + 28], eax
                        mov dword ptr [edi + 32], eax
                        mov dword ptr [edi + 36], eax
                        mov dword ptr [edi + 40], eax
                        mov dword ptr [edi + 44], eax
                        mov dword ptr [edi + 48], eax
                        mov dword ptr [edi + 52], eax
                        mov dword ptr [edi + 56], eax
                        mov dword ptr [edi + 60], eax
                        add edi, 64
                        jmp token_loop
                fill_tables:
                        mov edi, repeatedPixelHandlers
                        mov eax, offset repeat_run_1
                        mov dword ptr [edi], eax
                        mov eax, offset repeat_run_2
                        mov dword ptr [edi + 4], eax
                        mov eax, offset repeat_run_3
                        mov dword ptr [edi + 8], eax
                        mov eax, offset repeat_run_4
                        mov dword ptr [edi + 12], eax
                        mov eax, offset repeat_run_5
                        mov dword ptr [edi + 16], eax
                        mov eax, offset repeat_run_6
                        mov dword ptr [edi + 20], eax
                        mov eax, offset repeat_run_7
                        mov dword ptr [edi + 24], eax
                        mov eax, offset repeat_run_8
                        mov dword ptr [edi + 28], eax
                        mov eax, offset repeat_run_9
                        mov dword ptr [edi + 32], eax
                        mov eax, offset repeat_run_10
                        mov dword ptr [edi + 36], eax
                        mov eax, offset repeat_run_11
                        mov dword ptr [edi + 40], eax
                        mov eax, offset repeat_run_12
                        mov dword ptr [edi + 44], eax
                        mov eax, offset repeat_run_13
                        mov dword ptr [edi + 48], eax
                        mov eax, offset repeat_run_14
                        mov dword ptr [edi + 52], eax
                        mov eax, offset repeat_run_15
                        mov dword ptr [edi + 56], eax
                        mov eax, offset repeat_run_16
                        mov dword ptr [edi + 60], eax
                        mov eax, offset repeat_run_17
                        mov dword ptr [edi + 64], eax
                        mov eax, offset repeat_run_18
                        mov dword ptr [edi + 68], eax
                        mov eax, offset repeat_run_19
                        mov dword ptr [edi + 72], eax
                        mov eax, offset repeat_run_20
                        mov dword ptr [edi + 76], eax
                        mov eax, offset repeat_run_21
                        mov dword ptr [edi + 80], eax
                        mov eax, offset repeat_run_22
                        mov dword ptr [edi + 84], eax
                        mov eax, offset repeat_run_23
                        mov dword ptr [edi + 88], eax
                        mov eax, offset repeat_run_24
                        mov dword ptr [edi + 92], eax
                        mov eax, offset repeat_run_25
                        mov dword ptr [edi + 96], eax
                        mov eax, offset repeat_run_26
                        mov dword ptr [edi + 100], eax
                        mov eax, offset repeat_run_27
                        mov dword ptr [edi + 104], eax
                        mov eax, offset repeat_run_28
                        mov dword ptr [edi + 108], eax
                        mov eax, offset repeat_run_29
                        mov dword ptr [edi + 112], eax
                        mov eax, offset repeat_run_30
                        mov dword ptr [edi + 116], eax
                        mov eax, offset repeat_run_31
                        mov dword ptr [edi + 120], eax
                        mov eax, offset repeat_run_32
                        mov dword ptr [edi + 124], eax
                        mov edi, streamRunHandlers
                        mov eax, offset stream_run_1
                        mov dword ptr [edi], eax
                        mov eax, offset stream_run_2
                        mov dword ptr [edi + 4], eax
                        mov eax, offset stream_run_3
                        mov dword ptr [edi + 8], eax
                        mov eax, offset stream_run_4
                        mov dword ptr [edi + 12], eax
                        mov eax, offset stream_run_5
                        mov dword ptr [edi + 16], eax
                        mov eax, offset stream_run_6
                        mov dword ptr [edi + 20], eax
                        mov eax, offset stream_run_7
                        mov dword ptr [edi + 24], eax
                        mov eax, offset stream_run_8
                        mov dword ptr [edi + 28], eax
                        mov eax, offset stream_run_9
                        mov dword ptr [edi + 32], eax
                        mov eax, offset stream_run_10
                        mov dword ptr [edi + 36], eax
                        mov eax, offset stream_run_11
                        mov dword ptr [edi + 40], eax
                        mov eax, offset stream_run_12
                        mov dword ptr [edi + 44], eax
                        mov eax, offset stream_run_13
                        mov dword ptr [edi + 48], eax
                        mov eax, offset stream_run_14
                        mov dword ptr [edi + 52], eax
                        mov eax, offset stream_run_15
                        mov dword ptr [edi + 56], eax
                        mov eax, offset stream_run_16
                        mov dword ptr [edi + 60], eax
                        mov eax, offset stream_run_17
                        mov dword ptr [edi + 64], eax
                        mov eax, offset stream_run_18
                        mov dword ptr [edi + 68], eax
                        mov eax, offset stream_run_19
                        mov dword ptr [edi + 72], eax
                        mov eax, offset stream_run_20
                        mov dword ptr [edi + 76], eax
                        mov eax, offset stream_run_21
                        mov dword ptr [edi + 80], eax
                        mov eax, offset stream_run_22
                        mov dword ptr [edi + 84], eax
                        mov eax, offset stream_run_23
                        mov dword ptr [edi + 88], eax
                        mov eax, offset stream_run_24
                        mov dword ptr [edi + 92], eax
                        mov eax, offset stream_run_25
                        mov dword ptr [edi + 96], eax
                        mov eax, offset stream_run_26
                        mov dword ptr [edi + 100], eax
                        mov eax, offset stream_run_27
                        mov dword ptr [edi + 104], eax
                        mov eax, offset stream_run_28
                        mov dword ptr [edi + 108], eax
                        mov eax, offset stream_run_29
                        mov dword ptr [edi + 112], eax
                        mov eax, offset stream_run_30
                        mov dword ptr [edi + 116], eax
                        mov eax, offset stream_run_31
                        mov dword ptr [edi + 120], eax
                        mov eax, offset stream_run_32
                        mov dword ptr [edi + 124], eax
                        jmp draw_start
                done:
                }
                // clang-format on
            } else {
                DAT_TextureRenderCoreObject::instance.currentRenderSurface
                    = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                lineTail = 4056 * 2;
                lineStride = 4056 * 2;
                heightStart = this->mapGameSurfaceHeightRange.start;
                if (drawY + imageHeight > this->mapGameSurfaceHeightRange.end) {
                    imageHeight -= drawY + imageHeight - this->mapGameSurfaceHeightRange.end;
                    if (imageHeight <= 0) {
                        return;
                    }
                }
                // clang-format off
                __asm {
                        mov esi, imageAddress
                        mov edi, DAT_TextureRenderCoreObject::instance.currentRenderSurface
                        mov eax, drawX
                        cmp eax, 0
                        jl zoom_done
                        and eax, 0xfffffffe
                        add edi, eax
                        mov eax, drawY
                        mov ebx, heightStart
                        cmp eax, ebx
                        jge zoom_row_start
                        sub ebx, eax
                        mov eax, ebx
                        cmp imageHeight, eax
                        jle zoom_done
                        sub imageHeight, eax
                zoom_skip_rows_above_top:
                        mov bl, byte ptr [esi]
                        movzx ecx, bl
                        and bl, TGX_TYPE_MASK
                        and cl, TGX_LENGTH_MASK
                        add esi, 1
                        cmp bl, TGX_SKIP
                        je zoom_skip_rows_above_top
                        cmp bl, TGX_STREAM
                        je zoom_skip_rows_stream
                        cmp bl, TGX_REPEAT
                        je zoom_skip_rows_repeat
                        jmp zoom_skip_rows_new_line
                zoom_skip_rows_stream:
                        add ecx, 1
                        add ecx, ecx
                        add esi, ecx
                        jmp zoom_skip_rows_above_top
                zoom_skip_rows_repeat:
                        add esi, 2
                        jmp zoom_skip_rows_above_top
                zoom_skip_rows_new_line:
                        sub eax, 1
                        jg zoom_skip_rows_above_top
                        mov eax, heightStart
                zoom_row_start:
                        mov edx, lineStride
                        mov ecx, eax
                        shr eax, 1
                        mul edx
                        add edi, eax
                        xor eax, eax
                        xor ebx, ebx
                        mov oddColumn, ebx
                        mov edx, imageHeight
                zoom_token_loop:
                        mov al, byte ptr [esi]
                        movzx ecx, al
                        and al, TGX_TYPE_MASK
                        and cl, TGX_LENGTH_MASK
                        add esi, 1
                        cmp al, TGX_SKIP
                        je zoom_token_skip
                        cmp al, TGX_STREAM
                        je zoom_token_stream
                        cmp al, TGX_REPEAT
                        je zoom_token_repeat
                        add edi, lineTail
                        sub edx, 1
                        jle zoom_done
                zoom_skip_odd_row:
                        mov bl, byte ptr [esi]
                        movzx ecx, bl
                        and bl, TGX_TYPE_MASK
                        and cl, TGX_LENGTH_MASK
                        add esi, 1
                        cmp bl, TGX_SKIP
                        je zoom_skip_odd_row
                        cmp bl, TGX_STREAM
                        je zoom_odd_row_stream
                        cmp bl, TGX_REPEAT
                        je zoom_odd_row_repeat
                        jmp zoom_odd_row_new_line
                zoom_odd_row_stream:
                        add ecx, 1
                        add ecx, ecx
                        add esi, ecx
                        jmp zoom_skip_odd_row
                zoom_odd_row_repeat:
                        add esi, 2
                        jmp zoom_skip_odd_row
                zoom_odd_row_new_line:
                        xor eax, eax
                        xor ebx, ebx
                        mov oddColumn, ebx
                        sub edx, 1
                        jg zoom_token_loop
                        jmp zoom_done
                zoom_token_skip:
                        add ecx, 1
                        add oddColumn, ecx
                        jmp zoom_token_loop
                zoom_token_repeat:
                        movzx eax, word ptr [esi]
                        add esi, 2
                        add ecx, 1
                        mov ebx, oddColumn
                        add oddColumn, ecx
                zoom_repeat_pixel:
                        test ebx, 1
                        jne zoom_repeat_next
                        mov word ptr [edi + ebx], ax
                zoom_repeat_next:
                        add ebx, 1
                        sub ecx, 1
                        jne zoom_repeat_pixel
                        jmp zoom_token_loop
                zoom_token_stream:
                        add ecx, 1
                        mov ebx, oddColumn
                        add oddColumn, ecx
                zoom_stream_pixel:
                        test ebx, 1
                        jne zoom_stream_next
                        mov ax, word ptr [esi]
                        mov word ptr [edi + ebx], ax
                zoom_stream_next:
                        add ebx, 1
                        add esi, 2
                        sub ecx, 1
                        jne zoom_stream_pixel
                        jmp zoom_token_loop
                zoom_done:
                }
                // clang-format on
            }
        }

    }
}
}
