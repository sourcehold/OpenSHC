#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x004708F0
        void WindowAndDirectDraw::reinitWindow()
        {
            HWND const window = this->windowHandle;
            if (GetForegroundWindow() != window) {
                return;
            }
            this->isNotProcessingInputEvents = FALSE;
            if (DAT_WindowAndDirectDraw::instance.runGameAsExclusiveFullscreen) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::prepareWindowAndDDrawUnk, this)();
                SetRect(
                    &this->clientOnScreenCoords, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
                SetFocus(this->windowHandle);
                return;
            }
            GetClientRect(window, &this->clientOnScreenCoords);
            ClientToScreen(this->windowHandle, (LPPOINT) & this->clientOnScreenCoords.left);
            ClientToScreen(this->windowHandle, (LPPOINT) & this->clientOnScreenCoords.right);
            UpdateWindow(this->windowHandle);
            SetFocus(this->windowHandle);
        }

    }
}
}
