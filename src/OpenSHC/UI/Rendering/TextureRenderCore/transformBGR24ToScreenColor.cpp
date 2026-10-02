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
            ushort uVar1;
            uVar1 = (ushort)(color >> 0x13) & 0x1f;
            if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_555) {
                return (ushort)(color >> 6) & 0x3e0 | uVar1 | (ushort)((color & 0xf8) << 7);
            }
            return (ushort)(color >> 5) & 0x7e0 | uVar1 | ((byte)color & 0xf8) << 8;
        }

    }
}
}
