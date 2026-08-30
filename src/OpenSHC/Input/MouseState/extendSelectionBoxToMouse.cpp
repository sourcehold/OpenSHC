#include "../MouseState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Input {

    // FUNCTION: STRONGHOLDCRUSADER 0x00470B30
    void MouseState::extendSelectionBoxToMouse()
    {
        this->previousSelectionBox.right
            = this->screenSpaceX + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX;
        this->previousSelectionBox.bottom
            = this->screenSpaceY + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY;

        if (DAT_ViewportRenderState::instance.viewportState.isZoomedOutUnk) {
            this->selectionBox.right
                = (DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX + this->screenSpaceX) * 2 + 2;
            this->selectionBox.bottom
                = (DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY + this->screenSpaceY) * 2 + 2;
        } else {
            this->selectionBox.right = this->previousSelectionBox.right;
            this->selectionBox.bottom = this->previousSelectionBox.bottom;
        }

        DAT_MouseState::instance.selectionBoxMode = 2;

        MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
            DAT_DirectionAlgorithmState::ptr)(
            this->selectionBox.left, this->selectionBox.top, this->selectionBox.right, this->selectionBox.bottom);

        if (16 < DAT_DirectionAlgorithmState::instance.distanceHigh) {
            DAT_MouseState::instance.field31_0x94 = 1;
        }
    }

}
}
