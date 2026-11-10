#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/Rendering/ColorMode.hpp"

#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044C8F0
        void TextureRenderCore::transformGmColorTableFromRGB555To565IfRequired(int gmID)
        {
            if (DAT_WindowAndDirectDraw::instance.colorBitMode != OpenSHC::Rendering::RGB_565) {
                return;
            }
            ushort* color = (ushort*)this->gmFileHeaderColorpaletteArray[gmID].colorPalette;
            for (int remaining = countof(this->gmFileHeaderColorpaletteArray[gmID].colorPalette)
                    * countof(this->gmFileHeaderColorpaletteArray[gmID].colorPalette[0]);
                remaining != 0; --remaining) {
                ushort const rgb555 = *color;
                // red and green move up a bit to make room for green's sixth bit; blue stays
                *color = (rgb555 & 0x1f) + ((rgb555 & 0xfc00) + (rgb555 & 0x3e0)) * 2;
                ++color;
            }
        }

    }
}
}
