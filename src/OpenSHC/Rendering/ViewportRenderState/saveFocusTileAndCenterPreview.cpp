#include "../ViewportRenderState.func.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x004E8C50
    void ViewportRenderState::saveFocusTileAndCenterPreview()
    {
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::updateBuildingPreviewPosition, this)
        (this->screenPixelWidth / 2 + this->windowX, this->screenPixelHeight / 2 + this->windowY);
        this->field_0x18b738 = this->viewportState.mouseTile;
    }

}
}
