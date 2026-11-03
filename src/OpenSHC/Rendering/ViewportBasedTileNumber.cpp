#include "../Rendering.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x004B2A60
int Rendering::ViewportBasedTileNumber()
{
    int orientationOffset = 8;
    if (DAT_TileMapState::instance.mapOrientation) {
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
                  + (int)DAT_ViewportRenderState::instance.viewportState.mbr_0xb0 / 2)
                * 401
            + DAT_ViewportRenderState::instance.viewportState.mbr_0xac + orientationOffset - 8];
}

}
