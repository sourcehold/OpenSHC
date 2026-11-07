#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

#pragma optimize("g", off)
        // FUNCTION: STRONGHOLDCRUSADER 0x00468F20
        void PencilRenderCore::drawCurrentPixel()
        {
            uint _currentX = this->currentX;
            uint _currentY = this->currentY;
            ushort _drawColor = this->drawColor;
            *(ushort*)((int)DAT_PencilRenderCore::instance.surfacePtr + _currentX * 2
                + _currentY * DAT_PencilRenderCore::instance.horizontalByteSize) = _drawColor;
        }
#pragma optimize("g", on)

    }
}
}
