#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/IO/Graphics/TgxToken.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/DAT_BlendFilterArrays.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::IO::Graphics::TT_REPEATING_PIXELS;
        using OpenSHC::IO::Graphics::TT_STREAM_OF_PIXELS;
        using OpenSHC::IO::Graphics::TT_TGX_PIXEL_HEADER;
        using OpenSHC::IO::Graphics::TT_TGX_PIXEL_LENGTH;
        using OpenSHC::IO::Graphics::TT_TRANSPARENT_PIXELS;

        // The four drawing loops are handwritten assembly in the original, transcribed here from the binary.

        // FUNCTION: STRONGHOLDCRUSADER 0x0044E630
        void TextureRenderCore::renderInterfaceOrBuildingOccupationArea(
            int x, int y, int width, int height, ushort* imageDataPtr, int blendStrengthUnk)
        {
            // Blends the TGX image over the destination through the two filter rows blendStrengthUnk picks
            // Declared before the if because all three arms assign them; lineJump is from one row's end to the next
            int lineJump;
            int lineBytes;
            int heightStart;
            int heightEnd;
            if (height <= 0) {
                return;
            }
            // The last filter entry is still zero until the filter arrays are built
            if (DAT_BlendFilterArrays::instance[32][31][0] == 0) {
                MACRO_CALL(OpenSHC::UI::Rendering_Func::InitBlendFilterArraysUnk)();
            }
            short* const dstFilter = DAT_BlendFilterArrays::instance[blendStrengthUnk][0];
            short* const srcFilter = DAT_BlendFilterArrays::instance[32 - blendStrengthUnk][0];
            if (!DAT_TextureRenderCoreObject::instance.isZoom2) {
                // Map arm first (== with the arms swapped: quick_diff 0.8270 -> 0.8228)
                if (this->drawBufferChoiceValue != OpenSHC::Rendering::Enums::RT_SCREEN_MENU) {
                    DAT_TextureRenderCoreObject::instance.currentRenderSurface
                        = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                    // The map surface is 4056 pixels wide
                    lineJump = (4056 - width) * 2;
                    heightStart = this->mapGameSurfaceHeightRange.start;
                    heightEnd = this->mapGameSurfaceHeightRange.end;
                    lineBytes = 4056 * 2;
                } else {
                    DAT_TextureRenderCoreObject::instance.currentRenderSurface
                        = DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu;
                    lineJump = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine - width * 2;
                    heightStart = this->screenMenuSurfaceHeightRange.start;
                    heightEnd = this->screenMenuSurfaceHeightRange.end;
                    lineBytes = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine;
                }
                if (height + y > heightEnd) {
                    height = heightEnd - y;
                    if (height <= 0) {
                        return;
                    }
                }
                if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_555) {
                    // clang-format off
                    __asm {
                        mov esi, imageDataPtr
                        mov edi, DAT_TextureRenderCoreObject::instance.currentRenderSurface
                        mov eax, x
                        cmp eax, 0
                        jl done_555
                        add eax, eax
                        add edi, eax
                        mov eax, y
                        mov ebx, heightStart
                        cmp eax, ebx
                        jge add_y_offset_555
                        sub ebx, eax
                        mov eax, ebx
                        cmp height, eax
                        jle done_555
                        sub height, eax
                    skip_token_555:
                        mov bl, byte ptr [esi]
                        movzx ecx, byte ptr [esi]
                        and bl, TT_TGX_PIXEL_HEADER
                        and cl, TT_TGX_PIXEL_LENGTH
                        add esi, 1
                        cmp bl, TT_TRANSPARENT_PIXELS
                        je skip_token_555
                        cmp bl, TT_STREAM_OF_PIXELS
                        je skip_stream_555
                        cmp bl, TT_REPEATING_PIXELS
                        je skip_repeating_555
                        jmp skip_newline_555
                    skip_stream_555:
                        add ecx, 1
                        add ecx, ecx
                        add esi, ecx
                        jmp skip_token_555
                    skip_repeating_555:
                        add esi, 2
                        jmp skip_token_555
                    skip_newline_555:
                        sub eax, 1
                        cmp eax, 0
                        jg skip_token_555
                        mov eax, heightStart
                    add_y_offset_555:
                        mov edx, lineBytes
                        mul edx
                        add edi, eax
                        mov edx, height
                    draw_token_555:
                        mov ecx, 0
                        mov al, byte ptr [esi]
                        mov cl, byte ptr [esi]
                        and al, TT_TGX_PIXEL_HEADER
                        and cl, TT_TGX_PIXEL_LENGTH
                        add esi, 1
                        cmp al, TT_TRANSPARENT_PIXELS
                        je draw_transparent_555
                        cmp al, TT_STREAM_OF_PIXELS
                        je draw_stream_555
                        cmp al, TT_REPEATING_PIXELS
                        je draw_repeating_555
                        add edi, lineJump
                        sub edx, 1
                        cmp edx, 0
                        jg draw_token_555
                        jmp done_555
                    draw_transparent_555:
                        add ecx, 1
                        add ecx, ecx
                        add edi, ecx
                        jmp draw_token_555
                    draw_repeating_555:
                        mov eax, 0
                        mov ax, word ptr [esi]
                        add esi, 2
                        add ecx, 1
                        push edx
                        mov edx, srcFilter
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
                    repeating_pixel_555:
                        mov dx, word ptr [edi]
                        push ax
                        mov eax, dstFilter
                        mov ebx, 0
                        mov bx, dx
                        and bx, 0x1f
                        mov bx, word ptr [eax + ebx*8]
                        and dx, 0xffe0
                        or dx, bx
                        mov bx, dx
                        shr bx, 5
                        and bx, 0x1f
                        mov bx, word ptr [eax + ebx*8 + 2]
                        and dx, 0xfc1f
                        or dx, bx
                        mov bx, dx
                        shr bx, 10
                        and bx, 0x1f
                        mov bx, word ptr [eax + ebx*8 + 4]
                        and dx, 0x83ff
                        or dx, bx
                        pop ax
                        add dx, ax
                        mov word ptr [edi], dx
                        add edi, 2
                        sub ecx, 1
                        jne repeating_pixel_555
                        pop edx
                        jmp draw_token_555
                    draw_stream_555:
                        add ecx, 1
                        push edx
                        mov ebx, 0
                    stream_pixel_555:
                        mov ax, word ptr [esi]
                        mov edx, srcFilter
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
                        mov dx, word ptr [edi]
                        mov word ptr [edi], ax
                        mov eax, dstFilter
                        mov ebx, 0
                        mov bx, dx
                        and bx, 0x1f
                        mov bx, word ptr [eax + ebx*8]
                        and dx, 0xffe0
                        or dx, bx
                        mov bx, dx
                        shr bx, 5
                        and bx, 0x1f
                        mov bx, word ptr [eax + ebx*8 + 2]
                        and dx, 0xfc1f
                        or dx, bx
                        mov bx, dx
                        shr bx, 10
                        and bx, 0x1f
                        mov bx, word ptr [eax + ebx*8 + 4]
                        and dx, 0x83ff
                        or dx, bx
                        add word ptr [edi], dx
                        add esi, 2
                        add edi, 2
                        sub ecx, 1
                        jne stream_pixel_555
                        pop edx
                        jmp draw_token_555
                    done_555:
                    }
                    // clang-format on
                    return;
                }
                // clang-format off
                __asm {
                    mov esi, imageDataPtr
                    mov edi, DAT_TextureRenderCoreObject::instance.currentRenderSurface
                    mov eax, x
                    cmp eax, 0
                    jl done_565
                    add eax, eax
                    add edi, eax
                    mov eax, y
                    mov ebx, heightStart
                    cmp eax, ebx
                    jge add_y_offset_565
                    sub ebx, eax
                    mov eax, ebx
                    cmp height, eax
                    jle done_565
                    sub height, eax
                skip_token_565:
                    mov bl, byte ptr [esi]
                    movzx ecx, bl
                    and bl, TT_TGX_PIXEL_HEADER
                    and cl, TT_TGX_PIXEL_LENGTH
                    add esi, 1
                    cmp bl, TT_TRANSPARENT_PIXELS
                    je skip_token_565
                    cmp bl, TT_STREAM_OF_PIXELS
                    je skip_stream_565
                    cmp bl, TT_REPEATING_PIXELS
                    je skip_repeating_565
                    jmp skip_newline_565
                skip_stream_565:
                    add ecx, 1
                    add ecx, ecx
                    add esi, ecx
                    jmp skip_token_565
                skip_repeating_565:
                    add esi, 2
                    jmp skip_token_565
                skip_newline_565:
                    sub eax, 1
                    jg skip_token_565
                    mov eax, heightStart
                add_y_offset_565:
                    mov edx, lineBytes
                    mul edx
                    add edi, eax
                    mov edx, height
                draw_token_565:
                    mov al, byte ptr [esi]
                    movzx ecx, al
                    and al, TT_TGX_PIXEL_HEADER
                    and cl, TT_TGX_PIXEL_LENGTH
                    add esi, 1
                    cmp al, TT_TRANSPARENT_PIXELS
                    je draw_transparent_565
                    cmp al, TT_STREAM_OF_PIXELS
                    je draw_stream_565
                    cmp al, TT_REPEATING_PIXELS
                    je draw_repeating_565
                    add edi, lineJump
                    sub edx, 1
                    jg draw_token_565
                    jmp done_565
                draw_transparent_565:
                    add ecx, 1
                    add ecx, ecx
                    add edi, ecx
                    jmp draw_token_565
                draw_repeating_565:
                    movzx eax, word ptr [esi]
                    add esi, 2
                    push esi
                    add ecx, 1
                    push edx
                    mov esi, srcFilter
                    movzx ebx, ax
                    and bx, 0x1f
                    mov dx, word ptr [esi + ebx*8]
                    mov bx, ax
                    shr bx, 5
                    and bx, 0x3f
                    or dx, word ptr [esi + ebx*8 + 2]
                    mov bx, ax
                    shr bx, 11
                    and bx, 0x1f
                    or dx, word ptr [esi + ebx*8 + 4]
                    mov ax, dx
                    mov esi, dstFilter
                repeating_pixel_565:
                    mov dx, word ptr [edi]
                    push ax
                    movzx ebx, dx
                    and bx, 0x1f
                    mov ax, word ptr [esi + ebx*8]
                    mov bx, dx
                    shr bx, 5
                    and bx, 0x3f
                    or ax, word ptr [esi + ebx*8 + 2]
                    mov bx, dx
                    shr bx, 11
                    and bx, 0x1f
                    or ax, word ptr [esi + ebx*8 + 4]
                    mov dx, ax
                    pop ax
                    add dx, ax
                    mov word ptr [edi], dx
                    add edi, 2
                    sub ecx, 1
                    jne repeating_pixel_565
                    pop edx
                    pop esi
                    jmp draw_token_565
                draw_stream_565:
                    add ecx, 1
                    push edx
                    xor ebx, ebx
                stream_pixel_565:
                    mov ax, word ptr [esi]
                    mov edx, srcFilter
                    push cx
                    mov bx, ax
                    and bx, 0x1f
                    mov cx, word ptr [edx + ebx*8]
                    mov bx, ax
                    shr bx, 5
                    and bx, 0x3f
                    or cx, word ptr [edx + ebx*8 + 2]
                    mov bx, ax
                    shr bx, 11
                    and bx, 0x1f
                    or cx, word ptr [edx + ebx*8 + 4]
                    mov dx, word ptr [edi]
                    mov eax, dstFilter
                    movzx ebx, dx
                    and bx, 0x1f
                    add cx, word ptr [eax + ebx*8]
                    mov bx, dx
                    shr bx, 5
                    and bx, 0x3f
                    add cx, word ptr [eax + ebx*8 + 2]
                    mov bx, dx
                    shr bx, 11
                    and bx, 0x1f
                    add cx, word ptr [eax + ebx*8 + 4]
                    mov word ptr [edi], cx
                    add esi, 2
                    add edi, 2
                    pop cx
                    sub ecx, 1
                    jne stream_pixel_565
                    pop edx
                    jmp draw_token_565
                done_565:
                }
                // clang-format on
            } else {
                // Written by the asm only; declared in this branch (at function scope: quick_diff 1.0000 -> 0.9702)
                int columnOffset;
                DAT_TextureRenderCoreObject::instance.currentRenderSurface
                    = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                // A whole row here: the zoomed-out loops keep edi at the row's start and add columnOffset
                lineJump = 4056 * 2;
                lineBytes = 4056 * 2;
                heightStart = this->mapGameSurfaceHeightRange.start;
                heightEnd = this->mapGameSurfaceHeightRange.end;
                if (height + y > heightEnd) {
                    height = heightEnd - y;
                    if (height <= 0) {
                        return;
                    }
                }
                if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_555) {
                    // clang-format off
                    __asm {
                        mov esi, imageDataPtr
                        mov edi, DAT_TextureRenderCoreObject::instance.currentRenderSurface
                        mov eax, x
                        cmp eax, 0
                        jl zoom_done_555
                        and eax, 0xfffffffe
                        add edi, eax
                        mov eax, y
                        mov ebx, heightStart
                        cmp eax, ebx
                        jge zoom_add_y_offset_555
                        sub ebx, eax
                        mov eax, ebx
                        cmp height, eax
                        jle zoom_done_555
                        sub height, eax
                    zoom_skip_token_555:
                        mov bl, byte ptr [esi]
                        movzx ecx, bl
                        and bl, TT_TGX_PIXEL_HEADER
                        and cl, TT_TGX_PIXEL_LENGTH
                        add esi, 1
                        cmp bl, TT_TRANSPARENT_PIXELS
                        je zoom_skip_token_555
                        cmp bl, TT_STREAM_OF_PIXELS
                        je zoom_skip_stream_555
                        cmp bl, TT_REPEATING_PIXELS
                        je zoom_skip_repeating_555
                        jmp zoom_skip_newline_555
                    zoom_skip_stream_555:
                        add ecx, 1
                        add ecx, ecx
                        add esi, ecx
                        jmp zoom_skip_token_555
                    zoom_skip_repeating_555:
                        add esi, 2
                        jmp zoom_skip_token_555
                    zoom_skip_newline_555:
                        sub eax, 1
                        jg zoom_skip_token_555
                        mov eax, heightStart
                    zoom_add_y_offset_555:
                        mov edx, lineBytes
                        mov ecx, eax
                        shr eax, 1
                        mul edx
                        add edi, eax
                        xor eax, eax
                        xor ebx, ebx
                        mov columnOffset, ebx
                        mov edx, height
                    zoom_draw_token_555:
                        mov al, byte ptr [esi]
                        movzx ecx, al
                        and al, TT_TGX_PIXEL_HEADER
                        and cl, TT_TGX_PIXEL_LENGTH
                        add esi, 1
                        cmp al, TT_TRANSPARENT_PIXELS
                        je zoom_draw_transparent_555
                        cmp al, TT_STREAM_OF_PIXELS
                        je zoom_draw_stream_555
                        cmp al, TT_REPEATING_PIXELS
                        je zoom_draw_repeating_555
                        add edi, lineJump
                        sub edx, 1
                        jle zoom_done_555
                    zoom_skip_row_token_555:
                        mov bl, byte ptr [esi]
                        movzx ecx, bl
                        and bl, TT_TGX_PIXEL_HEADER
                        and cl, TT_TGX_PIXEL_LENGTH
                        add esi, 1
                        cmp bl, TT_TRANSPARENT_PIXELS
                        je zoom_skip_row_token_555
                        cmp bl, TT_STREAM_OF_PIXELS
                        je zoom_skip_row_stream_555
                        cmp bl, TT_REPEATING_PIXELS
                        je zoom_skip_row_repeating_555
                        jmp zoom_row_skipped_555
                    zoom_skip_row_stream_555:
                        add ecx, 1
                        add ecx, ecx
                        add esi, ecx
                        jmp zoom_skip_row_token_555
                    zoom_skip_row_repeating_555:
                        add esi, 2
                        jmp zoom_skip_row_token_555
                    zoom_row_skipped_555:
                        xor eax, eax
                        xor ebx, ebx
                        mov columnOffset, ebx
                        sub edx, 1
                        jg zoom_draw_token_555
                        jmp zoom_done_555
                    zoom_draw_transparent_555:
                        add ecx, 1
                        add columnOffset, ecx
                        jmp zoom_draw_token_555
                    zoom_draw_repeating_555:
                        movzx eax, word ptr [esi]
                        add esi, 2
                        push edx
                        mov edx, srcFilter
                        movzx ebx, ax
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
                        pop edx
                        add ecx, 1
                        mov ebx, columnOffset
                        add columnOffset, ecx
                    zoom_repeating_pixel_555:
                        test ebx, 1
                        jne zoom_repeating_next_555
                        push edx
                        push ebx
                        mov dx, word ptr [edi + ebx]
                        push ax
                        mov eax, dstFilter
                        movzx ebx, dx
                        and bx, 0x1f
                        mov bx, word ptr [eax + ebx*8]
                        and dx, 0xffe0
                        or dx, bx
                        mov bx, dx
                        shr bx, 5
                        and bx, 0x1f
                        mov bx, word ptr [eax + ebx*8 + 2]
                        and dx, 0xfc1f
                        or dx, bx
                        mov bx, dx
                        shr bx, 10
                        and bx, 0x1f
                        mov bx, word ptr [eax + ebx*8 + 4]
                        and dx, 0x83ff
                        or dx, bx
                        pop ax
                        add dx, ax
                        pop ebx
                        mov word ptr [edi + ebx], dx
                        pop edx
                    zoom_repeating_next_555:
                        add ebx, 1
                        sub ecx, 1
                        jne zoom_repeating_pixel_555
                        jmp zoom_draw_token_555
                    zoom_draw_stream_555:
                        add ecx, 1
                        mov ebx, columnOffset
                        add columnOffset, ecx
                    zoom_stream_pixel_555:
                        test ebx, 1
                        jne zoom_stream_next_555
                        push edx
                        push ebx
                        mov ax, word ptr [esi]
                        mov edx, srcFilter
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
                        pop ebx
                        mov dx, word ptr [edi + ebx]
                        mov word ptr [edi + ebx], ax
                        push ebx
                        mov eax, dstFilter
                        movzx ebx, dx
                        and bx, 0x1f
                        mov bx, word ptr [eax + ebx*8]
                        and dx, 0xffe0
                        or dx, bx
                        mov bx, dx
                        shr bx, 5
                        and bx, 0x1f
                        mov bx, word ptr [eax + ebx*8 + 2]
                        and dx, 0xfc1f
                        or dx, bx
                        mov bx, dx
                        shr bx, 10
                        and bx, 0x1f
                        mov bx, word ptr [eax + ebx*8 + 4]
                        and dx, 0x83ff
                        or dx, bx
                        pop ebx
                        add word ptr [edi + ebx], dx
                        pop edx
                    zoom_stream_next_555:
                        add ebx, 1
                        add esi, 2
                        sub ecx, 1
                        jne zoom_stream_pixel_555
                        jmp zoom_draw_token_555
                    zoom_done_555:
                    }
                    // clang-format on
                    return;
                }
                // clang-format off
                __asm {
                    mov esi, imageDataPtr
                    mov edi, DAT_TextureRenderCoreObject::instance.currentRenderSurface
                    mov eax, x
                    cmp eax, 0
                    jl zoom_done_565
                    and eax, 0xfffffffe
                    add edi, eax
                    mov eax, y
                    mov ebx, heightStart
                    cmp eax, ebx
                    jge zoom_add_y_offset_565
                    sub ebx, eax
                    mov eax, ebx
                    cmp height, eax
                    jle zoom_done_565
                    sub height, eax
                zoom_skip_token_565:
                    mov bl, byte ptr [esi]
                    movzx ecx, bl
                    and bl, TT_TGX_PIXEL_HEADER
                    and cl, TT_TGX_PIXEL_LENGTH
                    add esi, 1
                    cmp bl, TT_TRANSPARENT_PIXELS
                    je zoom_skip_token_565
                    cmp bl, TT_STREAM_OF_PIXELS
                    je zoom_skip_stream_565
                    cmp bl, TT_REPEATING_PIXELS
                    je zoom_skip_repeating_565
                    jmp zoom_skip_newline_565
                zoom_skip_stream_565:
                    add ecx, 1
                    add ecx, ecx
                    add esi, ecx
                    jmp zoom_skip_token_565
                zoom_skip_repeating_565:
                    add esi, 2
                    jmp zoom_skip_token_565
                zoom_skip_newline_565:
                    sub eax, 1
                    jg zoom_skip_token_565
                    mov eax, heightStart
                zoom_add_y_offset_565:
                    mov edx, lineBytes
                    mov ecx, eax
                    shr eax, 1
                    mul edx
                    add edi, eax
                    xor eax, eax
                    xor ebx, ebx
                    mov columnOffset, ebx
                    mov edx, height
                zoom_draw_token_565:
                    mov al, byte ptr [esi]
                    movzx ecx, al
                    and al, TT_TGX_PIXEL_HEADER
                    and cl, TT_TGX_PIXEL_LENGTH
                    add esi, 1
                    cmp al, TT_TRANSPARENT_PIXELS
                    je zoom_draw_transparent_565
                    cmp al, TT_STREAM_OF_PIXELS
                    je zoom_draw_stream_565
                    cmp al, TT_REPEATING_PIXELS
                    je zoom_draw_repeating_565
                    add edi, lineJump
                    sub edx, 1
                    jle zoom_done_565
                zoom_skip_row_token_565:
                    mov bl, byte ptr [esi]
                    movzx ecx, bl
                    and bl, TT_TGX_PIXEL_HEADER
                    and cl, TT_TGX_PIXEL_LENGTH
                    add esi, 1
                    cmp bl, TT_TRANSPARENT_PIXELS
                    je zoom_skip_row_token_565
                    cmp bl, TT_STREAM_OF_PIXELS
                    je zoom_skip_row_stream_565
                    cmp bl, TT_REPEATING_PIXELS
                    je zoom_skip_row_repeating_565
                    jmp zoom_row_skipped_565
                zoom_skip_row_stream_565:
                    add ecx, 1
                    add ecx, ecx
                    add esi, ecx
                    jmp zoom_skip_row_token_565
                zoom_skip_row_repeating_565:
                    add esi, 2
                    jmp zoom_skip_row_token_565
                zoom_row_skipped_565:
                    xor eax, eax
                    xor ebx, ebx
                    mov columnOffset, ebx
                    sub edx, 1
                    jg zoom_draw_token_565
                    jmp zoom_done_565
                zoom_draw_transparent_565:
                    add ecx, 1
                    add columnOffset, ecx
                    jmp zoom_draw_token_565
                zoom_draw_repeating_565:
                    movzx eax, word ptr [esi]
                    add esi, 2
                    push edx
                    mov edx, srcFilter
                    movzx ebx, ax
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
                    pop edx
                    add ecx, 1
                    mov ebx, columnOffset
                    add columnOffset, ecx
                zoom_repeating_pixel_565:
                    test ebx, 1
                    jne zoom_repeating_next_565
                    push edx
                    push ebx
                    mov dx, word ptr [edi + ebx]
                    push ax
                    mov eax, dstFilter
                    movzx ebx, dx
                    and bx, 0x1f
                    mov bx, word ptr [eax + ebx*8]
                    and dx, 0xffe0
                    or dx, bx
                    mov bx, dx
                    shr bx, 5
                    and bx, 0x3f
                    mov bx, word ptr [eax + ebx*8 + 2]
                    and dx, 0xf81f
                    or dx, bx
                    mov bx, dx
                    shr bx, 11
                    and bx, 0x1f
                    mov bx, word ptr [eax + ebx*8 + 4]
                    and dx, 0x7ff
                    or dx, bx
                    pop ax
                    add dx, ax
                    pop ebx
                    mov word ptr [edi + ebx], dx
                    pop edx
                zoom_repeating_next_565:
                    add ebx, 1
                    sub ecx, 1
                    jne zoom_repeating_pixel_565
                    jmp zoom_draw_token_565
                zoom_draw_stream_565:
                    add ecx, 1
                    mov ebx, columnOffset
                    add columnOffset, ecx
                zoom_stream_pixel_565:
                    test ebx, 1
                    jne zoom_stream_next_565
                    push edx
                    push ebx
                    mov ax, word ptr [esi]
                    mov edx, srcFilter
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
                    pop ebx
                    mov dx, word ptr [edi + ebx]
                    mov word ptr [edi + ebx], ax
                    push ebx
                    mov eax, dstFilter
                    movzx ebx, dx
                    and bx, 0x1f
                    mov bx, word ptr [eax + ebx*8]
                    and dx, 0xffe0
                    or dx, bx
                    mov bx, dx
                    shr bx, 5
                    and bx, 0x3f
                    mov bx, word ptr [eax + ebx*8 + 2]
                    and dx, 0xf81f
                    or dx, bx
                    mov bx, dx
                    shr bx, 11
                    and bx, 0x1f
                    mov bx, word ptr [eax + ebx*8 + 4]
                    and dx, 0x7ff
                    or dx, bx
                    pop ebx
                    add word ptr [edi + ebx], dx
                    pop edx
                zoom_stream_next_565:
                    add ebx, 1
                    add esi, 2
                    sub ecx, 1
                    jne zoom_stream_pixel_565
                    jmp zoom_draw_token_565
                zoom_done_565:
                }
                // clang-format on
            }
        }

    }
}
}
