#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/IO/Graphics/TgxToken.hpp"
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

        // FUNCTION: STRONGHOLDCRUSADER 0x0044F6F0
        void TextureRenderCore::renderTgxWithColorUnk(
            int xPos, int yPos, int width, int height, ushort* imageSource, ushort fillColorUnk)
        {
            // Draws the TGX image's shape in one colour: every stream or repeating pixel becomes fillColorUnk
            // Declared before the if because both arms assign them; lineJump is from one row's end to the next
            int lineJump;
            int lineBytes;
            int heightStart;
            int heightEnd;
            // Map arm first (== with the arms swapped: quick_diff 0.8016 -> 0.7115)
            if (this->drawBufferChoiceValue != OpenSHC::Rendering::Enums::RT_SCREEN_MENU) {
                DAT_TextureRenderCoreObject::instance.currentRenderSurface
                    = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                // The map surface is 4056 pixels wide
                lineJump = (4056 - width) * 2;
                heightStart = this->mapGameSurfaceHeightRange.start;
                lineBytes = 4056 * 2;
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
            // The token loop is handwritten assembly in the original
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

                // Rows above heightStart: skip their tokens without drawing
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
                add edi, lineJump
                sub edx, 1
                cmp edx, 0
                jg draw_token
                jmp done
            draw_transparent:
                add ecx, 1
                add ecx, ecx
                add edi, ecx
                jmp draw_token
            draw_repeating:
                add esi, 2
                add ecx, 1
                mov ax, fillColorUnk
            repeating_pixel:
                mov word ptr [edi], ax
                add edi, 2
                sub ecx, 1
                jne repeating_pixel
                jmp draw_token
            draw_stream:
                add ecx, 1
                mov ax, fillColorUnk
            stream_pixel:
                mov word ptr [edi], ax
                add esi, 2
                add edi, 2
                sub ecx, 1
                jne stream_pixel
                jmp draw_token
            done:
            }
            // clang-format on
        }

    }
}
}
