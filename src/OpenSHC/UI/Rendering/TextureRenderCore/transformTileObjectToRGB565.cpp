#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore/RGB555To565Asm.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044CAE0
        void TextureRenderCore::transformTileObjectToRGB565(int imageOffset)
        {
            // The conversion loop is handwritten assembly in the original, see RGB555To565Asm.hpp.
            ushort* _colorPtr = (ushort*)(this->gmProcessedImageData + imageOffset);
            // written by the asm below
            ushort _blue;
            ushort _green;
            // a tile object is 512 bytes, 256 pixels
            MACRO_RGB555_TO_565_LOOP(512)
        }

    }
}
}
