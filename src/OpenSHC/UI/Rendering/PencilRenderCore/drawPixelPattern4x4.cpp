#include "../PencilRenderCore.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00468F70
        void PencilRenderCore::drawPixelPattern4x4(int drawX, int drawY)
        {
            int _drawPtr;
            dword _horizontalByteSize;
            _horizontalByteSize = this->horizontalByteSize;
            _drawPtr = (int)this->surfacePtr + drawY * this->horizontalByteSize + drawX * 2;
            *(undefined4*)_drawPtr = 0xffff7bcf;
            *(undefined4*)(_drawPtr + 4) = 0x39c70000;
            *(undefined4*)(_drawPtr + _horizontalByteSize) = 0x7bcf7bcf;
            *(undefined4*)(_drawPtr + 4 + _horizontalByteSize) = 0x39c70000;
            *(undefined4*)(_drawPtr + _horizontalByteSize * 2) = 0x39c739c7;
            *(undefined4*)(_drawPtr + 4 + _horizontalByteSize * 2) = 0x39c70000;
            *(undefined4*)(_drawPtr + _horizontalByteSize * 3) = 0;
            *(undefined4*)(_drawPtr + 4 + _horizontalByteSize * 3) = 0;
        }

    }
}
}
