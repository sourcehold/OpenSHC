#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004712E0
        void PencilRenderCore::drawPixelPattern4x4OverWholeScreen()
        {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::setupPencilSurface, this)();
            this->currentY = 0;
            if (0 < DAT_WindowAndDirectDraw::instance.resolutionY) {
                do {
                    this->currentX = 0;
                    if (0 < DAT_WindowAndDirectDraw::instance.resolutionX) {
                        do {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawPixelPattern4x4, this)(
                                this->currentX, (int)((int)(this->currentY)));
                            this->currentX = this->currentX + 4;
                        } while ((int)this->currentX < DAT_WindowAndDirectDraw::instance.resolutionX);
                    }
                    this->currentY = this->currentY + 4;
                } while ((int)this->currentY < DAT_WindowAndDirectDraw::instance.resolutionY);
            }
        }

    }
}
}
