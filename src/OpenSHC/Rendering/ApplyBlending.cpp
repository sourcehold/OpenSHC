#include "../Rendering.func.hpp"

#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"

#include "OpenSHC/Globals/DAT_00ed3154.hpp"
#include "OpenSHC/Globals/DAT_BlendFilterArrays.hpp"
#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GMImageOffsets.hpp"
#include "OpenSHC/Globals/DAT_GmImageAddressToBeRendered.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_DrawSomeX.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_DrawSomeY.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_YOffset.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {

// Blends the tile being drawn into the map surface, pixel by pixel: every colour component of the tile and of the
// surface under it is looked up in DAT_BlendFilterArrays (scaled by (32 - blendLevel) / 32 and blendLevel / 32) and
// the two results are added. The offset tables say where each pixel of the diamond-shaped tile lands on the
// 4056-pixel-wide map surface; zoomed out, every other row and column is used.
// The pixel loops are handwritten assembly in the original, transcribed here from the binary.

// One row of the 4056-pixel map surface, in bytes.
enum { MAP_ROW = 4056 * 2 };

// FUNCTION: STRONGHOLDCRUSADER 0x00453600
void Rendering::ApplyBlending(int blendLevel)
{
    // The asm below names DAT_RenderMap_DrawSomeX, which inline asm can only do once C++ code has instantiated it;
    // sizeof does that without generating any code.
    (void)sizeof(DAT_RenderMap_DrawSomeX::instance);
    // Declared up front because both branches assign them; the asm reads them by frame slot.
    int* offsets;
    short* destinationTable;
    short* sourceTable;
    char* source = (char*)DAT_TextureRenderCoreObject::instance.gmProcessedImageData;
    if (!DAT_TextureRenderCoreObject::instance.isZoom2) {
        offsets = DAT_BlendingDefinedData::instance.field_0x27fc;
        int const drawY
            = DAT_RenderMap_DrawSomeY::instance + (DAT_00ed3154::instance - DAT_RenderMap_YOffset::instance);
        if (drawY < DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start
            || drawY >= DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.end) {
            return;
        }
        source += DAT_GMImageOffsets::instance[DAT_GmImageAddressToBeRendered::instance];
        // Built on first use: the full-strength table's last entry is 0 until then.
        if (DAT_BlendFilterArrays::instance[32][31][0] == 0) {
            MACRO_CALL(UI::Rendering_Func::InitBlendFilterArraysUnk)();
        }
        destinationTable = DAT_BlendFilterArrays::instance[blendLevel][0];
        sourceTable = DAT_BlendFilterArrays::instance[32 - blendLevel][0];
        if (DAT_WindowAndDirectDraw::instance.colorBitMode == Rendering::RGB_555) {
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
                mov ecx, 256
            pixel_555:
                mov ax, word ptr [esi]
                mov edx, dword ptr sourceTable
                mov ebx, 0
                mov bx, ax
                and bx, 0x1f
                mov bx, word ptr [edx + ebx*8]
                and ax, 0xffe0
                or ax, bx
                mov bx, ax
                shr bx, 5
                and bx, 0x1f
                mov bx, word ptr [edx + ebx*8 + 2]
                and ax, 0xfc1f
                or ax, bx
                mov bx, ax
                shr bx, 10
                and bx, 0x1f
                mov bx, word ptr [edx + ebx*8 + 4]
                and ax, 0x3ff
                or ax, bx
                push ax
                mov edx, dword ptr offsets
                mov edx, dword ptr [edx]
                mov ax, word ptr [edi + edx]
                mov edx, dword ptr destinationTable
                mov ebx, 0
                mov bx, ax
                and bx, 0x1f
                mov bx, word ptr [edx + ebx*8]
                and ax, 0xffe0
                or ax, bx
                mov bx, ax
                shr bx, 5
                and bx, 0x1f
                mov bx, word ptr [edx + ebx*8 + 2]
                and ax, 0xfc1f
                or ax, bx
                mov bx, ax
                shr bx, 10
                and bx, 0x1f
                mov bx, word ptr [edx + ebx*8 + 4]
                and ax, 0x83ff
                or ax, bx
                mov edx, dword ptr offsets
                mov edx, dword ptr [edx]
                mov word ptr [edi + edx], ax
                pop ax
                add word ptr [edi + edx], ax
                add esi, 2
                add dword ptr offsets, 4
                sub cx, 1
                jne pixel_555
            }
            // clang-format on
            return;
        }
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
            mov ecx, 256
        pixel_565:
            mov ax, word ptr [esi]
            mov edx, dword ptr sourceTable
            mov ebx, 0
            mov bx, ax
            and bx, 0x1f
            mov bx, word ptr [edx + ebx*8]
            and ax, 0xffe0
            or ax, bx
            mov bx, ax
            shr bx, 5
            and bx, 0x3f
            mov bx, word ptr [edx + ebx*8 + 2]
            and ax, 0xf81f
            or ax, bx
            mov bx, ax
            shr bx, 11
            and bx, 0x1f
            mov bx, word ptr [edx + ebx*8 + 4]
            and ax, 0x7ff
            or ax, bx
            push ax
            mov edx, dword ptr offsets
            mov edx, dword ptr [edx]
            mov ax, word ptr [edi + edx]
            mov edx, dword ptr destinationTable
            mov ebx, 0
            mov bx, ax
            and bx, 0x1f
            mov bx, word ptr [edx + ebx*8]
            and ax, 0xffe0
            or ax, bx
            mov bx, ax
            shr bx, 5
            and bx, 0x3f
            mov bx, word ptr [edx + ebx*8 + 2]
            and ax, 0xf81f
            or ax, bx
            mov bx, ax
            shr bx, 11
            and bx, 0x1f
            mov bx, word ptr [edx + ebx*8 + 4]
            and ax, 0x7ff
            or ax, bx
            mov edx, dword ptr offsets
            mov edx, dword ptr [edx]
            mov word ptr [edi + edx], ax
            pop ax
            add word ptr [edi + edx], ax
            add esi, 2
            add dword ptr offsets, 4
            sub cx, 1
            jne pixel_565
        }
        // clang-format on
        return;
    }

    offsets = DAT_BlendingDefinedData::instance.field_0x2dfc;
    int* evenRowOffsets = DAT_BlendingDefinedData::instance.field_0x2bfc;
    int const drawY = DAT_RenderMap_DrawSomeY::instance + (DAT_00ed3154::instance - DAT_RenderMap_YOffset::instance);
    if (drawY < DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start
        || drawY >= DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.end) {
        return;
    }
    source += DAT_GMImageOffsets::instance[DAT_GmImageAddressToBeRendered::instance];
    // Built on first use: the full-strength table's last entry is 0 until then.
    if (DAT_BlendFilterArrays::instance[32][31][0] == 0) {
        MACRO_CALL(UI::Rendering_Func::InitBlendFilterArraysUnk)();
    }
    destinationTable = DAT_BlendFilterArrays::instance[blendLevel][0];
    sourceTable = DAT_BlendFilterArrays::instance[32 - blendLevel][0];
    if (DAT_WindowAndDirectDraw::instance.colorBitMode == Rendering::RGB_555) {
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
            jne zoom_rows_chosen_555
            mov eax, dword ptr evenRowOffsets
            mov dword ptr offsets, eax
        zoom_rows_chosen_555:
            mov ecx, 64
        zoom_pixel_555:
            mov edx, dword ptr offsets
            add dword ptr offsets, 4
            mov edx, dword ptr [edx]
            mov ax, word ptr [esi + edx]
            mov edx, dword ptr sourceTable
            mov ebx, 0
            mov bx, ax
            and bx, 0x1f
            mov bx, word ptr [edx + ebx*8]
            and ax, 0xffe0
            or ax, bx
            mov bx, ax
            shr bx, 5
            and bx, 0x1f
            mov bx, word ptr [edx + ebx*8 + 2]
            and ax, 0xfc1f
            or ax, bx
            mov bx, ax
            shr bx, 10
            and bx, 0x1f
            mov bx, word ptr [edx + ebx*8 + 4]
            and ax, 0x3ff
            or ax, bx
            push ax
            mov edx, dword ptr offsets
            mov edx, dword ptr [edx]
            mov ax, word ptr [edi + edx]
            mov edx, dword ptr destinationTable
            mov ebx, 0
            mov bx, ax
            and bx, 0x1f
            mov bx, word ptr [edx + ebx*8]
            and ax, 0xffe0
            or ax, bx
            mov bx, ax
            shr bx, 5
            and bx, 0x1f
            mov bx, word ptr [edx + ebx*8 + 2]
            and ax, 0xfc1f
            or ax, bx
            mov bx, ax
            shr bx, 10
            and bx, 0x1f
            mov bx, word ptr [edx + ebx*8 + 4]
            and ax, 0x83ff
            or ax, bx
            mov edx, dword ptr offsets
            mov edx, dword ptr [edx]
            mov word ptr [edi + edx], ax
            pop ax
            add word ptr [edi + edx], ax
            add dword ptr offsets, 4
            sub cx, 1
            jne zoom_pixel_555
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
        jne zoom_rows_chosen_565
        mov eax, dword ptr evenRowOffsets
        mov dword ptr offsets, eax
    zoom_rows_chosen_565:
        mov ecx, 64
    zoom_pixel_565:
        mov edx, dword ptr offsets
        add dword ptr offsets, 4
        mov edx, dword ptr [edx]
        mov ax, word ptr [esi + edx]
        mov edx, dword ptr sourceTable
        mov ebx, 0
        mov bx, ax
        and bx, 0x1f
        mov bx, word ptr [edx + ebx*8]
        and ax, 0xffe0
        or ax, bx
        mov bx, ax
        shr bx, 5
        and bx, 0x3f
        mov bx, word ptr [edx + ebx*8 + 2]
        and ax, 0xf81f
        or ax, bx
        mov bx, ax
        shr bx, 11
        and bx, 0x1f
        mov bx, word ptr [edx + ebx*8 + 4]
        and ax, 0x7ff
        or ax, bx
        push ax
        mov edx, dword ptr offsets
        mov edx, dword ptr [edx]
        mov ax, word ptr [edi + edx]
        mov edx, dword ptr destinationTable
        mov ebx, 0
        mov bx, ax
        and bx, 0x1f
        mov bx, word ptr [edx + ebx*8]
        and ax, 0xffe0
        or ax, bx
        mov bx, ax
        shr bx, 5
        and bx, 0x3f
        mov bx, word ptr [edx + ebx*8 + 2]
        and ax, 0xf81f
        or ax, bx
        mov bx, ax
        shr bx, 11
        and bx, 0x1f
        mov bx, word ptr [edx + ebx*8 + 4]
        and ax, 0x7ff
        or ax, bx
        mov edx, dword ptr offsets
        mov edx, dword ptr [edx]
        mov word ptr [edi + edx], ax
        pop ax
        add word ptr [edi + edx], ax
        add dword ptr offsets, 4
        sub cx, 1
        jne zoom_pixel_565
    }
    // clang-format on
}

}
