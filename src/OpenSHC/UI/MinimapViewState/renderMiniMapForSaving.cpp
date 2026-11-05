#include "../MinimapViewState.func.hpp"

#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B7600
    void MinimapViewState::renderMiniMapForSaving(int xPos, int yPos, int width, int height)
    {
        int mapOffset = 400 - DAT_TileMapState::instance.mapSize;
        if (mapOffset == 400) {
            mapOffset = 0;
        }
        // the viewport position in pixels (32 per tile across, 8 down), divided back into tiles as
        // renderMinimapEditor divides viewportX by 32 and viewportY by 8
        int const xOffset = (mapOffset / 2 / 2 + 1) * 32 / 32
            + (DAT_ViewportRenderState::instance.viewportState.viewportHeight - 5) / 2;
        int const yOffset
            = (mapOffset / 2 * 8 + 8) / 8 + DAT_ViewportRenderState::instance.viewportState.viewportWidth / 2;
        MACRO_CALL(OpenSHC::OS_Func::_memset)(this->loadedMiniMap, 0, sizeof(this->loadedMiniMap));
        if (200 < DAT_TileMapState::instance.mapSize) {
            MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::drawMinimap, this)(
                xPos, yPos, width, height, 5, xOffset, yOffset, 2, 1, 1);
            MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::locatePlayerKeepPositionsOnMinimap, this)(4, 2, 1);
        } else {
            MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::drawMinimap, this)(
                xPos, yPos, width, height, 5, xOffset, yOffset, 4, 2, 1);
            MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::locatePlayerKeepPositionsOnMinimap, this)(4, 4, 2);
        }
        this->lastRenderedXOffset = xOffset;
        this->lastRenderedYOffset = yOffset;
        this->needsRedraw = 1;
        this->field3_0xc = 0;
    }

}
}
