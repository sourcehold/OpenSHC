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

using UI::Rendering::WindowAndDirectDraw;

// Like BlitMapImageWithVerticalClip, but the second image (DAT_00ed316c) starts 160 - DAT_RenderMap_YOffset rows in.
// The copy loops are handwritten assembly in the original, transcribed here from the binary.

// Inline assembly cannot name a resolver global, so the loops reach the globals they use through these.
static WindowAndDirectDraw* const s_windowAndDirectDraw = &DAT_WindowAndDirectDraw::instance;
static uint* const s_drawSomeX = &DAT_RenderMap_DrawSomeX::instance;
static uint* const s_blitModeUnk = &DAT_00ed317c::instance;
static uint* const s_remainingRowsUnk = &DAT_00ed3170::instance;

// FUNCTION: STRONGHOLDCRUSADER 0x00454080
void Rendering::BlitMapImageWithVerticalClipAndYOffset()
{
    char* image = (char*)DAT_TextureRenderCoreObject::instance.gmProcessedImageData;
    char* nextImage = (char*)DAT_TextureRenderCoreObject::instance.gmProcessedImageData;
    int drawY = DAT_RenderMap_DrawSomeY::instance + (DAT_00ed3154::instance - DAT_RenderMap_YOffset::instance) + 9;
    int height = DAT_GMImageHeaders::instance.imh[DAT_GmImageAddressToBeRendered::instance].height - 7;
    int skip = 0;
    int nextSkip = 160 - DAT_RenderMap_YOffset::instance;
    if ((int)DAT_00ed3170::instance <= 0) {
        return;
    }
    if (drawY < DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start) {
        skip = DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start - drawY;
        DAT_00ed3170::instance = DAT_00ed3170::instance - skip;
        drawY = DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start;
        nextSkip = nextSkip + skip;
        height = height - skip;
    }
    if ((int)(DAT_00ed3170::instance + drawY) >= DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.end) {
        DAT_00ed3170::instance = DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.end - drawY;
        // fixme: always adds 0, the original subtracts the already shortened row count
        height = height
            + (DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.end - DAT_00ed3170::instance - drawY);
    }
    // rows to bytes: tile objects are 15 dwords per row
    skip = skip * 60;
    nextSkip = nextSkip * 60;
    int firstRows;
    if (height <= 0) {
        firstRows = 0;
    } else if (height < (int)DAT_00ed3170::instance) {
        DAT_00ed3170::instance = DAT_00ed3170::instance - height;
        firstRows = height;
        nextSkip = nextSkip + height * 60;
    } else {
        firstRows = DAT_00ed3170::instance;
        DAT_00ed3170::instance = 0;
        skip = nextSkip;
    }
    if (DAT_00ed317c::instance == 3) {
        skip = skip - 480;
    }
    image = image + DAT_GMImageOffsets::instance[DAT_GmImageAddressToBeRendered::instance];
    nextImage = nextImage + DAT_GMImageOffsets::instance[DAT_00ed316c::instance];
    if (!DAT_TextureRenderCoreObject::instance.isZoom2) {
        // clang-format off
        __asm {
        mov esi, image
        mov eax, skip
        add esi, eax
        mov ecx, s_windowAndDirectDraw
        mov edi, dword ptr [ecx]WindowAndDirectDraw.surfacePointer_mapGame
        mov eax, s_drawSomeX
        mov eax, dword ptr [eax]
        add eax, eax
        add edi, eax
        mov eax, drawY
        mov edx, 0x1fb0
        mul edx
        add edi, eax
        mov edx, firstRows
        cmp edx, 0
        jle nrm_454359
nrm_4541d6:
        mov eax, s_blitModeUnk
        mov eax, dword ptr [eax]
        cmp eax, 1
        je nrm_45428f
        cmp eax, 2
        je nrm_4542e7
        cmp eax, 3
        je nrm_45433d
nrm_4541f6:
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
        jle nrm_454359
        jmp nrm_4541f6
nrm_45428f:
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
        jle nrm_454359
        jmp nrm_45428f
nrm_4542e7:
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
        jle nrm_454359
        jmp nrm_4542e7
nrm_45433d:
        mov ebx, dword ptr [esi + 0x1c]
        mov dword ptr [edi + 0xddec], ebx
        add esi, 0x3c
        add edi, 0x1fb0
        sub edx, 1
        cmp edx, 0
        jle nrm_454359
        jmp nrm_45433d
nrm_454359:
        mov eax, s_remainingRowsUnk
        cmp dword ptr [eax], 0
        jle nrm_45437f
        mov edx, dword ptr [eax]
        mov dword ptr [eax], 0
        mov esi, dword ptr nextImage
        mov eax, dword ptr nextSkip
        add esi, eax
        jmp nrm_4541d6
nrm_45437f:
        pop ebx
        }
        // clang-format on
        return;
    }
    // clang-format off
    __asm {
        mov esi, image
        mov eax, skip
        add esi, eax
        mov ecx, s_windowAndDirectDraw
        mov edi, dword ptr [ecx]WindowAndDirectDraw.surfacePointer_mapGame
        mov eax, s_drawSomeX
        mov eax, dword ptr [eax]
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
        jle zm_4545eb
zm_4543ba:
        mov eax, s_blitModeUnk
        mov eax, dword ptr [eax]
        cmp eax, 1
        je zm_4544ac
        cmp eax, 2
        je zm_454536
        cmp eax, 3
        je zm_4545b3
zm_4543da:
        mov eax, ecx
        and eax, 1
        cmp eax, 0
        jne zm_454448
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
        jle zm_4545eb
        jmp zm_4543da
zm_454448:
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
        jle zm_4545eb
        jmp zm_4543da
zm_4544ac:
        mov eax, ecx
        and eax, 1
        jne zm_4544f0
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
        jle zm_4545eb
        jmp zm_4544ac
zm_4544f0:
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
        jle zm_4545eb
        jmp zm_4544ac
zm_454536:
        mov eax, ecx
        and eax, 1
        jne zm_454574
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
        jle zm_4545eb
        jmp zm_454536
zm_454574:
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
        jle zm_4545eb
        jmp zm_454536
zm_4545b3:
        mov eax, ecx
        and eax, 1
        jne zm_4545ca
        add esi, 0x3c
        add ecx, 1
        sub edx, 1
        cmp edx, 0
        jle zm_4545eb
        jmp zm_4545b3
zm_4545ca:
        add edi, 0x1fb0
        mov ax, word ptr [esi + 0x1c]
        mov word ptr [edi + 0x5f1e], ax
        add esi, 0x3c
        add ecx, 1
        sub edx, 1
        cmp edx, 0
        jle zm_4545eb
        jmp zm_4545b3
zm_4545eb:
        mov eax, s_remainingRowsUnk
        cmp dword ptr [eax], 0
        jle zm_454611
        mov edx, dword ptr [eax]
        mov dword ptr [eax], 0
        mov esi, dword ptr nextImage
        mov eax, dword ptr nextSkip
        add esi, eax
        jmp zm_4543ba
zm_454611:
        pop ebx
    }
    // clang-format on
}

}
