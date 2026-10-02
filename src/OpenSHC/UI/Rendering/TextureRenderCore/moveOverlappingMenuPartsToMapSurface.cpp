#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"

#include "OpenSHC/Globals/COL_MAGENTA.hpp"
#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::ScreenResolutionEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00454F00
        void TextureRenderCore::moveOverlappingMenuPartsToMapSurface()
        {
            int _lineJumpBytes;
            int _height;
            int _runWidth;
            ushort* _screenSurfacePtr;
            ushort* _mapSurfacePtr;
            int* _xPosPtr;
            int* _widthPtr;
            int* _hightPtr;
            int* _yPosPtr;
            undefined2 _ignoreColor;
            int _width;
            if ((this->activeMenuTabIndex != 0)
                && (DAT_BlendingDefinedData::instance.field166_0x2dfc[this->activeMenuTabIndex * 0x28 + 0x5e] != -1)) {
                _widthPtr = DAT_BlendingDefinedData::instance.field166_0x2dfc + this->activeMenuTabIndex * 0x28 + 0x60;
                _xPosPtr = DAT_BlendingDefinedData::instance.field166_0x2dfc + this->activeMenuTabIndex * 0x28 + 0x5e;
                _hightPtr = DAT_BlendingDefinedData::instance.field166_0x2dfc + this->activeMenuTabIndex * 0x28 + 0x61;
                _yPosPtr = DAT_BlendingDefinedData::instance.field166_0x2dfc + this->activeMenuTabIndex * 0x28 + 0x5f;
                do {
                    _ignoreColor = COL_MAGENTA::instance.shortValue;
                    if (*_xPosPtr == -2) {
                        if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            == OpenSHC::Rendering::SRE_800x600) {}
                        _yPosPtr = _yPosPtr + 4;
                        _hightPtr = _hightPtr + 4;
                        _widthPtr = _widthPtr + 4;
                        _xPosPtr = _xPosPtr + 4;
                    }
                    _screenSurfacePtr = (ushort*)((int)DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu
                        + (DAT_MenuHandlerState::instance.x + *_xPosPtr) * 2
                        + (*_yPosPtr + DAT_MenuHandlerState::instance.y)
                            * DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine);
                    _mapSurfacePtr = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame
                        + (*_yPosPtr + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY
                              + DAT_MenuHandlerState::instance.y)
                            * 0xfd8
                        + *_xPosPtr + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX
                        + DAT_MenuHandlerState::instance.x;
                    _width = *_widthPtr;
                    _lineJumpBytes = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine + _width * -2;
                    _height = *_hightPtr;
                    _runWidth = _width;
                    do {
                        do {
                            if (*_screenSurfacePtr != _ignoreColor) {
                                *_mapSurfacePtr = *_screenSurfacePtr;
                            }
                            _screenSurfacePtr = _screenSurfacePtr + 1;
                            _mapSurfacePtr = _mapSurfacePtr + 1;
                            _runWidth = _runWidth + -1;
                        } while (_runWidth != 0);
                        _screenSurfacePtr = (ushort*)((int)_screenSurfacePtr + _lineJumpBytes);
                        _mapSurfacePtr = _mapSurfacePtr + (0xfd8 - _width);
                        _height = _height + -1;
                        _runWidth = _width;
                    } while (_height != 0);
                    _yPosPtr = _yPosPtr + 4;
                    _hightPtr = _hightPtr + 4;
                    _widthPtr = _widthPtr + 4;
                    _xPosPtr = _xPosPtr + 4;
                } while (*_xPosPtr != -1);
            }
        }

    }
}
}
