#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/WindowsDeviceCap.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;
        using OpenSHC::WindowsHelper::Enums::WindowsDeviceCap;

        /*
          WARNING: Enum "WindowsSystemMetricInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00467B40
        void WindowAndDirectDraw::getDeviceCapsAndSetup()
        {
            HDC__* _hdc;
            int _numOfColors;
            int _numColorPlanes;
            int _colorBitsPerPixel;
            int _screenWidth;
            int _screenHeight;
            _hdc = GetDC((HWND__*)0x0);
            _numOfColors = GetDeviceCaps(_hdc, OpenSHC::WindowsHelper::Enums::WDC_NUMCOLORS);
            if (_numOfColors == -1) {
                this->colorDepth = 0x10;
            } else {
                _numColorPlanes = GetDeviceCaps(_hdc, OpenSHC::WindowsHelper::Enums::WDC_PLANES);
                _colorBitsPerPixel = GetDeviceCaps(_hdc, OpenSHC::WindowsHelper::Enums::WDC_BITSPIXEL);
                this->colorDepth = _numColorPlanes * _colorBitsPerPixel;
            }
            ReleaseDC((HWND__*)0x0, _hdc);
            /*
              The width of the screen of the primary display monitor, in pixels. This is   the same value obtained by
              calling GetDeviceCaps as follows: GetDeviceCaps(   hdcPrimaryMonitor, HORZRES)
             */
            _screenWidth = GetSystemMetrics(SM_CXSCREEN);
            this->screenHorizontalResolutionInPixels = _screenWidth;
            /*
              The height of the screen of the primary display monitor, in pixels. This is   the same value obtained by
              calling GetDeviceCaps as follows: GetDeviceCaps(   hdcPrimaryMonitor, VERTRES).
             */
            _screenHeight = GetSystemMetrics(SM_CYSCREEN);
            /*
              Set variable, if not 16 bit. Maybe it needs to take the screen, because it   can not directly blt to a non
              15bit/16bit desktop?
             */
            this->screenVerticalResolutionInPixels = _screenHeight;
            if (this->colorDepth != 0x10) {
                this->runGameAsExclusiveFullscreen = TRUE;
            }
            /*
              Set flag, if screen resolution smaller than requested resolution.   It shall not "scale down", I think.
              -TheRedDaemon
             */
            if (this->screenHorizontalResolutionInPixels < this->gameResolutionX) {
                this->runGameAsExclusiveFullscreen = TRUE;
            }
            return;
        }

    }
}
}
