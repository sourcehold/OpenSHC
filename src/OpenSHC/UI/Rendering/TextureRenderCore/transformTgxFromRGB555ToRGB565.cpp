#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/IO/Graphics/TgxToken.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore/RGB555To565Asm.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::IO::Graphics::TT_NEWLINE;
        using OpenSHC::IO::Graphics::TT_REPEATING_PIXELS;
        using OpenSHC::IO::Graphics::TT_TGX_PIXEL_HEADER;
        using OpenSHC::IO::Graphics::TT_TGX_PIXEL_LENGTH;
        using OpenSHC::IO::Graphics::TT_TRANSPARENT_PIXELS;

        // FUNCTION: STRONGHOLDCRUSADER 0x0044C9C0
        void TextureRenderCore::transformTgxFromRGB555ToRGB565(ushort* tgxDataPtr, int tgxByteSize)
        {
            // Copied in C++: the original copies the parameter before saving ebx and esi
            ushort* const tgxPtr = tgxDataPtr;
            // Written by the asm only; red waits in tgxDataPtr's slot, dead once copied
            ushort _blue;
            ushort _green;
            // Handwritten in the original; a token's top three bits are its kind, the low five its run length - 1
            // clang-format off
            __asm {
                mov esi, tgxPtr
                mov edx, tgxByteSize

            next_token:
                cmp edx, 0
                jle done
                mov ecx, 0
                mov al, byte ptr [esi]
                mov cl, byte ptr [esi]
                and al, TT_TGX_PIXEL_HEADER
                and cl, TT_TGX_PIXEL_LENGTH
                add ecx, 1
                sub edx, 1
                add esi, 1
                cmp al, TT_NEWLINE
                je newline
                cmp al, TT_REPEATING_PIXELS
                je repeating_pixels
                cmp al, TT_TRANSPARENT_PIXELS
                je transparent_pixels

            stream_pixel:
            }
            MACRO_RGB555_TO_565_PIXEL(tgxDataPtr, MACRO_ASM_SKIP_MARKER_TEST, MACRO_ASM_SKIP_MARKER_LABEL)
            __asm {
                sub ecx, 1
                cmp ecx, 0
                jle next_token
                jmp stream_pixel

            repeating_pixels:
            }
            MACRO_RGB555_TO_565_PIXEL(tgxDataPtr, MACRO_ASM_NONE, MACRO_ASM_NONE)
            __asm {
                jmp next_token

            transparent_pixels:
                jmp next_token

            newline:
                jmp next_token

            done:
            }
            // clang-format on
        }

    }
}
}
