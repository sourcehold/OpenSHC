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
        int tileY;
        bool found = false;
        for (tileY = 0; tileY < 400; tileY++) {
            rowLength = (rowLength != 201) + 200;
            for (tileX = 0; tileX < rowLength; ++tileX) {
                if (this->screenPointToTileNumber[screenPointIndex] == tile) {
                    found = true;
                    break;
                }
                screenPointIndex = screenPointIndex + 1;
            }
            if (found) {
                break;
            }
        }

        this->viewportState.viewportX = (tileX - this->viewportState.mbr_0xac) * 32;
        this->viewportState.viewportY = (tileY - this->viewportState.mbr_0xb0) * 8;
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
    }

}
}
