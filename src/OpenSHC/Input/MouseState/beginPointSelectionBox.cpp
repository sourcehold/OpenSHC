#include "../MouseState.func.hpp"

#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Input {

    // FUNCTION: STRONGHOLDCRUSADER 0x00468420
    void MouseState::beginPointSelectionBox()
    {
        this->previousSelectionBox.left
            = this->screenSpaceX + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX - 1;
        this->previousSelectionBox.top
            = this->screenSpaceY + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY - 1;
        this->previousSelectionBox.right
            = this->screenSpaceX + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX + 1;
        this->previousSelectionBox.bottom
            = this->screenSpaceY + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY + 1;

        if (DAT_ViewportRenderState::instance.viewportState.isZoomedOutUnk) {
            this->selectionBox.left
                = (this->screenSpaceX + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX) * 2 - 2;
            this->selectionBox.top
                = (this->screenSpaceY + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY) * 2 - 2;
            this->selectionBox.right
                = (this->screenSpaceX + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX) * 2 + 2;
            this->selectionBox.bottom
                = (this->screenSpaceY + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY) * 2 + 2;
        } else {
            this->selectionBox.left = this->previousSelectionBox.left;
            this->selectionBox.top = this->previousSelectionBox.top;
            this->selectionBox.right = this->previousSelectionBox.right;
            this->selectionBox.bottom = this->previousSelectionBox.bottom;
        }

        DAT_MouseState::instance.field31_0x94 = 0;
        DAT_MouseState::instance.selectionBoxMode = 1;
    }

}
}
