#include "../MouseState.func.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Input {

    // FUNCTION: STRONGHOLDCRUSADER 0x004684D0
    void MouseState::setupHitBox(int width, int height)
    {
        if (DAT_ViewportRenderState::instance.viewportState.isZoomedOutUnk) {
            this->hitboxXStart = (this->screenSpaceX
                                     + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX - width / 2)
                * 2;
            this->hitboxYStart
                = (this->screenSpaceY + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY
                      - height / 2)
                * 2;
            this->hitboxXEnd = (this->screenSpaceX
                                   + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX + width / 2)
                * 2;
            this->hitboxYEnd = (this->screenSpaceY
                                   + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY + height / 2)
                * 2;
        } else {
            this->hitboxXStart
                = this->screenSpaceX + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX - width / 2;
            this->hitboxYStart = this->screenSpaceY
                + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY - height / 2;
            this->hitboxXEnd
                = this->screenSpaceX + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX + width / 2;
            this->hitboxYEnd = this->screenSpaceY + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY
                + height / 2;
        }
    }

}
}
