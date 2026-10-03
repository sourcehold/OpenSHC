#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

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
            int _rowOffset;
            _horizontalByteSize = DAT_PencilRenderCore::instance.horizontalByteSize;
            _drawPtr = (int)DAT_PencilRenderCore::instance.surfacePtr
                + drawY * DAT_PencilRenderCore::instance.horizontalByteSize + drawX * 2;
            _rowOffset = 0;
            *(undefined4*)(_drawPtr + _rowOffset) = 0xffff7bcf;
            *(undefined4*)(_drawPtr + _rowOffset + 4) = 0x39c70000;
            _rowOffset = _rowOffset + _horizontalByteSize;
            *(undefined4*)(_drawPtr + _rowOffset) = 0x7bcf7bcf;
            *(undefined4*)(_drawPtr + _rowOffset + 4) = 0x39c70000;
            _rowOffset = _rowOffset + _horizontalByteSize;
            *(undefined4*)(_drawPtr + _rowOffset) = 0x39c739c7;
            *(undefined4*)(_drawPtr + _rowOffset + 4) = 0x39c70000;
            _rowOffset = _rowOffset + _horizontalByteSize;
            *(undefined4*)(_drawPtr + _rowOffset) = 0;
            *(undefined4*)(_drawPtr + _rowOffset + 4) = 0;
        }

    }
}
}
