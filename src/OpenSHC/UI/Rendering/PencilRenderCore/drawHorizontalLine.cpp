#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        /*
          The original reads the surface and its stride from the global instance rather than
          through this, and copies the four draw parameters into locals first.
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00468DE0
#pragma optimize("", off)
        void PencilRenderCore::drawHorizontalLine()
        {
            dword _startX;
            dword _startY;
            dword _endX;
            ushort _drawColor;
            _startX = this->drawStartX;
            _startY = this->drawStartY;
            _endX = this->drawEndX;
            _drawColor = this->drawColor;
            ushort* _surfacePtr = (ushort*)((int)DAT_PencilRenderCore::instance.surfacePtr + _startX * 2
                + _startY * DAT_PencilRenderCore::instance.horizontalByteSize);
            for (; _startX <= _endX; _startX = _startX + 1) {
                *_surfacePtr = _drawColor;
                _surfacePtr = _surfacePtr + 1;
            }
        }
#pragma optimize("", on)

    }
}
}
