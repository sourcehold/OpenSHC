#include "../MinimapViewState.func.hpp"

#include "OpenSHC/UI/MinimapViewState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B7460
    void MinimapViewState::renderMinimapLandscaping(int xPos, int yPos, int width, int heigth)
    {
        int yOffset;
        int xOffset;
        int widthFactor;
        int heightFactor;
        xOffset = (DAT_ViewportRenderState::instance.viewportState.viewportHeight + -5) / 2
            + (DAT_ViewportRenderState::instance.viewportState.viewportX / 32);
        yOffset = DAT_ViewportRenderState::instance.viewportState.viewportWidth / 2
            + (DAT_ViewportRenderState::instance.viewportState.viewportY / 8);
        if (this->needsRedraw || xOffset != this->lastRenderedXOffset || yOffset != this->lastRenderedYOffset) {
            if (DAT_TileMapState::instance.mapSize < 0xc9) {
                heightFactor = 2;
                widthFactor = 4;
            } else {
                heightFactor = 1;
                widthFactor = 2;
            }
            MACRO_CALL_MEMBER(UI::MinimapViewState_Func::drawMinimap, this)(
                xPos, yPos, width, heigth, 7, xOffset, yOffset, widthFactor, heightFactor, 0);
        }
        this->DAT_SomeMiniMapCounterTill4 = this->DAT_SomeMiniMapCounterTill4 + 1 & 0x80000003;
        if (this->DAT_SomeMiniMapCounterTill4 < 0) {
            this->DAT_SomeMiniMapCounterTill4 = (this->DAT_SomeMiniMapCounterTill4 - 1 | 0xfffffffc) + 1;
        }
        this->lastRenderedXOffset = xOffset;
        this->lastRenderedYOffset = yOffset;
        this->needsRedraw = 0;
        this->field3_0xc = 0;
    }

}
}
