#include "../ViewportRenderState.func.hpp"

#include "OpenSHC/Rendering/Enums/ViewportConstants.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x004E1FA0
    ViewportRenderState* ViewportRenderState::Constructor_ViewportRenderState()
    {
        this->viewportState.viewportX = Enums::VC_TILE_PIXEL_WIDTH;
        this->viewportState.viewportY = Enums::VC_TILE_ROW_PIXEL_HEIGHT;
        this->viewportState.previousMouseTile = -1;

        DWORD now = timeGetTime();
        this->animationFrame32PreviousTime = now;
        this->animationFrame16PreviousTime = now;
        this->slowAnimationPreviousTime = now;
        this->animationFrame36PreviousTime = now;

        this->viewportState.isZoomedOutUnk = 0;
        this->DAT_MapEditorDisplayLayer = 0;
        this->animationFrame32 = 0;
        this->animationFrame512 = 0;
        this->animationFrame36 = 0;
        this->slowAnimationTicked = FALSE;
        this->animationFrame16 = 0;
        this->viewportState.field_0x94 = 0;

        this->animationFrame36Interval = 160;
        this->slowAnimationInterval = 180;
        this->animationFrame16Interval = 80;
        this->animationFrame32Interval = 100;
        this->availableFloaterIndex = 1;

        for (int i = 0; i < countof(this->landscapeAnimationRandomTileArray); ++i) {
            this->landscapeAnimationRandomTileArray[i] = 0;
        }
        return this;
    }

}
}
