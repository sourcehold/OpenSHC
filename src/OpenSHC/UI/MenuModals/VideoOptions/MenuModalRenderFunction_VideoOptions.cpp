#include "../VideoOptions.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00492120
        void VideoOptions::MenuModalRenderFunction_VideoOptions(int x, int y, int width, int height)
        {
            /*
              added by script: "Video Options"
             */
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                DAT_PencilRenderCore::ptr)(0x4a, 4, x, y, width, height);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                DAT_PencilRenderCore::ptr)(x + 0x66, y + 0xd5, x + 0xb2, y + 0xfc, 0x10);
        }

    }
}
}
