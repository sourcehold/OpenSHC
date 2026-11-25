#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/Rendering/ColorMode.hpp"

#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044CBE0
        RGB15 TextureRenderCore::transformBGR24ToScreenColor(BGR24 color)
        {
            // The input is 0x00BBGGRR like a COLORREF; screen colors keep red in the top bits, so red moves up.
            // 0x3e0 and 0x7e0 are the green bits of a 555 and a 565 screen color.
            // One exit: returning from each branch loses the match.
            RGB15 screenColor;
            if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_555) {
                screenColor = ((color & 0xf8) << 7) | ((color >> 6) & 0x3e0) | ((color >> 19) & 0x1f);
            } else {
                screenColor = ((color & 0xf8) << 8) | ((color >> 5) & 0x7e0) | ((color >> 19) & 0x1f);
            }
            return screenColor;
        }

    }
}
}
