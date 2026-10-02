#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/UI/Rendering/WindowAndDirectDraw.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "WindowsSystemMetricInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004708F0
        void WindowAndDirectDraw::reinitWindow()
        {
            HWND__* hWnd;
            HWND__* _currentForegroundWindow;
            int yBottom;
            int xRight;
            hWnd = this->windowHandle;
            _currentForegroundWindow = GetForegroundWindow();
            if (_currentForegroundWindow == hWnd) {
                this->isNotProcessingInputEvents = FALSE;
                if (this->runGameAsExclusiveFullscreen != FALSE) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::prepareWindowAndDDrawUnk, this)();
                    yBottom = GetSystemMetrics(SM_CYSCREEN);
                    xRight = GetSystemMetrics(SM_CXSCREEN);
                    SetRect(&this->clientOnScreenCoords, 0, 0, xRight, yBottom);
                    SetFocus(this->windowHandle);
                }
                GetClientRect(hWnd, &this->clientOnScreenCoords);
                ClientToScreen(this->windowHandle, (LPPOINT)((int)((tagPOINT*)&this->clientOnScreenCoords)));
                ClientToScreen(this->windowHandle, (LPPOINT)((int)((tagPOINT*)&this->clientOnScreenCoords.right)));
                UpdateWindow(this->windowHandle);
                SetFocus(this->windowHandle);
            }
        }

    }
}
}
