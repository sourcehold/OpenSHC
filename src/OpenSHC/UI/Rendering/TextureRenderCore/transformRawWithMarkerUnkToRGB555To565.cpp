#include "../TextureRenderCore.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        /*
          The original is hand-written assembly: it compares with cmp edx,0 rather than
          test, keeps the blue and green components in word-sized stack slots, and reuses
          the first parameter slot as the scratch for the red component.
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0044C940
        void TextureRenderCore::transformRawWithMarkerUnkToRGB555To565(int imageOffset, int imageSize)
        {
            int _blue;
            int _green;
            ushort* _colorPtr;
            _colorPtr = (ushort*)((int)this->gmProcessedImageData + imageOffset);
            __asm {
                mov esi, _colorPtr
                mov edx, imageSize
            pixelLoop:
                cmp edx, 0
                jle done
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
                mov word ptr imageOffset, bx
                mov ax, word ptr _blue
                mov bx, word ptr _green
                shl bx, 6
                add ax, bx
                mov bx, word ptr imageOffset
                shl bx, 0Bh
                add ax, bx
                mov word ptr [esi], ax
            nextPixel:
                sub edx, 2
                add esi, 2
                jmp pixelLoop
            done:
            }
        }

    }
}
}
