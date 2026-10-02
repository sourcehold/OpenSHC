#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/Rendering/ColorMode.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::ColorMode;

        /*
          Halves the brightness of one scanline. The mask keeps the low bit of every colour
          channel clear, and gains the extra red bit in RGB565 (0xf7de) over RGB555 (0x7bde).
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00468EA0
#pragma optimize("", off)
        void PencilRenderCore::dimHorizontalLine()
        {
            dword _drawStartX;
            dword _drawEndX;
            int _isRGB565;
            _drawStartX = this->drawStartX;
            _drawEndX = this->drawEndX;
            _isRGB565 = DAT_WindowAndDirectDraw::instance.colorBitMode != OpenSHC::Rendering::RGB_555;
            ushort* _drawPtr = (ushort*)((int)DAT_PencilRenderCore::instance.surfacePtr + _drawStartX * 2
                + this->drawStartY * DAT_PencilRenderCore::instance.horizontalByteSize);
            for (; _drawStartX <= _drawEndX; _drawStartX = _drawStartX + 1) {
                *_drawPtr = (*_drawPtr & (_isRGB565 ? 0xf7de : 0x7bde)) >> 1;
                _drawPtr = _drawPtr + 1;
            }
        }
#pragma optimize("", on)

    }
}
}
