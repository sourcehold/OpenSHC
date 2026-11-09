#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/Rendering/ColorMode.hpp"

#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044C8F0
        void TextureRenderCore::transformGmColorTableFromRGB555To565IfRequired(int gmID)
        {
            if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_565) {
                ushort* color = (ushort*)this->gmFileHeaderColorpaletteArray[gmID].colorPalette;
                int remaining = 2560;
                // a pointer over the palette in a do-while, not an indexed for (the for: quick_diff 1.0000 -> 0.6957)
                do {
                    ushort const value = *color;
                    // red and green move up a bit to make room for green's sixth bit; blue stays
                    *color = (value & 0x1f) + ((value & 0xfc00) + (value & 0x3e0)) * 2;
                    ++color;
                    --remaining;
                } while (remaining);
            }
        }

    }
}
}
