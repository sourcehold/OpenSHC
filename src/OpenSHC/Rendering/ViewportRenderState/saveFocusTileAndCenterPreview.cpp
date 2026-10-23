#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x004E8C50
    void ViewportRenderState::saveFocusTileAndCenterPreview()
    {
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::updateBuildingPreviewPosition, this)
        ((int)this->screenPixelWidth / 2 + (int)this->windowX, (int)this->screenPixelHeight / 2 + (int)this->windowY);
        this->field44_0x18b738 = this->viewportState.mouseTile;
    }

}
}
