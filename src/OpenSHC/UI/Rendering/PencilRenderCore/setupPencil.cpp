#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // The map surface is 4056 pixels wide.
        enum { MAP_SURFACE_WIDTH = 4056 };

        // FUNCTION: STRONGHOLDCRUSADER 0x00468C80
        BOOLEnum PencilRenderCore::setupPencil(int left, int top, int right, int bottom, ushort color)
        {
            this->drawColor = color;
            // Clips the corners to the surface; right and bottom are inclusive.
            if (this->surfaceTarget != OpenSHC::Rendering::Enums::RT_SCREEN_MENU) {
                if (left < 0) {
                    if (right < 0) {
                        return FALSE;
                    }
                    left = 0;
                } else if (left >= MAP_SURFACE_WIDTH) {
                    if (right >= MAP_SURFACE_WIDTH) {
                        return FALSE;
                    }
                    left = MAP_SURFACE_WIDTH - 1;
                }
                if (right < 0) {
                    right = 0;
                } else if (right >= MAP_SURFACE_WIDTH) {
                    right = MAP_SURFACE_WIDTH - 1;
                }
                if (top < DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start) {
                    if (bottom < DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start) {
                        return FALSE;
                    }
                    top = DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start;
                }
                if (top >= DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.end) {
                    if (bottom >= DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.end) {
                        return FALSE;
                    }
                    top = DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.end - 1;
                }
                if (bottom < DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start) {
                    bottom = DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start;
                }
                if (bottom >= DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.end) {
                    bottom = DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.end - 1;
                }
            } else {
                if (left < 0) {
                    if (right < 0) {
                        return FALSE;
                    }
                    left = 0;
                }
                if (left >= DAT_WindowAndDirectDraw::instance.resolutionX) {
                    if (right >= DAT_WindowAndDirectDraw::instance.resolutionX) {
                        return FALSE;
                    }
                    left = DAT_WindowAndDirectDraw::instance.resolutionX - 1;
                }
                if (right < 0) {
                    right = 0;
                }
                if (right >= DAT_WindowAndDirectDraw::instance.resolutionX) {
                    right = DAT_WindowAndDirectDraw::instance.resolutionX - 1;
                }
                if (top < DAT_TextureRenderCoreObject::instance.screenMenuSurfaceHeightRange.start) {
                    if (bottom < DAT_TextureRenderCoreObject::instance.screenMenuSurfaceHeightRange.start) {
                        return FALSE;
                    }
                    top = DAT_TextureRenderCoreObject::instance.screenMenuSurfaceHeightRange.start;
                }
                if (top >= DAT_TextureRenderCoreObject::instance.screenMenuSurfaceHeightRange.end) {
                    if (bottom >= DAT_TextureRenderCoreObject::instance.screenMenuSurfaceHeightRange.end) {
                        return FALSE;
                    }
                    top = DAT_TextureRenderCoreObject::instance.screenMenuSurfaceHeightRange.end - 1;
                }
                if (bottom < DAT_TextureRenderCoreObject::instance.screenMenuSurfaceHeightRange.start) {
                    bottom = DAT_TextureRenderCoreObject::instance.screenMenuSurfaceHeightRange.start;
                }
                if (bottom >= DAT_TextureRenderCoreObject::instance.screenMenuSurfaceHeightRange.end) {
                    bottom = DAT_TextureRenderCoreObject::instance.screenMenuSurfaceHeightRange.end - 1;
                }
            }
            if (top > bottom) {
                this->currentHeight_0x2c = top - bottom;
            } else {
                this->currentHeight_0x2c = bottom - top;
            }
            if (left > right) {
                this->currentWidth_0x28 = left - right;
            } else {
                this->currentWidth_0x28 = right - left;
            }
            this->currentX = left;
            this->currentY = top;
            if (left <= right) {
                this->moveDirectionXUnk_0x20 = 1;
            } else {
                this->moveDirectionXUnk_0x20 = -1;
            }
            if (top <= bottom) {
                this->moveDirectionYUnk_0x24 = 1;
            } else {
                this->moveDirectionYUnk_0x24 = -1;
            }
            if (left > right) {
                this->drawStartX = right;
                this->drawEndX = left;
            } else {
                this->drawStartX = left;
                this->drawEndX = right;
            }
            if (top > bottom) {
                this->drawStartY = bottom;
                this->drawEndY = top;
            } else {
                this->drawEndY = bottom;
                this->drawStartY = top;
            }
            return TRUE;
        }

    }
}
}
