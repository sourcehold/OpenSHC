#include "../TextureRenderCore.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044C940
        void TextureRenderCore::transformRawWithMarkerUnkToRGB555To565(int imageOffset, int imageSize)
        {
            ushort* _colorPtr;
            ushort _color;
            _colorPtr = (ushort*)((int)this->gmProcessedImageData + imageOffset);
            for (; 0 < imageSize; imageSize = imageSize + -2) {
                _color = *_colorPtr;
                if (_color != 63519) {
                    *_colorPtr = (_color & 0x1f) + ((_color & 0x3e0) >> 5) * 0x40 + ((_color & 0x7c00) >> 10) * 0x800;
                }
                _colorPtr = _colorPtr + 1;
            }
        }

    }
}
}
