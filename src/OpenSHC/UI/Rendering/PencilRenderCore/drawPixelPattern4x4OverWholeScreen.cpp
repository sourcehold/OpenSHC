#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x004712E0
        void PencilRenderCore::drawPixelPattern4x4OverWholeScreen()
        {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::setupPencilSurface, this)();
            // The 4x4 pattern tiled over the whole screen
            for (this->currentY = 0; this->currentY < DAT_WindowAndDirectDraw::instance.resolutionY;
                this->currentY += 4) {
                for (this->currentX = 0; this->currentX < DAT_WindowAndDirectDraw::instance.resolutionX;
                    this->currentX += 4) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawPixelPattern4x4, this)(
                        this->currentX, this->currentY);
                }
            }
        }

    }
}
}
