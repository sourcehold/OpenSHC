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

using Rendering::ColorMode;
using UI::Rendering::WindowAndDirectDraw;

// Blends the tile being drawn into the map surface, pixel by pixel: every colour component of the tile and of the
// surface under it is looked up in DAT_BlendFilterArrays (scaled by (32 - blendLevel) / 32 and blendLevel / 32) and
// the two results are added. The offset tables say where each pixel of the diamond-shaped tile lands on the
// 4056-pixel-wide map surface; zoomed out, every other row and column is used.
// The pixel loops are handwritten assembly in the original, transcribed here from the binary.

// Inline assembly cannot name a resolver global, so the loops reach the two globals they use through these.
static UI::Rendering::WindowAndDirectDraw* const s_windowAndDirectDraw = &DAT_WindowAndDirectDraw::instance;
static uint* const s_drawSomeX = &DAT_RenderMap_DrawSomeX::instance;

// FUNCTION: STRONGHOLDCRUSADER 0x00453600
void Rendering::ApplyBlending(int blendLevel)
{
    int* offsets;
    short* destinationTable;
    short* sourceTable;
    ushort* source;
    if (!DAT_TextureRenderCoreObject::instance.isZoom2) {
        offsets = DAT_BlendingDefinedData::instance.field164_0x27fc;
        int const drawY = DAT_00ed3154::instance - DAT_RenderMap_YOffset::instance + DAT_RenderMap_DrawSomeY::instance;
        if (drawY < DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start
            || drawY >= DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.end) {
            return;
        }
        source = (ushort*)((char*)DAT_TextureRenderCoreObject::instance.gmProcessedImageData
            + DAT_GMImageOffsets::instance[DAT_GmImageAddressToBeRendered::instance]);
        if (DAT_BlendFilterArrays::instance[32][31][0] == 0) {
            MACRO_CALL(UI::Rendering_Func::InitBlendFilterArraysUnk)();
        }
        destinationTable = DAT_BlendFilterArrays::instance[blendLevel][0];
        sourceTable = DAT_BlendFilterArrays::instance[32 - blendLevel][0];
        if (DAT_WindowAndDirectDraw::instance.colorBitMode == Rendering::RGB_555) {
            // clang-format off
            __asm {
        mov esi, source
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
        mov dword ptr [ecx]WindowAndDirectDraw.unknownSpecificPointer, edi
        mov ecx, 0x100
n555_4536c0:
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
        shr bx, 0xa
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
        shr bx, 0xa
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
        jne n555_4536c0
            }
            // clang-format on
            return;
        }
        // clang-format off
        __asm {
        mov esi, source
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
        mov dword ptr [ecx]WindowAndDirectDraw.unknownSpecificPointer, edi
        mov ecx, 0x100
n565_4537ae:
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
        shr bx, 0xb
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
        shr bx, 0xb
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
        jne n565_4537ae
        }
        // clang-format on
        return;
    }

    offsets = DAT_BlendingDefinedData::instance.field166_0x2dfc;
    int* evenRowOffsets = DAT_BlendingDefinedData::instance.field165_0x2bfc;
    int const drawY = DAT_00ed3154::instance - DAT_RenderMap_YOffset::instance + DAT_RenderMap_DrawSomeY::instance;
    if (drawY < DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start
        || drawY >= DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.end) {
        return;
    }
    source = (ushort*)((char*)DAT_TextureRenderCoreObject::instance.gmProcessedImageData
        + DAT_GMImageOffsets::instance[DAT_GmImageAddressToBeRendered::instance]);
    if (DAT_BlendFilterArrays::instance[32][31][0] == 0) {
        MACRO_CALL(UI::Rendering_Func::InitBlendFilterArraysUnk)();
    }
    destinationTable = DAT_BlendFilterArrays::instance[blendLevel][0];
    sourceTable = DAT_BlendFilterArrays::instance[32 - blendLevel][0];
    if (DAT_WindowAndDirectDraw::instance.colorBitMode == Rendering::RGB_555) {
        // clang-format off
        __asm {
        mov esi, source
        mov ecx, s_windowAndDirectDraw
        mov edi, dword ptr [ecx]WindowAndDirectDraw.surfacePointer_mapGame
        mov eax, s_drawSomeX
        mov eax, dword ptr [eax]
        and eax, 0xfffffffe
        add edi, eax
        mov eax, drawY
        mov ebx, eax
        shr eax, 1
        mov edx, 0x1fb0
        mul edx
        add edi, eax
        mov dword ptr [ecx]WindowAndDirectDraw.unknownSpecificPointer, edi
        and ebx, 1
        cmp ebx, 0
        jne z555_45391b
        mov eax, dword ptr evenRowOffsets
        mov dword ptr offsets, eax
z555_45391b:
        mov ecx, 0x40
z555_453920:
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
        shr bx, 0xa
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
        shr bx, 0xa
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
        jne z555_453920
        }
        // clang-format on
        return;
    }
    // clang-format off
    __asm {
        mov esi, source
        mov ecx, s_windowAndDirectDraw
        mov edi, dword ptr [ecx]WindowAndDirectDraw.surfacePointer_mapGame
        mov eax, s_drawSomeX
        mov eax, dword ptr [eax]
        and eax, 0xfffffffe
        add edi, eax
        mov eax, drawY
        mov ebx, eax
        shr eax, 1
        mov edx, 0x1fb0
        mul edx
        add edi, eax
        mov dword ptr [ecx]WindowAndDirectDraw.unknownSpecificPointer, edi
        and ebx, 1
        cmp ebx, 0
        jne z565_453a23
        mov eax, dword ptr evenRowOffsets
        mov dword ptr offsets, eax
z565_453a23:
        mov ecx, 0x40
z565_453a28:
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
        shr bx, 0xb
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
        shr bx, 0xb
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
        jne z565_453a28
    }
    // clang-format on
}

}
