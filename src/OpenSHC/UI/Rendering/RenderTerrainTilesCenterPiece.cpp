#include "../Rendering.func.hpp"

#include "OpenSHC/Globals/DAT_00ed3154.hpp"
#include "OpenSHC/Globals/DAT_GMImageOffsets.hpp"
#include "OpenSHC/Globals/DAT_GmImageAddressToBeRendered.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_DrawSomeX.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_DrawSomeY.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_YOffset.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    // Copies the 32x16 center piece of a terrain tile (512 bytes of RGB words, row by row) onto the map surface,
    // or every other pixel of it when zoomed out. The copies are handwritten assembly, transcribed from the binary.

    // One row of the 4056-pixel map surface, in bytes.
    enum { MAP_ROW = 4056 * 2 };

    // FUNCTION: STRONGHOLDCRUSADER 0x00452900
    void Rendering::RenderTerrainTilesCenterPiece()
    {
        // The asm below names these two globals, which inline asm can only do once C++ code has instantiated them;
        // sizeof does that without generating any code.
        (void)sizeof(DAT_WindowAndDirectDraw::instance);
        (void)sizeof(DAT_RenderMap_DrawSomeX::instance);
        int const drawY
            = DAT_RenderMap_DrawSomeY::instance + (DAT_00ed3154::instance - DAT_RenderMap_YOffset::instance);
        if (drawY >= DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.end
            || drawY < DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start) {
            return;
        }
        char* const source = DAT_GMImageOffsets::instance[DAT_GmImageAddressToBeRendered::instance]
            + (char*)DAT_TextureRenderCoreObject::instance.gmProcessedImageData;
        if (!DAT_TextureRenderCoreObject::instance.isZoom2) {
            // clang-format off
            __asm {
                mov esi, source
                mov edi, DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame
                mov eax, DAT_RenderMap_DrawSomeX::instance
                add eax, eax
                add edi, eax
                mov eax, drawY
                mov edx, MAP_ROW
                mul edx
                add edi, eax
                mov DAT_WindowAndDirectDraw::instance.unknownSpecificPointer, edi
                mov eax, dword ptr [esi]
                mov ebx, dword ptr [esi + 4]
                mov ecx, dword ptr [esi + 8]
                mov edx, dword ptr [esi + 12]
                mov dword ptr [edi + 28], eax
                mov dword ptr [edi + MAP_ROW + 24], ebx
                mov dword ptr [edi + MAP_ROW + 28], ecx
                mov dword ptr [edi + MAP_ROW + 32], edx
                mov eax, dword ptr [esi + 16]
                mov ebx, dword ptr [esi + 20]
                mov ecx, dword ptr [esi + 24]
                mov edx, dword ptr [esi + 28]
                mov dword ptr [edi + 2 * MAP_ROW + 20], eax
                mov dword ptr [edi + 2 * MAP_ROW + 24], ebx
                mov dword ptr [edi + 2 * MAP_ROW + 28], ecx
                mov dword ptr [edi + 2 * MAP_ROW + 32], edx
                mov eax, dword ptr [esi + 32]
                mov ebx, dword ptr [esi + 36]
                mov ecx, dword ptr [esi + 40]
                mov edx, dword ptr [esi + 44]
                mov dword ptr [edi + 2 * MAP_ROW + 36], eax
                mov dword ptr [edi + 3 * MAP_ROW + 16], ebx
                mov dword ptr [edi + 3 * MAP_ROW + 20], ecx
                mov dword ptr [edi + 3 * MAP_ROW + 24], edx
                mov eax, dword ptr [esi + 48]
                mov ebx, dword ptr [esi + 52]
                mov ecx, dword ptr [esi + 56]
                mov edx, dword ptr [esi + 60]
                mov dword ptr [edi + 3 * MAP_ROW + 28], eax
                mov dword ptr [edi + 3 * MAP_ROW + 32], ebx
                mov dword ptr [edi + 3 * MAP_ROW + 36], ecx
                mov dword ptr [edi + 3 * MAP_ROW + 40], edx
                mov eax, dword ptr [esi + 64]
                mov ebx, dword ptr [esi + 68]
                mov ecx, dword ptr [esi + 72]
                mov edx, dword ptr [esi + 76]
                mov dword ptr [edi + 4 * MAP_ROW + 12], eax
                mov dword ptr [edi + 4 * MAP_ROW + 16], ebx
                mov dword ptr [edi + 4 * MAP_ROW + 20], ecx
                mov dword ptr [edi + 4 * MAP_ROW + 24], edx
                mov eax, dword ptr [esi + 80]
                mov ebx, dword ptr [esi + 84]
                mov ecx, dword ptr [esi + 88]
                mov edx, dword ptr [esi + 92]
                mov dword ptr [edi + 4 * MAP_ROW + 28], eax
                mov dword ptr [edi + 4 * MAP_ROW + 32], ebx
                mov dword ptr [edi + 4 * MAP_ROW + 36], ecx
                mov dword ptr [edi + 4 * MAP_ROW + 40], edx
                mov eax, dword ptr [esi + 96]
                mov ebx, dword ptr [esi + 100]
                mov ecx, dword ptr [esi + 104]
                mov edx, dword ptr [esi + 108]
                mov dword ptr [edi + 4 * MAP_ROW + 44], eax
                mov dword ptr [edi + 5 * MAP_ROW + 8], ebx
                mov dword ptr [edi + 5 * MAP_ROW + 12], ecx
                mov dword ptr [edi + 5 * MAP_ROW + 16], edx
                mov eax, dword ptr [esi + 112]
                mov ebx, dword ptr [esi + 116]
                mov ecx, dword ptr [esi + 120]
                mov edx, dword ptr [esi + 124]
                mov dword ptr [edi + 5 * MAP_ROW + 20], eax
                mov dword ptr [edi + 5 * MAP_ROW + 24], ebx
                mov dword ptr [edi + 5 * MAP_ROW + 28], ecx
                mov dword ptr [edi + 5 * MAP_ROW + 32], edx
                mov eax, dword ptr [esi + 128]
                mov ebx, dword ptr [esi + 132]
                mov ecx, dword ptr [esi + 136]
                mov edx, dword ptr [esi + 140]
                mov dword ptr [edi + 5 * MAP_ROW + 36], eax
                mov dword ptr [edi + 5 * MAP_ROW + 40], ebx
                mov dword ptr [edi + 5 * MAP_ROW + 44], ecx
                mov dword ptr [edi + 5 * MAP_ROW + 48], edx
                mov eax, dword ptr [esi + 144]
                mov ebx, dword ptr [esi + 148]
                mov ecx, dword ptr [esi + 152]
                mov edx, dword ptr [esi + 156]
                mov dword ptr [edi + 6 * MAP_ROW + 4], eax
                mov dword ptr [edi + 6 * MAP_ROW + 8], ebx
                mov dword ptr [edi + 6 * MAP_ROW + 12], ecx
                mov dword ptr [edi + 6 * MAP_ROW + 16], edx
                mov eax, dword ptr [esi + 160]
                mov ebx, dword ptr [esi + 164]
                mov ecx, dword ptr [esi + 168]
                mov edx, dword ptr [esi + 172]
                mov dword ptr [edi + 6 * MAP_ROW + 20], eax
                mov dword ptr [edi + 6 * MAP_ROW + 24], ebx
                mov dword ptr [edi + 6 * MAP_ROW + 28], ecx
                mov dword ptr [edi + 6 * MAP_ROW + 32], edx
                mov eax, dword ptr [esi + 176]
                mov ebx, dword ptr [esi + 180]
                mov ecx, dword ptr [esi + 184]
                mov edx, dword ptr [esi + 188]
                mov dword ptr [edi + 6 * MAP_ROW + 36], eax
                mov dword ptr [edi + 6 * MAP_ROW + 40], ebx
                mov dword ptr [edi + 6 * MAP_ROW + 44], ecx
                mov dword ptr [edi + 6 * MAP_ROW + 48], edx
                mov eax, dword ptr [esi + 192]
                mov ebx, dword ptr [esi + 196]
                mov ecx, dword ptr [esi + 200]
                mov edx, dword ptr [esi + 204]
                mov dword ptr [edi + 6 * MAP_ROW + 52], eax
                mov dword ptr [edi + 7 * MAP_ROW], ebx
                mov dword ptr [edi + 7 * MAP_ROW + 4], ecx
                mov dword ptr [edi + 7 * MAP_ROW + 8], edx
                mov eax, dword ptr [esi + 208]
                mov ebx, dword ptr [esi + 212]
                mov ecx, dword ptr [esi + 216]
                mov edx, dword ptr [esi + 220]
                mov dword ptr [edi + 7 * MAP_ROW + 12], eax
                mov dword ptr [edi + 7 * MAP_ROW + 16], ebx
                mov dword ptr [edi + 7 * MAP_ROW + 20], ecx
                mov dword ptr [edi + 7 * MAP_ROW + 24], edx
                mov eax, dword ptr [esi + 224]
                mov ebx, dword ptr [esi + 228]
                mov ecx, dword ptr [esi + 232]
                mov edx, dword ptr [esi + 236]
                mov dword ptr [edi + 7 * MAP_ROW + 28], eax
                mov dword ptr [edi + 7 * MAP_ROW + 32], ebx
                mov dword ptr [edi + 7 * MAP_ROW + 36], ecx
                mov dword ptr [edi + 7 * MAP_ROW + 40], edx
                mov eax, dword ptr [esi + 240]
                mov ebx, dword ptr [esi + 244]
                mov ecx, dword ptr [esi + 248]
                mov edx, dword ptr [esi + 252]
                mov dword ptr [edi + 7 * MAP_ROW + 44], eax
                mov dword ptr [edi + 7 * MAP_ROW + 48], ebx
                mov dword ptr [edi + 7 * MAP_ROW + 52], ecx
                mov dword ptr [edi + 7 * MAP_ROW + 56], edx
                mov eax, dword ptr [esi + 256]
                mov ebx, dword ptr [esi + 260]
                mov ecx, dword ptr [esi + 264]
                mov edx, dword ptr [esi + 268]
                mov dword ptr [edi + 8 * MAP_ROW], eax
                mov dword ptr [edi + 8 * MAP_ROW + 4], ebx
                mov dword ptr [edi + 8 * MAP_ROW + 8], ecx
                mov dword ptr [edi + 8 * MAP_ROW + 12], edx
                mov eax, dword ptr [esi + 272]
                mov ebx, dword ptr [esi + 276]
                mov ecx, dword ptr [esi + 280]
                mov edx, dword ptr [esi + 284]
                mov dword ptr [edi + 8 * MAP_ROW + 16], eax
                mov dword ptr [edi + 8 * MAP_ROW + 20], ebx
                mov dword ptr [edi + 8 * MAP_ROW + 24], ecx
                mov dword ptr [edi + 8 * MAP_ROW + 28], edx
                mov eax, dword ptr [esi + 288]
                mov ebx, dword ptr [esi + 292]
                mov ecx, dword ptr [esi + 296]
                mov edx, dword ptr [esi + 300]
                mov dword ptr [edi + 8 * MAP_ROW + 32], eax
                mov dword ptr [edi + 8 * MAP_ROW + 36], ebx
                mov dword ptr [edi + 8 * MAP_ROW + 40], ecx
                mov dword ptr [edi + 8 * MAP_ROW + 44], edx
                mov eax, dword ptr [esi + 304]
                mov ebx, dword ptr [esi + 308]
                mov ecx, dword ptr [esi + 312]
                mov edx, dword ptr [esi + 316]
                mov dword ptr [edi + 8 * MAP_ROW + 48], eax
                mov dword ptr [edi + 8 * MAP_ROW + 52], ebx
                mov dword ptr [edi + 8 * MAP_ROW + 56], ecx
                mov dword ptr [edi + 9 * MAP_ROW + 4], edx
                mov eax, dword ptr [esi + 320]
                mov ebx, dword ptr [esi + 324]
                mov ecx, dword ptr [esi + 328]
                mov edx, dword ptr [esi + 332]
                mov dword ptr [edi + 9 * MAP_ROW + 8], eax
                mov dword ptr [edi + 9 * MAP_ROW + 12], ebx
                mov dword ptr [edi + 9 * MAP_ROW + 16], ecx
                mov dword ptr [edi + 9 * MAP_ROW + 20], edx
                mov eax, dword ptr [esi + 336]
                mov ebx, dword ptr [esi + 340]
                mov ecx, dword ptr [esi + 344]
                mov edx, dword ptr [esi + 348]
                mov dword ptr [edi + 9 * MAP_ROW + 24], eax
                mov dword ptr [edi + 9 * MAP_ROW + 28], ebx
                mov dword ptr [edi + 9 * MAP_ROW + 32], ecx
                mov dword ptr [edi + 9 * MAP_ROW + 36], edx
                mov eax, dword ptr [esi + 352]
                mov ebx, dword ptr [esi + 356]
                mov ecx, dword ptr [esi + 360]
                mov edx, dword ptr [esi + 364]
                mov dword ptr [edi + 9 * MAP_ROW + 40], eax
                mov dword ptr [edi + 9 * MAP_ROW + 44], ebx
                mov dword ptr [edi + 9 * MAP_ROW + 48], ecx
                mov dword ptr [edi + 9 * MAP_ROW + 52], edx
                mov eax, dword ptr [esi + 368]
                mov ebx, dword ptr [esi + 372]
                mov ecx, dword ptr [esi + 376]
                mov edx, dword ptr [esi + 380]
                mov dword ptr [edi + 10 * MAP_ROW + 8], eax
                mov dword ptr [edi + 10 * MAP_ROW + 12], ebx
                mov dword ptr [edi + 10 * MAP_ROW + 16], ecx
                mov dword ptr [edi + 10 * MAP_ROW + 20], edx
                mov eax, dword ptr [esi + 384]
                mov ebx, dword ptr [esi + 388]
                mov ecx, dword ptr [esi + 392]
                mov edx, dword ptr [esi + 396]
                mov dword ptr [edi + 10 * MAP_ROW + 24], eax
                mov dword ptr [edi + 10 * MAP_ROW + 28], ebx
                mov dword ptr [edi + 10 * MAP_ROW + 32], ecx
                mov dword ptr [edi + 10 * MAP_ROW + 36], edx
                mov eax, dword ptr [esi + 400]
                mov ebx, dword ptr [esi + 404]
                mov ecx, dword ptr [esi + 408]
                mov edx, dword ptr [esi + 412]
                mov dword ptr [edi + 10 * MAP_ROW + 40], eax
                mov dword ptr [edi + 10 * MAP_ROW + 44], ebx
                mov dword ptr [edi + 10 * MAP_ROW + 48], ecx
                mov dword ptr [edi + 11 * MAP_ROW + 12], edx
                mov eax, dword ptr [esi + 416]
                mov ebx, dword ptr [esi + 420]
                mov ecx, dword ptr [esi + 424]
                mov edx, dword ptr [esi + 428]
                mov dword ptr [edi + 11 * MAP_ROW + 16], eax
                mov dword ptr [edi + 11 * MAP_ROW + 20], ebx
                mov dword ptr [edi + 11 * MAP_ROW + 24], ecx
                mov dword ptr [edi + 11 * MAP_ROW + 28], edx
                mov eax, dword ptr [esi + 432]
                mov ebx, dword ptr [esi + 436]
                mov ecx, dword ptr [esi + 440]
                mov edx, dword ptr [esi + 444]
                mov dword ptr [edi + 11 * MAP_ROW + 32], eax
                mov dword ptr [edi + 11 * MAP_ROW + 36], ebx
                mov dword ptr [edi + 11 * MAP_ROW + 40], ecx
                mov dword ptr [edi + 11 * MAP_ROW + 44], edx
                mov eax, dword ptr [esi + 448]
                mov ebx, dword ptr [esi + 452]
                mov ecx, dword ptr [esi + 456]
                mov edx, dword ptr [esi + 460]
                mov dword ptr [edi + 12 * MAP_ROW + 16], eax
                mov dword ptr [edi + 12 * MAP_ROW + 20], ebx
                mov dword ptr [edi + 12 * MAP_ROW + 24], ecx
                mov dword ptr [edi + 12 * MAP_ROW + 28], edx
                mov eax, dword ptr [esi + 464]
                mov ebx, dword ptr [esi + 468]
                mov ecx, dword ptr [esi + 472]
                mov edx, dword ptr [esi + 476]
                mov dword ptr [edi + 12 * MAP_ROW + 32], eax
                mov dword ptr [edi + 12 * MAP_ROW + 36], ebx
                mov dword ptr [edi + 12 * MAP_ROW + 40], ecx
                mov dword ptr [edi + 13 * MAP_ROW + 20], edx
                mov eax, dword ptr [esi + 480]
                mov ebx, dword ptr [esi + 484]
                mov ecx, dword ptr [esi + 488]
                mov edx, dword ptr [esi + 492]
                mov dword ptr [edi + 13 * MAP_ROW + 24], eax
                mov dword ptr [edi + 13 * MAP_ROW + 28], ebx
                mov dword ptr [edi + 13 * MAP_ROW + 32], ecx
                mov dword ptr [edi + 13 * MAP_ROW + 36], edx
                mov eax, dword ptr [esi + 496]
                mov ebx, dword ptr [esi + 500]
                mov ecx, dword ptr [esi + 504]
                mov edx, dword ptr [esi + 508]
                mov dword ptr [edi + 14 * MAP_ROW + 24], eax
                mov dword ptr [edi + 14 * MAP_ROW + 28], ebx
                mov dword ptr [edi + 14 * MAP_ROW + 32], ecx
                mov dword ptr [edi + 15 * MAP_ROW + 28], edx
            }
            // clang-format on
            return;
        }
        // clang-format off
        __asm {
            mov esi, source
            mov edi, DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame
            mov eax, DAT_RenderMap_DrawSomeX::instance
            and eax, 0xfffffffe
            add edi, eax
            mov eax, drawY
            mov ebx, eax
            shr eax, 1
            mov edx, MAP_ROW
            mul edx
            add edi, eax
            mov DAT_WindowAndDirectDraw::instance.unknownSpecificPointer, edi
            and ebx, 1
            cmp ebx, 0
            jne odd_row
            mov ax, word ptr [esi]
            mov word ptr [edi + 14], ax
            mov ax, word ptr [esi + 16]
            mov bx, word ptr [esi + 20]
            mov cx, word ptr [esi + 24]
            mov dx, word ptr [esi + 28]
            mov word ptr [edi + MAP_ROW + 10], ax
            mov word ptr [edi + MAP_ROW + 12], bx
            mov word ptr [edi + MAP_ROW + 14], cx
            mov word ptr [edi + MAP_ROW + 16], dx
            mov ax, word ptr [esi + 32]
            mov word ptr [edi + MAP_ROW + 18], ax
            mov ax, word ptr [esi + 64]
            mov bx, word ptr [esi + 68]
            mov cx, word ptr [esi + 72]
            mov dx, word ptr [esi + 76]
            mov word ptr [edi + 2 * MAP_ROW + 6], ax
            mov word ptr [edi + 2 * MAP_ROW + 8], bx
            mov word ptr [edi + 2 * MAP_ROW + 10], cx
            mov word ptr [edi + 2 * MAP_ROW + 12], dx
            mov ax, word ptr [esi + 80]
            mov bx, word ptr [esi + 84]
            mov cx, word ptr [esi + 88]
            mov dx, word ptr [esi + 92]
            mov word ptr [edi + 2 * MAP_ROW + 14], ax
            mov word ptr [edi + 2 * MAP_ROW + 16], bx
            mov word ptr [edi + 2 * MAP_ROW + 18], cx
            mov word ptr [edi + 2 * MAP_ROW + 20], dx
            mov ax, word ptr [esi + 96]
            mov word ptr [edi + 2 * MAP_ROW + 22], ax
            mov ax, word ptr [esi + 144]
            mov bx, word ptr [esi + 148]
            mov cx, word ptr [esi + 152]
            mov dx, word ptr [esi + 156]
            mov word ptr [edi + 3 * MAP_ROW + 2], ax
            mov word ptr [edi + 3 * MAP_ROW + 4], bx
            mov word ptr [edi + 3 * MAP_ROW + 6], cx
            mov word ptr [edi + 3 * MAP_ROW + 8], dx
            mov ax, word ptr [esi + 160]
            mov bx, word ptr [esi + 164]
            mov cx, word ptr [esi + 168]
            mov dx, word ptr [esi + 172]
            mov word ptr [edi + 3 * MAP_ROW + 10], ax
            mov word ptr [edi + 3 * MAP_ROW + 12], bx
            mov word ptr [edi + 3 * MAP_ROW + 14], cx
            mov word ptr [edi + 3 * MAP_ROW + 16], dx
            mov ax, word ptr [esi + 176]
            mov bx, word ptr [esi + 180]
            mov cx, word ptr [esi + 184]
            mov dx, word ptr [esi + 188]
            mov word ptr [edi + 3 * MAP_ROW + 18], ax
            mov word ptr [edi + 3 * MAP_ROW + 20], bx
            mov word ptr [edi + 3 * MAP_ROW + 22], cx
            mov word ptr [edi + 3 * MAP_ROW + 24], dx
            mov ax, word ptr [esi + 192]
            mov word ptr [edi + 3 * MAP_ROW + 26], ax
            mov ax, word ptr [esi + 256]
            mov bx, word ptr [esi + 260]
            mov cx, word ptr [esi + 264]
            mov dx, word ptr [esi + 268]
            mov word ptr [edi + 4 * MAP_ROW], ax
            mov word ptr [edi + 4 * MAP_ROW + 2], bx
            mov word ptr [edi + 4 * MAP_ROW + 4], cx
            mov word ptr [edi + 4 * MAP_ROW + 6], dx
            mov ax, word ptr [esi + 272]
            mov bx, word ptr [esi + 276]
            mov cx, word ptr [esi + 280]
            mov dx, word ptr [esi + 284]
            mov word ptr [edi + 4 * MAP_ROW + 8], ax
            mov word ptr [edi + 4 * MAP_ROW + 10], bx
            mov word ptr [edi + 4 * MAP_ROW + 12], cx
            mov word ptr [edi + 4 * MAP_ROW + 14], dx
            mov ax, word ptr [esi + 288]
            mov bx, word ptr [esi + 292]
            mov cx, word ptr [esi + 296]
            mov dx, word ptr [esi + 300]
            mov word ptr [edi + 4 * MAP_ROW + 16], ax
            mov word ptr [edi + 4 * MAP_ROW + 18], bx
            mov word ptr [edi + 4 * MAP_ROW + 20], cx
            mov word ptr [edi + 4 * MAP_ROW + 22], dx
            mov ax, word ptr [esi + 304]
            mov bx, word ptr [esi + 308]
            mov cx, word ptr [esi + 312]
            mov word ptr [edi + 4 * MAP_ROW + 24], ax
            mov word ptr [edi + 4 * MAP_ROW + 26], bx
            mov word ptr [edi + 4 * MAP_ROW + 28], cx
            mov ax, word ptr [esi + 368]
            mov bx, word ptr [esi + 372]
            mov cx, word ptr [esi + 376]
            mov dx, word ptr [esi + 380]
            mov word ptr [edi + 5 * MAP_ROW + 4], ax
            mov word ptr [edi + 5 * MAP_ROW + 6], bx
            mov word ptr [edi + 5 * MAP_ROW + 8], cx
            mov word ptr [edi + 5 * MAP_ROW + 10], dx
            mov ax, word ptr [esi + 384]
            mov bx, word ptr [esi + 388]
            mov cx, word ptr [esi + 392]
            mov dx, word ptr [esi + 396]
            mov word ptr [edi + 5 * MAP_ROW + 12], ax
            mov word ptr [edi + 5 * MAP_ROW + 14], bx
            mov word ptr [edi + 5 * MAP_ROW + 16], cx
            mov word ptr [edi + 5 * MAP_ROW + 18], dx
            mov ax, word ptr [esi + 400]
            mov bx, word ptr [esi + 404]
            mov cx, word ptr [esi + 408]
            mov word ptr [edi + 5 * MAP_ROW + 20], ax
            mov word ptr [edi + 5 * MAP_ROW + 22], bx
            mov word ptr [edi + 5 * MAP_ROW + 24], cx
            mov ax, word ptr [esi + 448]
            mov bx, word ptr [esi + 452]
            mov cx, word ptr [esi + 456]
            mov dx, word ptr [esi + 460]
            mov word ptr [edi + 6 * MAP_ROW + 8], ax
            mov word ptr [edi + 6 * MAP_ROW + 10], bx
            mov word ptr [edi + 6 * MAP_ROW + 12], cx
            mov word ptr [edi + 6 * MAP_ROW + 14], dx
            mov ax, word ptr [esi + 464]
            mov bx, word ptr [esi + 468]
            mov cx, word ptr [esi + 472]
            mov word ptr [edi + 6 * MAP_ROW + 16], ax
            mov word ptr [edi + 6 * MAP_ROW + 18], bx
            mov word ptr [edi + 6 * MAP_ROW + 20], cx
            mov ax, word ptr [esi + 496]
            mov bx, word ptr [esi + 500]
            mov cx, word ptr [esi + 504]
            mov word ptr [edi + 7 * MAP_ROW + 12], ax
            mov word ptr [edi + 7 * MAP_ROW + 14], bx
            mov word ptr [edi + 7 * MAP_ROW + 16], cx
            jmp done
        odd_row:
            mov bx, word ptr [esi + 4]
            mov cx, word ptr [esi + 8]
            mov dx, word ptr [esi + 12]
            mov word ptr [edi + MAP_ROW + 12], bx
            mov word ptr [edi + MAP_ROW + 14], cx
            mov word ptr [edi + MAP_ROW + 16], dx
            mov bx, word ptr [esi + 36]
            mov cx, word ptr [esi + 40]
            mov dx, word ptr [esi + 44]
            mov word ptr [edi + 2 * MAP_ROW + 8], bx
            mov word ptr [edi + 2 * MAP_ROW + 10], cx
            mov word ptr [edi + 2 * MAP_ROW + 12], dx
            mov ax, word ptr [esi + 48]
            mov bx, word ptr [esi + 52]
            mov cx, word ptr [esi + 56]
            mov dx, word ptr [esi + 60]
            mov word ptr [edi + 2 * MAP_ROW + 14], ax
            mov word ptr [edi + 2 * MAP_ROW + 16], bx
            mov word ptr [edi + 2 * MAP_ROW + 18], cx
            mov word ptr [edi + 2 * MAP_ROW + 20], dx
            mov bx, word ptr [esi + 100]
            mov cx, word ptr [esi + 104]
            mov dx, word ptr [esi + 108]
            mov word ptr [edi + 3 * MAP_ROW + 4], bx
            mov word ptr [edi + 3 * MAP_ROW + 6], cx
            mov word ptr [edi + 3 * MAP_ROW + 8], dx
            mov ax, word ptr [esi + 112]
            mov bx, word ptr [esi + 116]
            mov cx, word ptr [esi + 120]
            mov dx, word ptr [esi + 124]
            mov word ptr [edi + 3 * MAP_ROW + 10], ax
            mov word ptr [edi + 3 * MAP_ROW + 12], bx
            mov word ptr [edi + 3 * MAP_ROW + 14], cx
            mov word ptr [edi + 3 * MAP_ROW + 16], dx
            mov ax, word ptr [esi + 128]
            mov bx, word ptr [esi + 132]
            mov cx, word ptr [esi + 136]
            mov dx, word ptr [esi + 140]
            mov word ptr [edi + 3 * MAP_ROW + 18], ax
            mov word ptr [edi + 3 * MAP_ROW + 20], bx
            mov word ptr [edi + 3 * MAP_ROW + 22], cx
            mov word ptr [edi + 3 * MAP_ROW + 24], dx
            mov bx, word ptr [esi + 196]
            mov cx, word ptr [esi + 200]
            mov dx, word ptr [esi + 204]
            mov word ptr [edi + 4 * MAP_ROW], bx
            mov word ptr [edi + 4 * MAP_ROW + 2], cx
            mov word ptr [edi + 4 * MAP_ROW + 4], dx
            mov ax, word ptr [esi + 208]
            mov bx, word ptr [esi + 212]
            mov cx, word ptr [esi + 216]
            mov dx, word ptr [esi + 220]
            mov word ptr [edi + 4 * MAP_ROW + 6], ax
            mov word ptr [edi + 4 * MAP_ROW + 8], bx
            mov word ptr [edi + 4 * MAP_ROW + 10], cx
            mov word ptr [edi + 4 * MAP_ROW + 12], dx
            mov ax, word ptr [esi + 224]
            mov bx, word ptr [esi + 228]
            mov cx, word ptr [esi + 232]
            mov dx, word ptr [esi + 236]
            mov word ptr [edi + 4 * MAP_ROW + 14], ax
            mov word ptr [edi + 4 * MAP_ROW + 16], bx
            mov word ptr [edi + 4 * MAP_ROW + 18], cx
            mov word ptr [edi + 4 * MAP_ROW + 20], dx
            mov ax, word ptr [esi + 240]
            mov bx, word ptr [esi + 244]
            mov cx, word ptr [esi + 248]
            mov dx, word ptr [esi + 252]
            mov word ptr [edi + 4 * MAP_ROW + 22], ax
            mov word ptr [edi + 4 * MAP_ROW + 24], bx
            mov word ptr [edi + 4 * MAP_ROW + 26], cx
            mov word ptr [edi + 4 * MAP_ROW + 28], dx
            mov dx, word ptr [esi + 316]
            mov word ptr [edi + 5 * MAP_ROW + 2], dx
            mov ax, word ptr [esi + 320]
            mov bx, word ptr [esi + 324]
            mov cx, word ptr [esi + 328]
            mov dx, word ptr [esi + 332]
            mov word ptr [edi + 5 * MAP_ROW + 4], ax
            mov word ptr [edi + 5 * MAP_ROW + 6], bx
            mov word ptr [edi + 5 * MAP_ROW + 8], cx
            mov word ptr [edi + 5 * MAP_ROW + 10], dx
            mov ax, word ptr [esi + 336]
            mov bx, word ptr [esi + 340]
            mov cx, word ptr [esi + 344]
            mov dx, word ptr [esi + 348]
            mov word ptr [edi + 5 * MAP_ROW + 12], ax
            mov word ptr [edi + 5 * MAP_ROW + 14], bx
            mov word ptr [edi + 5 * MAP_ROW + 16], cx
            mov word ptr [edi + 5 * MAP_ROW + 18], dx
            mov ax, word ptr [esi + 352]
            mov bx, word ptr [esi + 356]
            mov cx, word ptr [esi + 360]
            mov dx, word ptr [esi + 364]
            mov word ptr [edi + 5 * MAP_ROW + 20], ax
            mov word ptr [edi + 5 * MAP_ROW + 22], bx
            mov word ptr [edi + 5 * MAP_ROW + 24], cx
            mov word ptr [edi + 5 * MAP_ROW + 26], dx
            mov dx, word ptr [esi + 412]
            mov word ptr [edi + 6 * MAP_ROW + 6], dx
            mov ax, word ptr [esi + 416]
            mov bx, word ptr [esi + 420]
            mov cx, word ptr [esi + 424]
            mov dx, word ptr [esi + 428]
            mov word ptr [edi + 6 * MAP_ROW + 8], ax
            mov word ptr [edi + 6 * MAP_ROW + 10], bx
            mov word ptr [edi + 6 * MAP_ROW + 12], cx
            mov word ptr [edi + 6 * MAP_ROW + 14], dx
            mov ax, word ptr [esi + 432]
            mov bx, word ptr [esi + 436]
            mov cx, word ptr [esi + 440]
            mov dx, word ptr [esi + 444]
            mov word ptr [edi + 6 * MAP_ROW + 16], ax
            mov word ptr [edi + 6 * MAP_ROW + 18], bx
            mov word ptr [edi + 6 * MAP_ROW + 20], cx
            mov word ptr [edi + 6 * MAP_ROW + 22], dx
            mov dx, word ptr [esi + 476]
            mov word ptr [edi + 7 * MAP_ROW + 10], dx
            mov ax, word ptr [esi + 480]
            mov bx, word ptr [esi + 484]
            mov cx, word ptr [esi + 488]
            mov dx, word ptr [esi + 492]
            mov word ptr [edi + 7 * MAP_ROW + 12], ax
            mov word ptr [edi + 7 * MAP_ROW + 14], bx
            mov word ptr [edi + 7 * MAP_ROW + 16], cx
            mov word ptr [edi + 7 * MAP_ROW + 18], dx
            mov dx, word ptr [esi + 508]
            mov word ptr [edi + 8 * MAP_ROW + 14], dx
        done:
        }
        // clang-format on
    }

}
}
