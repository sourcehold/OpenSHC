#include "../Rendering.func.hpp"

#include "OpenSHC/Globals/DAT_00ed3154.hpp"
#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GMImageOffsets.hpp"
#include "OpenSHC/Globals/DAT_GmImageAddressToBeRendered.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_DrawSomeX.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_DrawSomeY.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_RowsLeft.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_SecondBlitImageIndex.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_WhatToDraw.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_YOffset.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {

// Copies a 30-pixel-wide map image column (tile objects are stored as 15 dwords per row) onto the map surface,
// clipped to the visible rows. When DAT_RenderMap_RowsLeft asks for more rows than the image has, the rest comes
// from a second image (DAT_RenderMap_SecondBlitImageIndex). DAT_RenderMap_WhatToDraw picks which half of the column
// is drawn (0 both, 1 right, 2 left, 3 only the middle column). Zoomed out, every other row and pixel is used.
// The copy loops are handwritten assembly in the original, transcribed here from the binary.

// One row of the 4056-pixel map surface, in bytes.
enum { MAP_ROW = 4056 * 2 };

// One row of a map image: 15 dwords.
enum { IMAGE_ROW = 60 };

// FUNCTION: STRONGHOLDCRUSADER 0x00453B00
void Rendering::BlitMapImageWithVerticalClip()
{
    // The asm below names these globals, which inline asm can only do once C++ code has instantiated them;
    // sizeof does that without generating any code.
    (void)sizeof(DAT_WindowAndDirectDraw::instance);
    (void)sizeof(DAT_RenderMap_DrawSomeX::instance);
    (void)sizeof(DAT_RenderMap_WhatToDraw::instance);
    char* image = (char*)DAT_TextureRenderCoreObject::instance.gmProcessedImageData;
    char* nextImage = (char*)DAT_TextureRenderCoreObject::instance.gmProcessedImageData;
    int drawY = DAT_RenderMap_DrawSomeY::instance + (DAT_00ed3154::instance - DAT_RenderMap_YOffset::instance) + 9;
    int height = DAT_GMImageHeaders::instance.imh[DAT_GmImageAddressToBeRendered::instance].height - 7;
    int skip = 0;
    int nextSkip = 0;
    if (DAT_RenderMap_RowsLeft::instance <= 0) {
        return;
    }
    if (drawY < DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start) {
        int const clippedRows = DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start - drawY;
        nextSkip = DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start - height - drawY;
        drawY = DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start;
        DAT_RenderMap_RowsLeft::instance -= clippedRows;
        height -= clippedRows;
        skip = clippedRows * IMAGE_ROW;
    }
    if (DAT_RenderMap_RowsLeft::instance + drawY
        >= DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.end) {
        DAT_RenderMap_RowsLeft::instance = DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.end - drawY;
        // fixme: always adds 0, the original subtracts the already shortened row count
        height += DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.end - DAT_RenderMap_RowsLeft::instance
            - drawY;
    }
    int firstRows;
    if (height <= 0) {
        firstRows = 0;
        nextSkip *= IMAGE_ROW;
    } else if (height < DAT_RenderMap_RowsLeft::instance) {
        firstRows = height;
        DAT_RenderMap_RowsLeft::instance -= height;
        nextSkip = 0;
    } else {
        firstRows = DAT_RenderMap_RowsLeft::instance;
        DAT_RenderMap_RowsLeft::instance = 0;
    }
    image += DAT_GMImageOffsets::instance[DAT_GmImageAddressToBeRendered::instance];
    nextImage += DAT_GMImageOffsets::instance[DAT_RenderMap_SecondBlitImageIndex::instance];
    if (!DAT_TextureRenderCoreObject::instance.isZoom2) {
        // clang-format off
        __asm {
            mov esi, image
            mov eax, skip
            add esi, eax
            mov edi, DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame
            mov eax, DAT_RenderMap_DrawSomeX::instance
            add eax, eax
            add edi, eax
            mov eax, drawY
            mov edx, MAP_ROW
            mul edx
            add edi, eax
            mov edx, firstRows
            cmp edx, 0
            jle next_image
        row_start:
            mov eax, DAT_RenderMap_WhatToDraw::instance
            cmp eax, 1
            je copy_right_half
            cmp eax, 2
            je copy_left_half
            cmp eax, 3
            je copy_middle
        copy_whole_row:
            mov eax, dword ptr [esi]
            mov ebx, dword ptr [esi + 4]
            mov ecx, dword ptr [esi + 8]
            mov dword ptr [edi], eax
            mov dword ptr [edi + MAP_ROW + 4], ebx
            mov dword ptr [edi + 2 * MAP_ROW + 8], ecx
            mov eax, dword ptr [esi + 12]
            mov ebx, dword ptr [esi + 16]
            mov ecx, dword ptr [esi + 20]
            mov dword ptr [edi + 3 * MAP_ROW + 12], eax
            mov dword ptr [edi + 4 * MAP_ROW + 16], ebx
            mov dword ptr [edi + 5 * MAP_ROW + 20], ecx
            mov eax, dword ptr [esi + 24]
            mov ebx, dword ptr [esi + 28]
            mov ecx, dword ptr [esi + 32]
            mov dword ptr [edi + 6 * MAP_ROW + 24], eax
            mov dword ptr [edi + 7 * MAP_ROW + 28], ebx
            mov dword ptr [edi + 6 * MAP_ROW + 32], ecx
            mov eax, dword ptr [esi + 36]
            mov ebx, dword ptr [esi + 40]
            mov ecx, dword ptr [esi + 44]
            mov dword ptr [edi + 5 * MAP_ROW + 36], eax
            mov dword ptr [edi + 4 * MAP_ROW + 40], ebx
            mov dword ptr [edi + 3 * MAP_ROW + 44], ecx
            mov eax, dword ptr [esi + 48]
            mov ebx, dword ptr [esi + 52]
            mov ecx, dword ptr [esi + 56]
            mov dword ptr [edi + 2 * MAP_ROW + 48], eax
            mov dword ptr [edi + MAP_ROW + 52], ebx
            mov dword ptr [edi + 56], ecx
            add esi, IMAGE_ROW
            add edi, MAP_ROW
            sub edx, 1
            cmp edx, 0
            jle next_image
            jmp copy_whole_row
        copy_right_half:
            mov ebx, dword ptr [esi + 28]
            mov ecx, dword ptr [esi + 32]
            mov dword ptr [edi + 7 * MAP_ROW + 28], ebx
            mov dword ptr [edi + 6 * MAP_ROW + 32], ecx
            mov eax, dword ptr [esi + 36]
            mov ebx, dword ptr [esi + 40]
            mov ecx, dword ptr [esi + 44]
            mov dword ptr [edi + 5 * MAP_ROW + 36], eax
            mov dword ptr [edi + 4 * MAP_ROW + 40], ebx
            mov dword ptr [edi + 3 * MAP_ROW + 44], ecx
            mov eax, dword ptr [esi + 48]
            mov ebx, dword ptr [esi + 52]
            mov ecx, dword ptr [esi + 56]
            mov dword ptr [edi + 2 * MAP_ROW + 48], eax
            mov dword ptr [edi + MAP_ROW + 52], ebx
            mov dword ptr [edi + 56], ecx
            add esi, IMAGE_ROW
            add edi, MAP_ROW
            sub edx, 1
            cmp edx, 0
            jle next_image
            jmp copy_right_half
        copy_left_half:
            mov eax, dword ptr [esi]
            mov ebx, dword ptr [esi + 4]
            mov ecx, dword ptr [esi + 8]
            mov dword ptr [edi], eax
            mov dword ptr [edi + MAP_ROW + 4], ebx
            mov dword ptr [edi + 2 * MAP_ROW + 8], ecx
            mov eax, dword ptr [esi + 12]
            mov ebx, dword ptr [esi + 16]
            mov ecx, dword ptr [esi + 20]
            mov dword ptr [edi + 3 * MAP_ROW + 12], eax
            mov dword ptr [edi + 4 * MAP_ROW + 16], ebx
            mov dword ptr [edi + 5 * MAP_ROW + 20], ecx
            mov eax, dword ptr [esi + 24]
            mov ebx, dword ptr [esi + 28]
            mov dword ptr [edi + 6 * MAP_ROW + 24], eax
            mov dword ptr [edi + 7 * MAP_ROW + 28], ebx
            add esi, IMAGE_ROW
            add edi, MAP_ROW
            sub edx, 1
            cmp edx, 0
            jle next_image
            jmp copy_left_half
        copy_middle:
            mov ebx, dword ptr [esi + 28]
            mov dword ptr [edi + 7 * MAP_ROW + 28], ebx
            add esi, IMAGE_ROW
            add edi, MAP_ROW
            sub edx, 1
            cmp edx, 0
            jle next_image
            jmp copy_middle
        next_image:
            cmp DAT_RenderMap_RowsLeft::instance, 0
            jle done
            mov edx, DAT_RenderMap_RowsLeft::instance
            mov DAT_RenderMap_RowsLeft::instance, 0
            mov esi, dword ptr nextImage
            mov eax, dword ptr nextSkip
            add esi, eax
            jmp row_start
        done:
        }
        // clang-format on
        return;
    }
    // clang-format off
    __asm {
        mov esi, image
        mov eax, skip
        add esi, eax
        mov edi, DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame
        mov eax, DAT_RenderMap_DrawSomeX::instance
        and eax, 0xfffffffe
        add edi, eax
        mov eax, drawY
        mov ecx, eax
        shr eax, 1
        mov edx, MAP_ROW
        mul edx
        add edi, eax
        mov edx, firstRows
        cmp edx, 0
        jle zoom_next_image
    zoom_row_start:
        mov eax, DAT_RenderMap_WhatToDraw::instance
        cmp eax, 1
        je zoom_right_half
        cmp eax, 2
        je zoom_left_half
        cmp eax, 3
        je zoom_middle
    zoom_whole_row:
        mov eax, ecx
        and eax, 1
        cmp eax, 0
        jne zoom_whole_row_odd
        mov ax, word ptr [esi]
        mov bx, word ptr [esi + 8]
        mov word ptr [edi], ax
        mov word ptr [edi + MAP_ROW + 4], bx
        mov ax, word ptr [esi + 16]
        mov bx, word ptr [esi + 24]
        mov word ptr [edi + 2 * MAP_ROW + 8], ax
        mov word ptr [edi + 3 * MAP_ROW + 12], bx
        mov ax, word ptr [esi + 32]
        mov bx, word ptr [esi + 40]
        mov word ptr [edi + 3 * MAP_ROW + 16], ax
        mov word ptr [edi + 2 * MAP_ROW + 20], bx
        mov ax, word ptr [esi + 48]
        mov bx, word ptr [esi + 56]
        mov word ptr [edi + MAP_ROW + 24], ax
        mov word ptr [edi + 28], bx
        add esi, IMAGE_ROW
        add ecx, 1
        sub edx, 1
        cmp edx, 0
        jle zoom_next_image
        jmp zoom_whole_row
    zoom_whole_row_odd:
        add edi, MAP_ROW
        mov ax, word ptr [esi + 4]
        mov bx, word ptr [esi + 12]
        mov word ptr [edi + 2], ax
        mov word ptr [edi + MAP_ROW + 6], bx
        mov ax, word ptr [esi + 20]
        mov bx, word ptr [esi + 28]
        mov word ptr [edi + 2 * MAP_ROW + 10], ax
        mov word ptr [edi + 3 * MAP_ROW + 14], bx
        mov ax, word ptr [esi + 36]
        mov bx, word ptr [esi + 44]
        mov word ptr [edi + 2 * MAP_ROW + 18], ax
        mov word ptr [edi + MAP_ROW + 22], bx
        mov ax, word ptr [esi + 52]
        mov word ptr [edi + 26], ax
        add esi, IMAGE_ROW
        add ecx, 1
        sub edx, 1
        cmp edx, 0
        jle zoom_next_image
        jmp zoom_whole_row
    zoom_right_half:
        mov eax, ecx
        and eax, 1
        jne zoom_right_half_odd
        mov ax, word ptr [esi + 32]
        mov bx, word ptr [esi + 40]
        mov word ptr [edi + 3 * MAP_ROW + 16], ax
        mov word ptr [edi + 2 * MAP_ROW + 20], bx
        mov ax, word ptr [esi + 48]
        mov bx, word ptr [esi + 56]
        mov word ptr [edi + MAP_ROW + 24], ax
        mov word ptr [edi + 28], bx
        add esi, IMAGE_ROW
        add ecx, 1
        sub edx, 1
        cmp edx, 0
        jle zoom_next_image
        jmp zoom_right_half
    zoom_right_half_odd:
        add edi, MAP_ROW
        mov ax, word ptr [esi + 28]
        mov bx, word ptr [esi + 36]
        mov word ptr [edi + 3 * MAP_ROW + 14], ax
        mov word ptr [edi + 2 * MAP_ROW + 18], bx
        mov ax, word ptr [esi + 44]
        mov bx, word ptr [esi + 52]
        mov word ptr [edi + MAP_ROW + 22], ax
        mov word ptr [edi + 26], bx
        add esi, IMAGE_ROW
        add ecx, 1
        sub edx, 1
        cmp edx, 0
        jle zoom_next_image
        jmp zoom_right_half
    zoom_left_half:
        mov eax, ecx
        and eax, 1
        jne zoom_left_half_odd
        mov ax, word ptr [esi]
        mov bx, word ptr [esi + 8]
        mov word ptr [edi], ax
        mov word ptr [edi + MAP_ROW + 4], bx
        mov ax, word ptr [esi + 16]
        mov bx, word ptr [esi + 24]
        mov word ptr [edi + 2 * MAP_ROW + 8], ax
        mov word ptr [edi + 3 * MAP_ROW + 12], bx
        add esi, IMAGE_ROW
        add ecx, 1
        sub edx, 1
        cmp edx, 0
        jle zoom_next_image
        jmp zoom_left_half
    zoom_left_half_odd:
        add edi, MAP_ROW
        mov ax, word ptr [esi + 4]
        mov bx, word ptr [esi + 12]
        mov word ptr [edi + 2], ax
        mov word ptr [edi + MAP_ROW + 6], bx
        mov ax, word ptr [esi + 20]
        mov bx, word ptr [esi + 28]
        mov word ptr [edi + 2 * MAP_ROW + 10], ax
        mov word ptr [edi + 3 * MAP_ROW + 14], bx
        add esi, IMAGE_ROW
        add ecx, 1
        sub edx, 1
        cmp edx, 0
        jle zoom_next_image
        jmp zoom_left_half
    zoom_middle:
        mov eax, ecx
        and eax, 1
        jne zoom_middle_odd
        add esi, IMAGE_ROW
        add ecx, 1
        sub edx, 1
        cmp edx, 0
        jle zoom_next_image
        jmp zoom_middle
    zoom_middle_odd:
        add edi, MAP_ROW
        mov ax, word ptr [esi + 28]
        mov word ptr [edi + 3 * MAP_ROW + 14], ax
        add esi, IMAGE_ROW
        add ecx, 1
        sub edx, 1
        cmp edx, 0
        jle zoom_next_image
        jmp zoom_middle
    zoom_next_image:
        cmp DAT_RenderMap_RowsLeft::instance, 0
        jle zoom_done
        mov edx, DAT_RenderMap_RowsLeft::instance
        mov DAT_RenderMap_RowsLeft::instance, 0
        mov esi, dword ptr nextImage
        mov eax, dword ptr nextSkip
        add esi, eax
        jmp zoom_row_start
    zoom_done:
    }
    // clang-format on
}

}
