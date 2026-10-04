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

        // NOTE: The copy loop is hand-written assembly in the original: it keeps the colour key in
        //   the 16-bit half of a callee-saved register and compares with cmp ax,bx, and reloads
        //   every loop-carried value from its stack slot at the loop it belongs to. That is also
        //   why the function has a frame pointer.
        //
        //   Each record of the overlap table holds x, y, width and height as four consecutive
        //   ints, and the four running pointers walk them a record at a time. A record whose x is
        //   -2 is a resolution marker: at 800x600 there is nothing to move, otherwise it is
        //   skipped and the next record used. -1 terminates the table.

        // FUNCTION: STRONGHOLDCRUSADER 0x00454F00
        void TextureRenderCore::moveOverlappingMenuPartsToMapSurface()
        {
            int* _yPosPtr;
            int* _hightPtr;
            int* _widthPtr;
            int* _xPosPtr;
            int _mapLineJump;
            int _screenLineJump;
            int _width;
            int _height;
            ushort* _mapSurfacePtr;
            ushort* _screenSurfacePtr;
            ushort _ignoreColor;
            int _recordIndex;
            if (this->activeMenuTabIndex == 0) {
                return;
            }
            _recordIndex = (this->activeMenuTabIndex - 1) * 0x28;
            if (DAT_BlendingDefinedData::instance.field166_0x2dfc[_recordIndex + 0x86] == -1) {
                return;
            }
            _recordIndex = (this->activeMenuTabIndex - 1) * 0x28;
            _widthPtr = DAT_BlendingDefinedData::instance.field166_0x2dfc + _recordIndex + 0x88;
            _yPosPtr = DAT_BlendingDefinedData::instance.field166_0x2dfc + _recordIndex + 0x87;
            _xPosPtr = DAT_BlendingDefinedData::instance.field166_0x2dfc + _recordIndex + 0x86;
            _hightPtr = DAT_BlendingDefinedData::instance.field166_0x2dfc + _recordIndex + 0x89;
            do {
                _ignoreColor = COL_MAGENTA::instance.shortValue;
                if (*_xPosPtr == -2) {
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
                        return;
                    }
                    _yPosPtr = _yPosPtr + 4;
                    _hightPtr = _hightPtr + 4;
                    _widthPtr = _widthPtr + 4;
                    _xPosPtr = _xPosPtr + 4;
                }
                _screenSurfacePtr = (ushort*)((int)DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu
                    + (*_yPosPtr + DAT_MenuHandlerState::instance.y)
                        * DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine
                    + (DAT_MenuHandlerState::instance.x + *_xPosPtr) * 2);
                _mapSurfacePtr = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame
                    + (*_yPosPtr + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY
                          + DAT_MenuHandlerState::instance.y)
                        * 0xfd8
                    + *_xPosPtr + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX
                    + DAT_MenuHandlerState::instance.x;
                _width = *_widthPtr;
                _mapLineJump = (0xfd8 - _width) * 2;
                _screenLineJump = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine - _width * 2;
                _height = *_hightPtr;
                __asm {
                    mov esi, _screenSurfacePtr
                    mov edi, _mapSurfacePtr
                    mov ecx, _height
                    mov bx, word ptr _ignoreColor
                rowLoop:
                    mov edx, _width
                pixelLoop:
                    mov ax, word ptr [esi]
                    cmp ax, bx
                    je skipPixel
                    mov word ptr [edi], ax
                skipPixel:
                    add esi, 2
                    add edi, 2
                    sub edx, 1
                    jne pixelLoop
                    add esi, _screenLineJump
                    add edi, _mapLineJump
                    sub ecx, 1
                    jne rowLoop
                }
                _yPosPtr = _yPosPtr + 4;
                _hightPtr = _hightPtr + 4;
                _widthPtr = _widthPtr + 4;
                _xPosPtr = _xPosPtr + 4;
            } while (*_xPosPtr != -1);
        }

    }
}
}
