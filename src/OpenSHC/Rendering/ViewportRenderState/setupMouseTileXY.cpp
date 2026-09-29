#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x004E5DD0
    void ViewportRenderState::setupMouseTileXY()
    {
        this->viewportState.mouseTileX = 0;
        for (this->viewportState.mouseTileY = 0; this->viewportState.mouseTileY < 400;
            this->viewportState.mouseTileY++) {
            if (this->viewportState.mouseAtomRefFloorTile
                < this->translationMatrix[this->viewportState.mouseTileY + 1].firstTileOfRow) {
                break;
            }
        }

        this->viewportState.mouseTileX = this->viewportState.mouseAtomRefFloorTile
            - this->translationMatrix[this->viewportState.mouseTileY].firstTileOfRow;
        this->viewportState.mouseTileX
            = this->translationMatrix[this->viewportState.mouseTileY].distanceToCenter + this->viewportState.mouseTileX;
    }

}
}
