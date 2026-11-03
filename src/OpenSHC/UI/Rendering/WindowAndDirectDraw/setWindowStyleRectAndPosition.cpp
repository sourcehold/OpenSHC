#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/Rendering/WindowInformation.func.hpp"

#include "OpenSHC/Globals/DAT_WindowInformation.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x0046F750
        void WindowAndDirectDraw::setWindowStyleRectAndPosition()
        {
            // Exclusive fullscreen is a bare pop-up; otherwise a window with a title bar, system menu and minimise box.
            DWORD style;
            if (this->runGameAsExclusiveFullscreen) {
                style = WS_POPUP;
            } else {
                style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
            }
            style |= WS_VISIBLE;
            SetWindowLongA(this->windowHandle, GWL_STYLE, style);
            RECT windowRect;
            SetRect(&windowRect, 0, 0, this->resolutionX, this->resolutionY);
            AdjustWindowRect(&windowRect, style, FALSE);
            MACRO_CALL_MEMBER(OpenSHC::Rendering::WindowInformation_Func::storeWindowRectangleInfoUnk,
                DAT_WindowInformation::ptr)(0, 0, this->resolutionX, this->resolutionY);
            if (this->runGameAsExclusiveFullscreen) {
                SetRect(
                    &this->clientOnScreenCoords, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
            } else {
                SetRect(&this->clientOnScreenCoords, 0, 0, this->resolutionX, this->resolutionY);
            }
            this->gameInWindowPosX_0x30 = windowRect.right - this->resolutionX - windowRect.left;
            this->gameInWindowPosY_0x34 = windowRect.bottom - windowRect.top - this->resolutionY;
            this->gameOnScreenPosX_0x28 = (this->screenHorizontalResolutionInPixels - this->gameResolutionX) / 2;
            this->gameOnScreenPosY_0x2c = (this->screenVerticalResolutionInPixels - this->gameResolutionY) / 2 - 20;
            SetWindowPos(this->windowHandle, HWND_NOTOPMOST, this->gameOnScreenPosX_0x28 - windowRect.left,
                this->gameOnScreenPosY_0x2c - windowRect.top, windowRect.right - windowRect.left,
                windowRect.bottom - windowRect.top, SWP_NOACTIVATE);
            UpdateWindow(this->windowHandle);
            SetFocus(this->windowHandle);
        }

    }
}
}
