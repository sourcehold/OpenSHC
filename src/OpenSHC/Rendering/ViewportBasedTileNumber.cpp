#include "../Rendering.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x004B2A60
int Rendering::ViewportBasedTileNumber()
{
    // The four orientations' tables are 80400 entries apart; the original adds 8 here and takes it off again
    // in the index below, so both stay.
    int orientationOffset = 8;
    if (DAT_TileMapState::instance.mapOrientation != 0) {
        if (DAT_TileMapState::instance.mapOrientation == 6) {
            orientationOffset = 80408;
        } else if (DAT_TileMapState::instance.mapOrientation == 4) {
            orientationOffset = 160808;
        } else if (DAT_TileMapState::instance.mapOrientation == 2) {
            orientationOffset = 241208;
        }
    }
    return DAT_ViewportRenderState::instance
        .screenPointToTileNumber[DAT_ViewportRenderState::instance.viewportState.viewportX / 32
            + (DAT_ViewportRenderState::instance.viewportState.viewportY / 16
                  + DAT_ViewportRenderState::instance.viewportState.mbr_0xb0 / 2)
                * 401
            + DAT_ViewportRenderState::instance.viewportState.mbr_0xac + orientationOffset];
}

}
