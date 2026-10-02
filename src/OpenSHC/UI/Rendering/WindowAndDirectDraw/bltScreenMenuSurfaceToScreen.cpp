#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/UI/Rendering/WindowAndDirectDraw.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004707F0
        void WindowAndDirectDraw::bltScreenMenuSurfaceToScreen(
            int windowedX, int windowedY, int windowedWidth, int windowedHeigth)
        {
            HWND__* _windowHandle;
            tagRECT _sourceRect;
            tagRECT _destinationRect;
            if (this->drawingReady_0x0 != FALSE) {
                _windowHandle = GetForegroundWindow();
                if (_windowHandle == this->windowHandle) {
                    if (this->NOTSelfBufferOrWindowMode_0xf8 == FALSE) {
                        _sourceRect.left = windowedX + -0x20;
                        _sourceRect.top = windowedY + -8;
                        _sourceRect.right = windowedWidth + 0x20;
                        _sourceRect.bottom = windowedHeigth + 8;
                        _destinationRect.left = this->clientOnScreenCoords.left + -0x20 + windowedX;
                        _destinationRect.top = this->clientOnScreenCoords.top + -8 + windowedY;
                        _destinationRect.right = this->clientOnScreenCoords.left + 0x20 + windowedWidth;
                        _destinationRect.bottom = this->clientOnScreenCoords.top + 8 + windowedHeigth;
                    } else {
                        _sourceRect.left = 0;
                        _sourceRect.top = 0;
                        _sourceRect.right = this->gameResolutionX;
                        _sourceRect.bottom = this->gameResolutionY;
                        _destinationRect.left = 0;
                        _destinationRect.top = 0;
                        _destinationRect.right = this->gameResolutionX;
                        _destinationRect.bottom = this->gameResolutionY;
                    }
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::adjustForNotExclusiveFullscreenUnk, this)(
                        &_destinationRect, &_sourceRect);
                    /*
                      Normal waiting blt. --TheRedDaemon
                     */
                    this->directDrawBackbufferSurfacePointer->Blt(&_destinationRect,
                        this->directDrawOffscreenSurfacePointer_screenMenu, &_sourceRect, 0x1000000, (LPDDBLTFX)0x0);
                    if (this->NOTSelfBufferOrWindowMode_0xf8 == TRUE) {
                        this->directDrawPrimarySurfacePointer->Flip((IDirectDrawSurface*)0x0, 1);
                    }
                }
            }
        }

    }
}
}
