#include "../ViewportRenderState.func.hpp"

#include "OpenSHC/Map/MapConstants.hpp"
#include "OpenSHC/Rendering/Enums/ViewportConstants.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x004E5E20
    void ViewportRenderState::focusOnTile(int tile)
    {
        int screenPointIndex = Enums::VC_SCREEN_POINT_TABLE_START;
        if (DAT_TileMapState::instance.mapOrientation != Map::MC_MAP_NORTH) {
            if (DAT_TileMapState::instance.mapOrientation == Map::MC_MAP_WEST) {
                screenPointIndex = Enums::VC_SCREEN_POINT_TABLE_START + Enums::VC_SCREEN_POINT_TABLE_SIZE;
            } else if (DAT_TileMapState::instance.mapOrientation == Map::MC_MAP_SOUTH) {
                screenPointIndex = Enums::VC_SCREEN_POINT_TABLE_START + 2 * Enums::VC_SCREEN_POINT_TABLE_SIZE;
            } else if (DAT_TileMapState::instance.mapOrientation == Map::MC_MAP_EAST) {
                screenPointIndex = Enums::VC_SCREEN_POINT_TABLE_START + 3 * Enums::VC_SCREEN_POINT_TABLE_SIZE;
            }
        }

        int rowLength = Enums::VC_SCREEN_POINT_LONG_ROW;
        int tileX = 0;
        int tileY;
        bool found = false;
        for (tileY = 0; tileY < Map::MC_MAP_XY_LIMIT; tileY++) {
            rowLength = (rowLength != Enums::VC_SCREEN_POINT_LONG_ROW) + Enums::VC_SCREEN_POINT_SHORT_ROW;
            for (tileX = 0; tileX < rowLength; ++tileX) {
                if (this->screenPointToTileNumber[screenPointIndex] == tile) {
                    found = true;
                    break;
                }
                screenPointIndex++;
            }
            if (found) {
                break;
            }
        }

        this->viewportState.viewportX = (tileX - this->viewportState.mbr_0xac) * Enums::VC_TILE_PIXEL_WIDTH;
        this->viewportState.viewportY = (tileY - this->viewportState.mbr_0xb0) * Enums::VC_TILE_ROW_PIXEL_HEIGHT;
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
    }

}
}
