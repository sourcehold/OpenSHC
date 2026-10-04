#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/IO/Graphics/TgxTokenByte.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using IO::Graphics::TgxTokenByte;

        /*
          The original is hand-written assembly: it materialises zero with mov ecx,0,
          compares with cmp edx,0 rather than test, loads the same token byte twice
          into al and cl, reaches the loop top from three separate jmps, and reuses
          the first parameter slot as the scratch for the red component.
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0044C9C0
        void TextureRenderCore::transformTgxFromRGB555ToRGB565(ushort* tgxDataPtr, int tgxByteSize)
        {
            int _blue;
            int _green;
            TgxTokenByte* _texPtr;
            _texPtr = (TgxTokenByte*)tgxDataPtr;
            __asm {
                mov esi, _texPtr
                mov edx, tgxByteSize
            tokenLoop:
                cmp edx, 0
                jle done
                mov ecx, 0
                mov al, byte ptr [esi]
                mov cl, byte ptr [esi]
                and al, 0E0h
                and cl, 1Fh
                add ecx, 1
                sub edx, 1
                add esi, 1
                cmp al, 80h
                je newline
                cmp al, 40h
                je repeatingPixel
                cmp al, 20h
                je transparentPixels
            pixelLoop:
                mov ax, word ptr [esi]
                cmp ax, 0F81Fh
                je nextPixel
                mov bx, ax
                and bx, 1Fh
                mov word ptr _blue, bx
                mov bx, ax
                and bx, 3E0h
                shr bx, 5
                mov word ptr _green, bx
                mov bx, ax
                and bx, 7C00h
                shr bx, 0Ah
                mov word ptr tgxDataPtr, bx
                mov ax, word ptr _blue
                mov bx, word ptr _green
                shl bx, 6
                add ax, bx
                mov bx, word ptr tgxDataPtr
                shl bx, 0Bh
                add ax, bx
                mov word ptr [esi], ax
            nextPixel:
                sub edx, 2
                add esi, 2
                sub ecx, 1
                cmp ecx, 0
                jle tokenLoop
                jmp pixelLoop
            repeatingPixel:
                mov ax, word ptr [esi]
                mov bx, ax
                and bx, 1Fh
                mov word ptr _blue, bx
                mov bx, ax
                and bx, 3E0h
                shr bx, 5
                mov word ptr _green, bx
                mov bx, ax
                and bx, 7C00h
                shr bx, 0Ah
                mov word ptr tgxDataPtr, bx
                mov ax, word ptr _blue
                mov bx, word ptr _green
                shl bx, 6
                add ax, bx
                mov bx, word ptr tgxDataPtr
                shl bx, 0Bh
                add ax, bx
                mov word ptr [esi], ax
                sub edx, 2
                add esi, 2
                jmp tokenLoop
            transparentPixels:
                jmp tokenLoop
            newline:
                jmp tokenLoop
            done:
            }
        }

    }
}
}
