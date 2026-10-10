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
        int yOffset;
        int xOffset;
        int widthFactor;
        int heightFactor;
        xOffset = (DAT_ViewportRenderState::instance.viewportState.viewportHeight + -5) / 2
            + (DAT_ViewportRenderState::instance.viewportState.viewportX / 32);
        yOffset = DAT_ViewportRenderState::instance.viewportState.viewportWidth / 2
            + (DAT_ViewportRenderState::instance.viewportState.viewportY / 8);
        this->DAT_SomeMiniMapCounterTill4 = 0;
        if (this->needsRedraw || xOffset != this->lastRenderedXOffset || yOffset != this->lastRenderedYOffset) {
            if (DAT_TileMapState::instance.mapSize < 0xc9) {
                heightFactor = 2;
                widthFactor = 4;
            } else {
                heightFactor = 1;
                widthFactor = 2;
            }
            MACRO_CALL_MEMBER(UI::MinimapViewState_Func::drawMinimap, this)(
                xPos, yPos, width, height, 5, xOffset, yOffset, widthFactor, heightFactor, -1);
            DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 2;
        }
        this->lastRenderedXOffset = xOffset;
        this->lastRenderedYOffset = yOffset;
        this->needsRedraw = 0;
        this->field3_0xc = 0;
    }

}
}
