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

        // The drawing loop is handwritten assembly in the original, transcribed here from the binary.

        // FUNCTION: STRONGHOLDCRUSADER 0x00454A60
        void TextureRenderCore::drawTgxOnFlaggedSurface(
            int xPos, int yPos, int gfxWidth, int gfxHeight, ushort* tgxSourcePtr)
        {
            // decodes a TGX picture onto the current render surface, clipped to renderingRect_16c854
            int const top = this->renderingRect_16c854.top;
            int const left = this->renderingRect_16c854.left;
            int const bottom = this->renderingRect_16c854.bottom;
            int const right = this->renderingRect_16c854.right;
            // declared before the switch because both cases assign them; lineJump is from one row's end to the next
            int lineJump;
            int lineBytes;
            switch (this->currentRenderSurfaceIdentifierUnk_0x8) {
            case OpenSHC::Rendering::Enums::RT_MAP_GAME:
                DAT_TextureRenderCoreObject::instance.currentRenderSurface
                    = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                // the map surface is 4056 pixels wide
                lineJump = (4056 - gfxWidth) * 2;
                lineBytes = 4056 * 2;
                break;
            case OpenSHC::Rendering::Enums::RT_SCREEN_MENU:
                DAT_TextureRenderCoreObject::instance.currentRenderSurface
                    = DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu;
                lineJump = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine - gfxWidth * 2;
                lineBytes = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine;
                break;
            }
            if (gfxHeight + yPos > bottom) {
                gfxHeight = bottom - yPos;
                if (gfxHeight <= 0) {
                    return;
                }
            }
            // clang-format off
            __asm {
                mov esi, tgxSourcePtr
                mov edi, DAT_TextureRenderCoreObject::instance.currentRenderSurface
                mov eax, xPos
                add eax, eax
                add edi, eax
                mov eax, yPos
                mov ebx, top
                cmp eax, ebx
                jge add_y_offset
                sub ebx, eax
                mov eax, ebx
                cmp gfxHeight, eax
                jle done
                sub gfxHeight, eax
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
                mov eax, top
            add_y_offset:
                mov edx, lineBytes
                mul edx
                add edi, eax
                mov edx, gfxHeight
                mov ebx, xPos
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
                mov ebx, xPos
                add edi, lineJump
                sub edx, 1
                cmp edx, 0
                jg draw_token
                jmp done
            draw_transparent:
                add ecx, 1
                add ebx, ecx
                add ecx, ecx
                add edi, ecx
                jmp draw_token
            draw_repeating:
                mov eax, 0
                add ecx, 1
                cmp ebx, right
                jl repeating_clip
            repeating_advance:
                add ebx, ecx
                add ecx, ecx
                add edi, ecx
                add esi, 2
                jmp draw_token
            repeating_clip:
                cmp ebx, left
                jge repeating_right
                mov eax, ecx
                add eax, ebx
                cmp eax, left
                jle repeating_advance
                mov eax, left
                sub eax, ebx
                sub ecx, eax
                add ebx, eax
                add eax, eax
                add edi, eax
            repeating_right:
                mov eax, ecx
                add eax, ebx
                cmp eax, right
                jl repeating_copy
                push edx
                mov edx, eax
                sub edx, right
                sub ecx, edx
                mov ax, word ptr [esi]
            repeating_clip_loop:
                mov word ptr [edi], ax
                add edi, 2
                add ebx, 1
                sub ecx, 1
                jne repeating_clip_loop
                add ebx, edx
                add edx, edx
                add edi, edx
                pop edx
                add esi, 2
                jmp draw_token
            repeating_copy:
                mov ax, word ptr [esi]
            repeating_copy_loop:
                mov word ptr [edi], ax
                add edi, 2
                add ebx, 1
                sub ecx, 1
                jne repeating_copy_loop
                add esi, 2
                jmp draw_token
            draw_stream:
                add ecx, 1
                cmp ebx, right
                jl stream_clip
            stream_advance:
                add ebx, ecx
                add ecx, ecx
                add esi, ecx
                add edi, ecx
                jmp draw_token
            stream_clip:
                cmp ebx, left
                jge stream_right
                mov eax, ecx
                add eax, ebx
                cmp eax, left
                jle stream_advance
                mov eax, left
                sub eax, ebx
                sub ecx, eax
                add ebx, eax
                add eax, eax
                add esi, eax
                add edi, eax
            stream_right:
                mov eax, ecx
                add eax, ebx
                cmp eax, right
                jl stream_copy
                push edx
                mov edx, eax
                sub edx, right
                sub ecx, edx
            stream_clip_loop:
                mov ax, word ptr [esi]
                mov word ptr [edi], ax
                add esi, 2
                add edi, 2
                add ebx, 1
                sub ecx, 1
                jne stream_clip_loop
                add ebx, edx
                add edx, edx
                add esi, edx
                add edi, edx
                pop edx
                jmp draw_token
            stream_copy:
                mov ax, word ptr [esi]
                mov word ptr [edi], ax
                add esi, 2
                add edi, 2
                add ebx, 1
                sub ecx, 1
                jne stream_copy
                jmp draw_token
            done:
            }
            // clang-format on
        }

    }
}
}
