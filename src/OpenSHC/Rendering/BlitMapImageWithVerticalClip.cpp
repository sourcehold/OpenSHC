#include "../Rendering.func.hpp"

#include "OpenSHC/Globals/DAT_00ed3154.hpp"
#include "OpenSHC/Globals/DAT_00ed316c.hpp"
#include "OpenSHC/Globals/DAT_00ed3170.hpp"
#include "OpenSHC/Globals/DAT_00ed317c.hpp"
#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GMImageOffsets.hpp"
#include "OpenSHC/Globals/DAT_GmImageAddressToBeRendered.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_DrawSomeX.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_DrawSomeY.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_YOffset.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {

// Copies a 30-pixel-wide map image column (tile objects are stored as 15 dwords per row) onto the map surface,
// clipped to the visible rows. When DAT_00ed3170 asks for more rows than the image has, the rest comes from a
// second image (DAT_00ed316c). DAT_00ed317c picks which half of the column is drawn (0 both, 1 right, 2 left,
// 3 only the middle column). Zoomed out, every other row and pixel is used.
// The copy loops are handwritten assembly in the original, transcribed here from the binary.

// FUNCTION: STRONGHOLDCRUSADER 0x00453B00
void Rendering::BlitMapImageWithVerticalClip()
{
    // The asm below names these globals, which inline asm can only do once C++ code has instantiated them;
    // sizeof does that without generating any code.
    (void)sizeof(DAT_WindowAndDirectDraw::instance);
    (void)sizeof(DAT_RenderMap_DrawSomeX::instance);
    (void)sizeof(DAT_00ed317c::instance);
    char* image = (char*)DAT_TextureRenderCoreObject::instance.gmProcessedImageData;
    char* nextImage = (char*)DAT_TextureRenderCoreObject::instance.gmProcessedImageData;
    int drawY = DAT_RenderMap_DrawSomeY::instance + (DAT_00ed3154::instance - DAT_RenderMap_YOffset::instance) + 9;
    int height = DAT_GMImageHeaders::instance.imh[DAT_GmImageAddressToBeRendered::instance].height - 7;
    int skip = 0;
    int nextSkip = 0;
    if (DAT_00ed3170::instance <= 0) {
        return;
    }
    if (drawY < DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start) {
        int const clippedRows = DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start - drawY;
        nextSkip = DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start - height - drawY;
        drawY = DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start;
        DAT_00ed3170::instance -= clippedRows;
        height -= clippedRows;
        // An image row is 60 bytes (15 dwords).
        skip = clippedRows * 60;
    }
    if (DAT_00ed3170::instance + drawY >= DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.end) {
        DAT_00ed3170::instance = DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.end - drawY;
        // fixme: always adds 0, the original subtracts the already shortened row count
        height += DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.end - DAT_00ed3170::instance - drawY;
    }
    int firstRows;
    if (height <= 0) {
        firstRows = 0;
        nextSkip *= 60;
    } else if (height < DAT_00ed3170::instance) {
        firstRows = height;
        DAT_00ed3170::instance -= height;
        nextSkip = 0;
    } else {
        firstRows = DAT_00ed3170::instance;
        DAT_00ed3170::instance = 0;
    }
    image += DAT_GMImageOffsets::instance[DAT_GmImageAddressToBeRendered::instance];
    nextImage += DAT_GMImageOffsets::instance[DAT_00ed316c::instance];
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
            mov edx, 0x1fb0
            mul edx
            add edi, eax
            mov edx, firstRows
            cmp edx, 0
            jle next_image
        row_start:
            mov eax, DAT_00ed317c::instance
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
            mov dword ptr [edi + 0x1fb4], ebx
            mov dword ptr [edi + 0x3f68], ecx
            mov eax, dword ptr [esi + 0xc]
            mov ebx, dword ptr [esi + 0x10]
            mov ecx, dword ptr [esi + 0x14]
            mov dword ptr [edi + 0x5f1c], eax
            mov dword ptr [edi + 0x7ed0], ebx
            mov dword ptr [edi + 0x9e84], ecx
            mov eax, dword ptr [esi + 0x18]
            mov ebx, dword ptr [esi + 0x1c]
            mov ecx, dword ptr [esi + 0x20]
            mov dword ptr [edi + 0xbe38], eax
            mov dword ptr [edi + 0xddec], ebx
            mov dword ptr [edi + 0xbe40], ecx
            mov eax, dword ptr [esi + 0x24]
            mov ebx, dword ptr [esi + 0x28]
            mov ecx, dword ptr [esi + 0x2c]
            mov dword ptr [edi + 0x9e94], eax
            mov dword ptr [edi + 0x7ee8], ebx
            mov dword ptr [edi + 0x5f3c], ecx
            mov eax, dword ptr [esi + 0x30]
            mov ebx, dword ptr [esi + 0x34]
            mov ecx, dword ptr [esi + 0x38]
            mov dword ptr [edi + 0x3f90], eax
            mov dword ptr [edi + 0x1fe4], ebx
            mov dword ptr [edi + 0x38], ecx
            add esi, 0x3c
            add edi, 0x1fb0
            sub edx, 1
            cmp edx, 0
            jle next_image
            jmp copy_whole_row
        copy_right_half:
            mov ebx, dword ptr [esi + 0x1c]
            mov ecx, dword ptr [esi + 0x20]
            mov dword ptr [edi + 0xddec], ebx
            mov dword ptr [edi + 0xbe40], ecx
            mov eax, dword ptr [esi + 0x24]
            mov ebx, dword ptr [esi + 0x28]
            mov ecx, dword ptr [esi + 0x2c]
            mov dword ptr [edi + 0x9e94], eax
            mov dword ptr [edi + 0x7ee8], ebx
            mov dword ptr [edi + 0x5f3c], ecx
            mov eax, dword ptr [esi + 0x30]
            mov ebx, dword ptr [esi + 0x34]
            mov ecx, dword ptr [esi + 0x38]
            mov dword ptr [edi + 0x3f90], eax
            mov dword ptr [edi + 0x1fe4], ebx
            mov dword ptr [edi + 0x38], ecx
            add esi, 0x3c
            add edi, 0x1fb0
            sub edx, 1
            cmp edx, 0
            jle next_image
            jmp copy_right_half
        copy_left_half:
            mov eax, dword ptr [esi]
            mov ebx, dword ptr [esi + 4]
            mov ecx, dword ptr [esi + 8]
            mov dword ptr [edi], eax
            mov dword ptr [edi + 0x1fb4], ebx
            mov dword ptr [edi + 0x3f68], ecx
            mov eax, dword ptr [esi + 0xc]
            mov ebx, dword ptr [esi + 0x10]
            mov ecx, dword ptr [esi + 0x14]
            mov dword ptr [edi + 0x5f1c], eax
            mov dword ptr [edi + 0x7ed0], ebx
            mov dword ptr [edi + 0x9e84], ecx
            mov eax, dword ptr [esi + 0x18]
            mov ebx, dword ptr [esi + 0x1c]
            mov dword ptr [edi + 0xbe38], eax
            mov dword ptr [edi + 0xddec], ebx
            add esi, 0x3c
            add edi, 0x1fb0
            sub edx, 1
            cmp edx, 0
            jle next_image
            jmp copy_left_half
        copy_middle:
            mov ebx, dword ptr [esi + 0x1c]
            mov dword ptr [edi + 0xddec], ebx
            add esi, 0x3c
            add edi, 0x1fb0
            sub edx, 1
            cmp edx, 0
            jle next_image
            jmp copy_middle
        next_image:
            cmp DAT_00ed3170::instance, 0
            jle done
            mov edx, DAT_00ed3170::instance
            mov DAT_00ed3170::instance, 0
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
        mov edx, 0x1fb0
        mul edx
        add edi, eax
        mov edx, firstRows
        cmp edx, 0
        jle zoom_next_image
    zoom_row_start:
        mov eax, DAT_00ed317c::instance
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
        mov word ptr [edi + 0x1fb4], bx
        mov ax, word ptr [esi + 0x10]
        mov bx, word ptr [esi + 0x18]
        mov word ptr [edi + 0x3f68], ax
        mov word ptr [edi + 0x5f1c], bx
        mov ax, word ptr [esi + 0x20]
        mov bx, word ptr [esi + 0x28]
        mov word ptr [edi + 0x5f20], ax
        mov word ptr [edi + 0x3f74], bx
        mov ax, word ptr [esi + 0x30]
        mov bx, word ptr [esi + 0x38]
        mov word ptr [edi + 0x1fc8], ax
        mov word ptr [edi + 0x1c], bx
        add esi, 0x3c
        add ecx, 1
        sub edx, 1
        cmp edx, 0
        jle zoom_next_image
        jmp zoom_whole_row
    zoom_whole_row_odd:
        add edi, 0x1fb0
        mov ax, word ptr [esi + 4]
        mov bx, word ptr [esi + 0xc]
        mov word ptr [edi + 2], ax
        mov word ptr [edi + 0x1fb6], bx
        mov ax, word ptr [esi + 0x14]
        mov bx, word ptr [esi + 0x1c]
        mov word ptr [edi + 0x3f6a], ax
        mov word ptr [edi + 0x5f1e], bx
        mov ax, word ptr [esi + 0x24]
        mov bx, word ptr [esi + 0x2c]
        mov word ptr [edi + 0x3f72], ax
        mov word ptr [edi + 0x1fc6], bx
        mov ax, word ptr [esi + 0x34]
        mov word ptr [edi + 0x1a], ax
        add esi, 0x3c
        add ecx, 1
        sub edx, 1
        cmp edx, 0
        jle zoom_next_image
        jmp zoom_whole_row
    zoom_right_half:
        mov eax, ecx
        and eax, 1
        jne zoom_right_half_odd
        mov ax, word ptr [esi + 0x20]
        mov bx, word ptr [esi + 0x28]
        mov word ptr [edi + 0x5f20], ax
        mov word ptr [edi + 0x3f74], bx
        mov ax, word ptr [esi + 0x30]
        mov bx, word ptr [esi + 0x38]
        mov word ptr [edi + 0x1fc8], ax
        mov word ptr [edi + 0x1c], bx
        add esi, 0x3c
        add ecx, 1
        sub edx, 1
        cmp edx, 0
        jle zoom_next_image
        jmp zoom_right_half
    zoom_right_half_odd:
        add edi, 0x1fb0
        mov ax, word ptr [esi + 0x1c]
        mov bx, word ptr [esi + 0x24]
        mov word ptr [edi + 0x5f1e], ax
        mov word ptr [edi + 0x3f72], bx
        mov ax, word ptr [esi + 0x2c]
        mov bx, word ptr [esi + 0x34]
        mov word ptr [edi + 0x1fc6], ax
        mov word ptr [edi + 0x1a], bx
        add esi, 0x3c
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
        mov word ptr [edi + 0x1fb4], bx
        mov ax, word ptr [esi + 0x10]
        mov bx, word ptr [esi + 0x18]
        mov word ptr [edi + 0x3f68], ax
        mov word ptr [edi + 0x5f1c], bx
        add esi, 0x3c
        add ecx, 1
        sub edx, 1
        cmp edx, 0
        jle zoom_next_image
        jmp zoom_left_half
    zoom_left_half_odd:
        add edi, 0x1fb0
        mov ax, word ptr [esi + 4]
        mov bx, word ptr [esi + 0xc]
        mov word ptr [edi + 2], ax
        mov word ptr [edi + 0x1fb6], bx
        mov ax, word ptr [esi + 0x14]
        mov bx, word ptr [esi + 0x1c]
        mov word ptr [edi + 0x3f6a], ax
        mov word ptr [edi + 0x5f1e], bx
        add esi, 0x3c
        add ecx, 1
        sub edx, 1
        cmp edx, 0
        jle zoom_next_image
        jmp zoom_left_half
    zoom_middle:
        mov eax, ecx
        and eax, 1
        jne zoom_middle_odd
        add esi, 0x3c
        add ecx, 1
        sub edx, 1
        cmp edx, 0
        jle zoom_next_image
        jmp zoom_middle
    zoom_middle_odd:
        add edi, 0x1fb0
        mov ax, word ptr [esi + 0x1c]
        mov word ptr [edi + 0x5f1e], ax
        add esi, 0x3c
        add ecx, 1
        sub edx, 1
        cmp edx, 0
        jle zoom_next_image
        jmp zoom_middle
    zoom_next_image:
        cmp DAT_00ed3170::instance, 0
        jle zoom_done
        mov edx, DAT_00ed3170::instance
        mov DAT_00ed3170::instance, 0
        mov esi, dword ptr nextImage
        mov eax, dword ptr nextSkip
        add esi, eax
        jmp zoom_row_start
    zoom_done:
    }
    // clang-format on
}

}
