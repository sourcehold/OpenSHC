#include "../ViewportRenderState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x004E5E20
    void ViewportRenderState::focusOnTile(int tile)
    {
        int screenPointIndex = 8;
        if (DAT_TileMapState::instance.mapOrientation != 0) {
            if (DAT_TileMapState::instance.mapOrientation == 6) {
                screenPointIndex = 80408;
            } else if (DAT_TileMapState::instance.mapOrientation == 4) {
                screenPointIndex = 160808;
            } else if (DAT_TileMapState::instance.mapOrientation == 2) {
                screenPointIndex = 241208;
            }
        }

        int rowLength = 201;
        int tileX = 0;
        int tileY = 0;
        bool found = false;
        do {
            rowLength = (rowLength != 201) + 200;
            for (tileX = 0; tileX < rowLength; ++tileX) {
                if (this->screenPointToTileNumber[screenPointIndex - 8] == tile) {
                    found = true;
                    break;
                }
                screenPointIndex = screenPointIndex + 1;
            }
            if (found) {
                break;
            }
            tileY = tileY + 1;
        } while (tileY < 400);

        this->viewportState.viewportX = (tileX - this->viewportState.mbr_0xac) * 0x20;
        this->viewportState.viewportY = (tileY - this->viewportState.mbr_0xb0) * 8;
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
    }

}
}
