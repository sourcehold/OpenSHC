#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/Rendering/ColorMode.hpp"

#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::ColorMode;

        /*
          This one needs validation, since it shifts R and B. Maybe SHC works with BGR, in which case the   name of
          functions needs to change. -TheRedDaemon   decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0044CBE0
        RGB15 TextureRenderCore::transformBGR24ToScreenColor(BGR24 color)
        {
            int _blue;
            _blue = color >> 0x13 & 0x1f;
            if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_555) {
                return (color >> 6 & 0x3e0) | _blue | ((color & 0xf8) << 7);
            }
            return (color >> 5 & 0x7e0) | _blue | (ushort)(((byte)color & 0xf8) << 8);
        }

    }
}
}
