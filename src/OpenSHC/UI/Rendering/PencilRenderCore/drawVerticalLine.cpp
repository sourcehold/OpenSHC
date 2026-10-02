#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00468E40
#pragma optimize("", off)
        void PencilRenderCore::drawVerticalLine()
        {
            dword _drawStartY;
            dword _drawEndY;
            dword _surfaceByteWidth;
            ushort _drawColor;
            _drawStartY = this->drawStartY;
            _drawEndY = this->drawEndY;
            _surfaceByteWidth = DAT_PencilRenderCore::instance.horizontalByteSize;
            _drawColor = this->drawColor;
            ushort* _surfacePtr = (ushort*)((int)DAT_PencilRenderCore::instance.surfacePtr + this->drawStartX * 2
                + _drawStartY * _surfaceByteWidth);
            for (; _drawStartY <= _drawEndY; _drawStartY = _drawStartY + 1) {
                *_surfacePtr = _drawColor;
                _surfacePtr = (ushort*)((int)_surfacePtr + _surfaceByteWidth);
            }
        }
#pragma optimize("", on)

    }
}
}
