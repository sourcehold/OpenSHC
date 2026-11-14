#include "../ViewportRenderState.func.hpp"

#include "OpenSHC/Map/MapConstants.hpp"
#include "OpenSHC/Rendering/Enums/ViewportConstants.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace Rendering {

    using OpenSHC::Rendering::ScreenResolutionEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004E5C00
    void ViewportRenderState::setViewportBasedOnMapSize()
    {
        int mapBorder = Map::MC_MAP_SIZE_400 - DAT_TileMapState::instance.mapSize;
        if (mapBorder == Map::MC_MAP_SIZE_400) {
            mapBorder = 0;
        }
        mapBorder /= 2;

        int maxViewportX = (((Map::MC_MAP_SIZE_400 - mapBorder) / 2 - this->viewportState.viewportHeight) + 4)
            * Enums::VC_TILE_PIXEL_WIDTH;
        int maxViewportY = ((Map::MC_MAP_SIZE_400 + 1 - this->viewportState.viewportWidth) - mapBorder)
            * Enums::VC_TILE_ROW_PIXEL_HEIGHT;
        int minViewportX = (mapBorder / 2 + 1) * Enums::VC_TILE_PIXEL_WIDTH;
        int minViewportY = mapBorder * Enums::VC_TILE_ROW_PIXEL_HEIGHT + Enums::VC_TILE_PIXEL_HEIGHT;
        if (this->viewportState.isZoomedOutUnk != 0) {
            minViewportX = (mapBorder / 2 - 4) * Enums::VC_TILE_PIXEL_WIDTH;
        }

        if (this->viewportState.viewportX < minViewportX) {
            this->viewportState.viewportX = minViewportX;
        }
        if (this->viewportState.viewportX > maxViewportX) {
            this->viewportState.viewportX = maxViewportX;
        }
        if (this->viewportState.viewportY < minViewportY) {
            this->viewportState.viewportY = minViewportY;
        }
        if (this->viewportState.viewportY > maxViewportY) {
            this->viewportState.viewportY = maxViewportY;
        }

        if (DAT_TileMapState::instance.mapOrientation != Map::MC_MAP_NORTH) {
            if (DAT_TileMapState::instance.mapOrientation == Map::MC_MAP_WEST) {
                if (this->viewportState.viewportX > maxViewportX - Enums::VC_TILE_PIXEL_WIDTH) {
                    this->viewportState.viewportX = maxViewportX - Enums::VC_TILE_PIXEL_WIDTH;
                }
            } else if (DAT_TileMapState::instance.mapOrientation == Map::MC_MAP_SOUTH) {
                if (this->viewportState.viewportY < minViewportY + Enums::VC_TILE_ROW_PIXEL_HEIGHT) {
                    this->viewportState.viewportY = minViewportY + Enums::VC_TILE_ROW_PIXEL_HEIGHT;
                }
                if (this->viewportState.viewportY > maxViewportY - Enums::VC_TILE_ROW_PIXEL_HEIGHT) {
                    this->viewportState.viewportY = maxViewportY - Enums::VC_TILE_ROW_PIXEL_HEIGHT;
                }
            } else if (DAT_TileMapState::instance.mapOrientation == Map::MC_MAP_EAST) {
                if (this->viewportState.viewportX < minViewportX + Enums::VC_TILE_PIXEL_WIDTH / 2) {
                    this->viewportState.viewportX = minViewportX + Enums::VC_TILE_PIXEL_WIDTH / 2;
                }
                if (this->viewportState.viewportY > maxViewportY - Enums::VC_TILE_ROW_PIXEL_HEIGHT) {
                    this->viewportState.viewportY = maxViewportY - Enums::VC_TILE_ROW_PIXEL_HEIGHT;
                }
            }
        }

        if (DAT_TileMapState::instance.mapSize == Map::MC_MAP_SIZE_160
            && DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768
            && this->viewportState.isZoomedOutUnk != 0) {
            minViewportY -= 10;
            maxViewportY -= 10;
        }

        if (minViewportX > maxViewportX) {
            this->viewportState.viewportX = (minViewportX - maxViewportX) / 2 + maxViewportX;
        }
        if (minViewportY > maxViewportY) {
            this->viewportState.viewportY = (minViewportY - maxViewportY) / 2 + maxViewportY;
        }

        if (this->viewportState.isZoomedOutUnk == 0) {
            this->viewportState.currentCameraOffsetX
                = (DAT_ViewportRenderState::instance.viewportState.viewportX & (Enums::VC_TILE_PIXEL_WIDTH - 1))
                + Enums::VC_MAP_SURFACE_MARGIN_X;
            this->viewportState.currentCameraOffsetY
                = (DAT_ViewportRenderState::instance.viewportState.viewportY & (Enums::VC_TILE_PIXEL_HEIGHT - 1))
                + Enums::VC_TILE_ROW_PIXEL_HEIGHT;
        } else {
            this->viewportState.currentCameraOffsetX = (DAT_ViewportRenderState::instance.viewportState.viewportX >> 1
                                                           & (Enums::VC_TILE_PIXEL_WIDTH / 2 - 1))
                + Enums::VC_MAP_SURFACE_MARGIN_X;
            this->viewportState.currentCameraOffsetY = (DAT_ViewportRenderState::instance.viewportState.viewportY >> 1
                                                           & (Enums::VC_TILE_PIXEL_HEIGHT / 2 - 1))
                + Enums::VC_TILE_ROW_PIXEL_HEIGHT;
        }
        this->viewportState.currentCameraOffsetY += Enums::VC_TILE_ROW_PIXEL_HEIGHT;
    }

}
}
