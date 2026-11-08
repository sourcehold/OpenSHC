#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore/RGB555To565Asm.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044CB60
        void TextureRenderCore::transformRawToRGB555To565(int imageOffset, int imageSize)
        {
            // The conversion loop is handwritten assembly in the original, see RGB555To565Asm.hpp.
            ushort* _colorPtr = (ushort*)(this->gmProcessedImageData + imageOffset);
            // written by the asm below
            ushort _blue;
            ushort _green;
            MACRO_RGB555_TO_565_LOOP(imageSize)
        }

    }
}
}
