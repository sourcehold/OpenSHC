#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/IO/Graphics/TgxToken.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
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

        // The two drawing loops are handwritten assembly in the original, transcribed here from the binary.

        // FUNCTION: STRONGHOLDCRUSADER 0x0044F170
        void TextureRenderCore::renderGmWithPreparedAlphaMask(
            int x, int y, int width, int height, ushort* imageDataPtr, int blendStrength)
        {
            // Declared before the if because both arms assign them; lineJump is from one row's end to the next
            int lineJump;
            int lineBytes;
            int heightStart;
            int heightEnd;
            // The alpha surface prepared earlier, walked in step with the destination
            ushort* maskPtr = AlphaAndButtonSurfaceObj::instance.surfacePtr;
            if (height <= 0) {
                return;
            }
            // The last filter entry is still zero until the filter arrays are built
            if (DAT_BlendFilterArrays::instance[32][31][0] == 0) {
                MACRO_CALL(OpenSHC::UI::Rendering_Func::InitBlendFilterArraysUnk)();
            }
            // Both start at the table's base: the asm adds the row for the alpha value to each
            short* const dstFilter = DAT_BlendFilterArrays::instance[0][0];
            short* const srcFilter = DAT_BlendFilterArrays::instance[0][0];
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
                lineBytes = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine;
                heightStart = this->screenMenuSurfaceHeightRange.start;
                heightEnd = this->screenMenuSurfaceHeightRange.end;
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
                    movzx ecx, bl
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
                    mov ebx, width
                    add maskPtr, ebx
                    add maskPtr, ebx
                    sub eax, 1
                    jg skip_token_555
                    mov eax, heightStart
                add_y_offset_555:
                    mov edx, lineBytes
                    mul edx
                    add edi, eax
                    mov edx, height
                draw_token_555:
                    mov al, byte ptr [esi]
                    movzx ecx, al
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
                    jg draw_token_555
                    jmp done_555
                draw_transparent_555:
                    add ecx, 1
                    add ecx, ecx
                    add edi, ecx
                    add maskPtr, ecx
                    jmp draw_token_555
                draw_repeating_555:
                    xor eax, eax
                    add ecx, 1
                    push edx
                repeating_pixel_555:
                    xor edx, edx
                    mov eax, maskPtr
                    add maskPtr, 2
                    mov dx, word ptr [eax]
                    and edx, 1Fh
                    sub edx, blendStrength
                    jle repeating_next_555
                    cmp edx, 1Fh
                    jne repeating_blend_555
                    mov ax, word ptr [esi]
                    mov word ptr [edi], ax
                    jmp repeating_next_555
                repeating_blend_555:
                    push edx
                    shl edx, 9
                    add edx, srcFilter
                    mov ax, word ptr [esi]
                    movzx ebx, ax
                    and bx, 1Fh
                    mov bx, word ptr [edx + ebx*8]
                    and ax, 0FFE0h
                    or ax, bx
                    mov bx, ax
                    shr bx, 5
                    and bx, 1Fh
                    mov bx, word ptr [edx + ebx*8 + 2]
                    and ax, 0FC1Fh
                    or ax, bx
                    mov bx, ax
                    shr bx, 0Ah
                    and bx, 1Fh
                    mov bx, word ptr [edx + ebx*8 + 4]
                    and ax, 3FFh
                    or ax, bx
                    pop edx
                    push ax
                    mov eax, 20h
                    sub eax, edx
                    shl eax, 9
                    add eax, dstFilter
                    mov dx, word ptr [edi]
                    movzx ebx, dx
                    and bx, 1Fh
                    mov bx, word ptr [eax + ebx*8]
                    and dx, 0FFE0h
                    or dx, bx
                    mov bx, dx
                    shr bx, 5
                    and bx, 1Fh
                    mov bx, word ptr [eax + ebx*8 + 2]
                    and dx, 0FC1Fh
                    or dx, bx
                    mov bx, dx
                    shr bx, 0Ah
                    and bx, 1Fh
                    mov bx, word ptr [eax + ebx*8 + 4]
                    and dx, 83FFh
                    or dx, bx
                    pop ax
                    add dx, ax
                    mov word ptr [edi], dx
                repeating_next_555:
                    add edi, 2
                    sub ecx, 1
                    jne repeating_pixel_555
                    pop edx
                    add esi, 2
                    jmp draw_token_555
                draw_stream_555:
                    add ecx, 1
                    push edx
                    xor ebx, ebx
                stream_pixel_555:
                    xor edx, edx
                    mov eax, maskPtr
                    add maskPtr, 2
                    mov dx, word ptr [eax]
                    and edx, 1Fh
                    sub edx, blendStrength
                    jle stream_next_555
                    cmp edx, 1Fh
                    jne stream_blend_555
                    mov ax, word ptr [esi]
                    mov word ptr [edi], ax
                    jmp stream_next_555
                stream_blend_555:
                    push edx
                    shl edx, 9
                    add edx, srcFilter
                    mov ax, word ptr [esi]
                    mov bx, ax
                    and bx, 1Fh
                    mov bx, word ptr [edx + ebx*8]
                    and ax, 0FFE0h
                    or ax, bx
                    mov bx, ax
                    shr bx, 5
                    and bx, 1Fh
                    mov bx, word ptr [edx + ebx*8 + 2]
                    and ax, 0FC1Fh
                    or ax, bx
                    mov bx, ax
                    shr bx, 0Ah
                    and bx, 1Fh
                    mov bx, word ptr [edx + ebx*8 + 4]
                    and ax, 3FFh
                    or ax, bx
                    mov bx, word ptr [edi]
                    mov word ptr [edi], ax
                    pop edx
                    mov eax, 20h
                    sub eax, edx
                    shl eax, 9
                    add eax, dstFilter
                    mov dx, bx
                    movzx ebx, dx
                    and bx, 1Fh
                    mov bx, word ptr [eax + ebx*8]
                    and dx, 0FFE0h
                    or dx, bx
                    mov bx, dx
                    shr bx, 5
                    and bx, 1Fh
                    mov bx, word ptr [eax + ebx*8 + 2]
                    and dx, 0FC1Fh
                    or dx, bx
                    mov bx, dx
                    shr bx, 0Ah
                    and bx, 1Fh
                    mov bx, word ptr [eax + ebx*8 + 4]
                    and dx, 83FFh
                    or dx, bx
                    add word ptr [edi], dx
                stream_next_555:
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
                mov ebx, width
                add maskPtr, ebx
                add maskPtr, ebx
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
                add maskPtr, ecx
                jmp draw_token_565
            draw_repeating_565:
                xor eax, eax
                add ecx, 1
                push edx
            repeating_pixel_565:
                xor edx, edx
                mov eax, maskPtr
                add maskPtr, 2
                mov dx, word ptr [eax]
                and edx, 1Fh
                sub edx, blendStrength
                jle repeating_next_565
                cmp edx, 1Fh
                jne repeating_blend_565
                mov ax, word ptr [esi]
                mov word ptr [edi], ax
                jmp repeating_next_565
            repeating_blend_565:
                push cx
                push edx
                shl edx, 9
                add edx, srcFilter
                mov ax, word ptr [esi]
                movzx ebx, ax
                and bx, 1Fh
                mov cx, word ptr [edx + ebx*8]
                mov bx, ax
                shr bx, 5
                and bx, 3Fh
                or cx, word ptr [edx + ebx*8 + 2]
                mov bx, ax
                shr bx, 0Bh
                and bx, 1Fh
                or cx, word ptr [edx + ebx*8 + 4]
                pop edx
                mov eax, 20h
                sub eax, edx
                shl eax, 9
                add eax, dstFilter
                mov dx, word ptr [edi]
                movzx ebx, dx
                and bx, 1Fh
                add cx, word ptr [eax + ebx*8]
                mov bx, dx
                shr bx, 5
                and bx, 3Fh
                add cx, word ptr [eax + ebx*8 + 2]
                mov bx, dx
                shr bx, 0Bh
                and bx, 1Fh
                add cx, word ptr [eax + ebx*8 + 4]
                mov word ptr [edi], cx
                pop cx
            repeating_next_565:
                add edi, 2
                sub ecx, 1
                jne repeating_pixel_565
                pop edx
                add esi, 2
                jmp draw_token_565
            draw_stream_565:
                add ecx, 1
                push edx
                xor ebx, ebx
            stream_pixel_565:
                xor edx, edx
                mov eax, maskPtr
                add maskPtr, 2
                mov dx, word ptr [eax]
                and edx, 1Fh
                sub edx, blendStrength
                jle stream_next_565
                cmp edx, 1Fh
                jne stream_blend_565
                mov ax, word ptr [esi]
                mov word ptr [edi], ax
                jmp stream_next_565
            stream_blend_565:
                push cx
                push edx
                shl edx, 9
                add edx, srcFilter
                mov ax, word ptr [esi]
                mov bx, ax
                and bx, 1Fh
                mov cx, word ptr [edx + ebx*8]
                mov bx, ax
                shr bx, 5
                and bx, 3Fh
                or cx, word ptr [edx + ebx*8 + 2]
                mov bx, ax
                shr bx, 0Bh
                and bx, 1Fh
                or cx, word ptr [edx + ebx*8 + 4]
                movzx bx, word ptr [edi]
                pop edx
                mov eax, 20h
                sub eax, edx
                shl eax, 9
                add eax, dstFilter
                mov dx, bx
                and bx, 1Fh
                add cx, word ptr [eax + ebx*8]
                mov bx, dx
                shr bx, 5
                and bx, 3Fh
                add cx, word ptr [eax + ebx*8 + 2]
                mov bx, dx
                shr bx, 0Bh
                and bx, 1Fh
                add cx, word ptr [eax + ebx*8 + 4]
                mov word ptr [edi], cx
                pop cx
            stream_next_565:
                add esi, 2
                add edi, 2
                sub ecx, 1
                jne stream_pixel_565
                pop edx
                jmp draw_token_565
            done_565:
            }
            // clang-format on
        }

    }
}
}
