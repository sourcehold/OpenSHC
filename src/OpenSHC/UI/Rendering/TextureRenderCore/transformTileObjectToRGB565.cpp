#include "../TextureRenderCore.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0044CAE0
        void TextureRenderCore::transformTileObjectToRGB565(int imageOffset)
        {
            ushort uVar1;
            ushort* _tileObjectPtr;
            int _index;
            _tileObjectPtr = (ushort*)((int)this->gmProcessedImageData + imageOffset);
            for (_index = 0x200; 0 < _index; _index = _index + -2) {
                uVar1 = *_tileObjectPtr;
                *_tileObjectPtr = (uVar1 & 0x1f) + ((uVar1 & 0x3e0) >> 5) * 0x40 + ((uVar1 & 0x7c00) >> 10) * 0x800;
                _tileObjectPtr = _tileObjectPtr + 1;
            }
        }

    }
}
}
