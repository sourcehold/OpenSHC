#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00468C80
        BOOLEnum PencilRenderCore::setupPencil(int left, int top, int right, int bottom, ushort color)
        {
            dword _drawHeight;
            dword _drawWidth;
            int _heightRangeEnd;
            dword _heightRangeStart;
            /*
              Reads like "right" and "bottom" are inclusive. Unlike the Windows RECT   definition used in DirectDraw (x,
              y, width, height).   Could also be that I am misinterpreting. -TheRedDaemon
             */
            this->drawColor = color;
            if (this->surfaceTarget == OpenSHC::Rendering::Enums::RT_SCREEN_MENU) {
                if (left < 0) {
                    if (right < 0) {
                        return FALSE;
                    }
                    left = 0;
                }
                if (DAT_WindowAndDirectDraw::instance.resolutionX <= left) {
                    if (DAT_WindowAndDirectDraw::instance.resolutionX <= right) {
                        return FALSE;
                    }
                    left = DAT_WindowAndDirectDraw::instance.resolutionX - 1;
                }
                if (right < 0) {
                    right = 0;
                }
                _heightRangeStart = DAT_TextureRenderCoreObject::instance.screenMenuSurfaceHeightRange.start;
                _heightRangeEnd = DAT_TextureRenderCoreObject::instance.screenMenuSurfaceHeightRange.end;
                if (DAT_WindowAndDirectDraw::instance.resolutionX <= right) {
                    right = DAT_WindowAndDirectDraw::instance.resolutionX - 1;
                }
            } else {
                if (left < 0) {
                    if (right < 0) {
                        return FALSE;
                    }
                    left = 0;
                } else if (4056 < left) {
                    if (4056 < right) {
                        return FALSE;
                    }
                    left = 4055;
                }
                _heightRangeStart = DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start;
                _heightRangeEnd = DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.end;
                if (right < 0) {
                    right = 0;
                } else if (4056 < right) {
                    right = 4055;
                }
            }
            if ((top < (int)_heightRangeStart) && (top = _heightRangeStart, bottom < (int)_heightRangeStart)) {
                return FALSE;
            }
            if (_heightRangeEnd <= top) {
                if (_heightRangeEnd <= bottom) {
                    return FALSE;
                }
                top = _heightRangeEnd - 1;
            }
            if (bottom < (int)_heightRangeStart) {
                bottom = _heightRangeStart;
            }
            if (_heightRangeEnd <= bottom) {
                bottom = _heightRangeEnd - 1;
            }
            if (bottom < top) {
                _drawHeight = top - bottom;
            } else {
                _drawHeight = bottom - top;
            }
            this->currentHeight_0x2c = _drawHeight;
            if (right < left) {
                _drawWidth = left - right;
            } else {
                _drawWidth = right - left;
            }
            this->currentWidth_0x28 = _drawWidth;
            this->currentX = left;
            this->currentY = top;
            this->moveDirectionXUnk_0x20 = (uint)(left <= right) * 2 - 1;
            this->moveDirectionYUnk_0x24 = (uint)(top <= bottom) * 2 - 1;
            this->drawStartX = left;
            this->drawEndX = right;
            if (right < left) {
                this->drawStartX = right;
                this->drawEndX = left;
            }
            if (bottom < top) {
                this->drawStartY = bottom;
                this->drawEndY = top;
                return TRUE;
            }
            this->drawEndY = bottom;
            this->drawStartY = top;
            return TRUE;
        }

    }
}
}
