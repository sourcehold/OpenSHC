#include "../MinimapViewState.func.hpp"

#include "OpenSHC/UI/MinimapViewState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B7530
    void MinimapViewState::renderMinimapEditor(int xPos, int yPos, int width, int height)
    {
        int const xOffset = (DAT_ViewportRenderState::instance.viewportState.viewportHeight - 5) / 2
            + DAT_ViewportRenderState::instance.viewportState.viewportX / 32;
        int const yOffset = DAT_ViewportRenderState::instance.viewportState.viewportY / 8
            + DAT_ViewportRenderState::instance.viewportState.viewportWidth / 2;
        this->someMiniMapCounterTill4 = 0;
        if (this->needsRedraw != 0 || xOffset != this->lastRenderedXOffset || yOffset != this->lastRenderedYOffset) {
            if (200 < DAT_TileMapState::instance.mapSize) {
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::drawMinimap, this)(
                    xPos, yPos, width, height, 5, xOffset, yOffset, 2, 1, -1);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::drawMinimap, this)(
                    xPos, yPos, width, height, 5, xOffset, yOffset, 4, 2, -1);
            }
            DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 2;
        }
        this->lastRenderedXOffset = xOffset;
        this->lastRenderedYOffset = yOffset;
        this->needsRedraw = 0;
        this->field3_0xc = 0;
    }

}
}
