#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace Rendering {

    using OpenSHC::Rendering::ScreenResolutionEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004E5C00
    void ViewportRenderState::setViewportBasedOnMapSize()
    {
        int mapBorder = 400 - DAT_TileMapState::instance.mapSize;
        if (mapBorder == 400) {
            mapBorder = 0;
        }
        mapBorder = mapBorder / 2;

        int maxViewportX = (((400 - mapBorder) / 2 - this->viewportState.viewportHeight) + 4) * 0x20;
        int maxViewportY = ((401 - this->viewportState.viewportWidth) - mapBorder) * 8;
        int minViewportX = mapBorder / 2 + 1;
        int minViewportY = mapBorder * 8 + 0x10;
        if (this->viewportState.isZoomedOutUnk != 0) {
            minViewportX = mapBorder / 2 + -4;
        }
        minViewportX = minViewportX * 0x20;

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

        if (DAT_TileMapState::instance.mapOrientation != 0) {
            if (DAT_TileMapState::instance.mapOrientation == 6) {
                if (this->viewportState.viewportX > maxViewportX + -0x20) {
                    this->viewportState.viewportX = maxViewportX + -0x20;
                }
            } else if (DAT_TileMapState::instance.mapOrientation == 4) {
                if (this->viewportState.viewportY < minViewportY + 8) {
                    this->viewportState.viewportY = minViewportY + 8;
                }
                if (this->viewportState.viewportY > maxViewportY + -8) {
                    this->viewportState.viewportY = maxViewportY + -8;
                }
            } else if (DAT_TileMapState::instance.mapOrientation == 2) {
                if (this->viewportState.viewportX < minViewportX + 0x10) {
                    this->viewportState.viewportX = minViewportX + 0x10;
                }
                if (this->viewportState.viewportY > maxViewportY + -8) {
                    this->viewportState.viewportY = maxViewportY + -8;
                }
            }
        }

        if (DAT_TileMapState::instance.mapSize == 160
            && DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768
            && this->viewportState.isZoomedOutUnk != 0) {
            minViewportY = minViewportY - 10;
            maxViewportY = maxViewportY + -10;
        }

        if (maxViewportX < minViewportX) {
            this->viewportState.viewportX = (minViewportX - maxViewportX) / 2 + maxViewportX;
        }
        if (maxViewportY < minViewportY) {
            this->viewportState.viewportY = (minViewportY - maxViewportY) / 2 + maxViewportY;
        }

        if (this->viewportState.isZoomedOutUnk == 0) {
            this->viewportState.currentCameraOffsetX = (this->viewportState.viewportX & 0x1fU) + 150;
            this->viewportState.currentCameraOffsetY = (this->viewportState.viewportY & 0xfU) + 0x10;
            return;
        }
        this->viewportState.currentCameraOffsetX = (this->viewportState.viewportX >> 1 & 0xfU) + 150;
        this->viewportState.currentCameraOffsetY = (this->viewportState.viewportY >> 1 & 7U) + 0x10;
    }

}
}
