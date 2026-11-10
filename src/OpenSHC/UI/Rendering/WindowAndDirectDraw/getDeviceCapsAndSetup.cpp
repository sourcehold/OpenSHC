#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/WindowsDeviceCap.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00467B40
        void WindowAndDirectDraw::getDeviceCapsAndSetup()
        {
            HDC hdc = GetDC(NULL);
            if (GetDeviceCaps(hdc, OpenSHC::WindowsHelper::Enums::WDC_NUMCOLORS) == -1) {
                this->colorDepth = 16;
            } else {
                this->colorDepth = GetDeviceCaps(hdc, OpenSHC::WindowsHelper::Enums::WDC_PLANES)
                    * GetDeviceCaps(hdc, OpenSHC::WindowsHelper::Enums::WDC_BITSPIXEL);
            }
            ReleaseDC(NULL, hdc);
            // The same values as GetDeviceCaps(hdcPrimaryMonitor, HORZRES) and VERTRES.
            this->screenHorizontalResolutionInPixels = GetSystemMetrics(SM_CXSCREEN);
            this->screenVerticalResolutionInPixels = GetSystemMetrics(SM_CYSCREEN);
            // Set variable, if not 16 bit. Maybe it needs to take the screen, because it can not directly blt to a non
            // 15bit/16bit desktop?
            if (this->colorDepth != 16) {
                this->runGameAsExclusiveFullscreen = TRUE;
            }
            // Set flag, if screen resolution smaller than requested resolution. It shall not "scale down", I think.
            // -TheRedDaemon
            if (this->gameResolutionX > this->screenHorizontalResolutionInPixels) {
                this->runGameAsExclusiveFullscreen = TRUE;
            }
        }

    }
}
}
