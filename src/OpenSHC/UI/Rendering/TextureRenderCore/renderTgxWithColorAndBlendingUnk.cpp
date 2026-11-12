#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/IO/Graphics/TgxToken.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

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

        // The drawing loop is handwritten assembly in the original, transcribed here from the binary.

        // FUNCTION: STRONGHOLDCRUSADER 0x0044F850
        void TextureRenderCore::renderTgxWithColorAndBlendingUnk(
            int xPos, int yPos, int width, int height, ushort* imageSource, ushort fillColorUnk, int blendStrengthUnk)
        {
            // blends fillColorUnk into the surface under a TGX picture, by each pixel's green channel times
            // (32 - blendStrengthUnk) / 32; clipped to the surface's height range
            // declared before the ifs because both arms assign them
            int greenShift;
            int redShift;
            int lineJump;
            int lineBytes;
            int heightStart;
            int heightEnd;
            // inverted in the parameter's own slot (a fresh local: reccmp 100.0% -> 93.6%)
            blendStrengthUnk = 32 - blendStrengthUnk;
            // map arm first (== with the arms swapped: quick_diff 0.8678 -> 0.8319)
            if (this->drawBufferChoiceValue != OpenSHC::Rendering::Enums::RT_SCREEN_MENU) {
                DAT_TextureRenderCoreObject::instance.currentRenderSurface
                    = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                // the map surface is 4056 pixels wide
                lineJump = (4056 - width) * 2;
                lineBytes = 4056 * 2;
                heightStart = this->mapGameSurfaceHeightRange.start;
                heightEnd = this->mapGameSurfaceHeightRange.end;
            } else {
                DAT_TextureRenderCoreObject::instance.currentRenderSurface
                    = DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu;
                lineJump = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine - width * 2;
                lineBytes = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine;
                heightStart = this->screenMenuSurfaceHeightRange.start;
                heightEnd = this->screenMenuSurfaceHeightRange.end;
            }
            if (height + yPos > heightEnd) {
                height = heightEnd - yPos;
                if (height <= 0) {
                    return;
                }
            }
            if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_555) {
                greenShift = 5;
                redShift = 10;
            } else {
                greenShift = 6;
                redShift = 11;
            }
            // clang-format off
            __asm {
                mov esi, imageSource
                mov edi, DAT_TextureRenderCoreObject::instance.currentRenderSurface
                mov eax, xPos
                cmp eax, 0
                jl done
                add eax, eax
                add edi, eax
                mov eax, yPos
                mov ebx, heightStart
                cmp eax, ebx
                jge add_y_offset
                sub ebx, eax
                mov eax, ebx
                cmp height, eax
                jle done
                sub height, eax
            skip_token:
                mov ecx, 0
                mov bl, byte ptr [esi]
                mov cl, byte ptr [esi]
                and bl, TT_TGX_PIXEL_HEADER
                and cl, TT_TGX_PIXEL_LENGTH
                add esi, 1
                cmp bl, TT_TRANSPARENT_PIXELS
                je skip_token
                cmp bl, TT_STREAM_OF_PIXELS
                je skip_stream
                cmp bl, TT_REPEATING_PIXELS
                je skip_repeating
                jmp skip_newline
            skip_stream:
                add ecx, 1
                add ecx, ecx
                add esi, ecx
                jmp skip_token
            skip_repeating:
                add esi, 2
                jmp skip_token
            skip_newline:
                sub eax, 1
                cmp eax, 0
                jg skip_token
                mov eax, heightStart
            add_y_offset:
                mov edx, lineBytes
                mul edx
                add edi, eax
                mov edx, height
            draw_token:
                push edx
                mov ecx, 0
                mov al, byte ptr [esi]
                mov cl, byte ptr [esi]
                and al, TT_TGX_PIXEL_HEADER
                and cl, TT_TGX_PIXEL_LENGTH
                add esi, 1
                cmp al, TT_TRANSPARENT_PIXELS
                je draw_transparent
                cmp al, TT_STREAM_OF_PIXELS
                je draw_stream
                cmp al, TT_REPEATING_PIXELS
                je draw_repeating
                pop edx
                add edi, lineJump
                sub edx, 1
                cmp edx, 0
                jg draw_token
                jmp done
            draw_transparent:
                add ecx, 1
                add ecx, ecx
                add edi, ecx
                pop edx
                jmp draw_token
            draw_repeating:
                mov edx, 0
                mov dx, word ptr [esi]
                add esi, 2
                add ecx, 1
                mov bx, word ptr fillColorUnk
                push cx
                mov cx, word ptr greenShift
                shr dx, cl
                and dx, 0x1f
                pop cx
                mov eax, blendStrengthUnk
                mul dx
                shr ax, 5
                mov dx, ax
                cmp dx, 0x1f
                je repeating_opaque
            repeating_blend:
                push bx
                push cx
                mov ax, bx
                push bx
                and ax, 0x1f
                mov cx, word ptr [edi]
                and cx, 0x1f
                sub ax, cx
                imul ax, dx
                shr ax, 5
                mov bx, word ptr [edi]
                and bx, 0x1f
                add ax, bx
                and ax, 0x1f
                pop bx
                push ax
                mov ax, bx
                push bx
                mov cx, word ptr greenShift
                shr ax, cl
                and ax, 0x1f
                mov bx, word ptr [edi]
                shr bx, cl
                and bx, 0x1f
                sub ax, bx
                imul ax, dx
                shr ax, 5
                mov bx, word ptr [edi]
                shr bx, cl
                and bx, 0x1f
                add ax, bx
                and ax, 0x1f
                shl ax, cl
                pop bx
                push ax
                mov ax, bx
                mov cx, word ptr redShift
                shr ax, cl
                and ax, 0x1f
                mov bx, word ptr [edi]
                shr bx, cl
                and bx, 0x1f
                sub ax, bx
                imul ax, dx
                shr ax, 5
                mov bx, word ptr [edi]
                shr bx, cl
                and bx, 0x1f
                add ax, bx
                and ax, 0x1f
                shl ax, cl
                mov bx, ax
                pop ax
                add bx, ax
                pop ax
                add bx, ax
                pop cx
                mov word ptr [edi], bx
                pop bx
                add edi, 2
                sub ecx, 1
                jne repeating_blend
                pop edx
                jmp draw_token
            repeating_opaque:
                mov word ptr [edi], bx
                add edi, 2
                sub ecx, 1
                jne repeating_opaque
                pop edx
                jmp draw_token
            draw_stream:
                add ecx, 1
            stream_pixel:
                mov dx, word ptr [esi]
                push cx
                mov cx, word ptr greenShift
                shr dx, cl
                and dx, 0x1f
                pop cx
                mov eax, blendStrengthUnk
                mul dx
                shr ax, 5
                mov dx, ax
                mov ax, word ptr fillColorUnk
                cmp dx, 0x1f
                je stream_opaque
                mov bx, ax
                push cx
                mov ax, bx
                push bx
                and ax, 0x1f
                mov cx, word ptr [edi]
                and cx, 0x1f
                sub ax, cx
                imul ax, dx
                shr ax, 5
                mov bx, word ptr [edi]
                and bx, 0x1f
                add ax, bx
                and ax, 0x1f
                pop bx
                push ax
                mov ax, bx
                push bx
                mov cx, word ptr greenShift
                shr ax, cl
                and ax, 0x1f
                mov bx, word ptr [edi]
                shr bx, cl
                and bx, 0x1f
                sub ax, bx
                imul ax, dx
                shr ax, 5
                mov bx, word ptr [edi]
                shr bx, cl
                and bx, 0x1f
                add ax, bx
                and ax, 0x1f
                shl ax, cl
                pop bx
                push ax
                mov ax, bx
                mov cx, word ptr redShift
                shr ax, cl
                and ax, 0x1f
                mov bx, word ptr [edi]
                shr bx, cl
                and bx, 0x1f
                sub ax, bx
                imul ax, dx
                shr ax, 5
                mov bx, word ptr [edi]
                shr bx, cl
                and bx, 0x1f
                add ax, bx
                and ax, 0x1f
                shl ax, cl
                mov bx, ax
                pop ax
                add bx, ax
                pop ax
                add bx, ax
                pop cx
                mov word ptr [edi], bx
                add esi, 2
                add edi, 2
                sub ecx, 1
                jne stream_pixel
                pop edx
                jmp draw_token
            stream_opaque:
                mov word ptr [edi], ax
                add esi, 2
                add edi, 2
                sub ecx, 1
                jne stream_pixel
                pop edx
                jmp draw_token
            done:
            }
            // clang-format on
        }

    }
}
}
