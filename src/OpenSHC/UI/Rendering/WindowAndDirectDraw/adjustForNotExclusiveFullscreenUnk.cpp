#include "../WindowAndDirectDraw.func.hpp"

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
        // FUNCTION: STRONGHOLDCRUSADER 0x00467E50
        void WindowAndDirectDraw::adjustForNotExclusiveFullscreenUnk(LPRECT destinationRect, LPRECT sourceRect)
        {
            int _screenWidth;
            int _screenHeight;
            if (this->runGameAsExclusiveFullscreen == FALSE) {
                _screenWidth = GetSystemMetrics(SM_CXSCREEN);
                _screenHeight = GetSystemMetrics(SM_CYSCREEN);
                if (destinationRect->left < 0) {
                    sourceRect->left = sourceRect->left - destinationRect->left;
                    destinationRect->left = 0;
                }
                if (destinationRect->top < 0) {
                    sourceRect->top = sourceRect->top - destinationRect->top;
                    destinationRect->top = 0;
                }
                if (_screenWidth < destinationRect->right) {
                    sourceRect->right = sourceRect->right + (_screenWidth - destinationRect->right);
                    destinationRect->right = _screenWidth;
                }
                if (_screenHeight < destinationRect->bottom) {
                    sourceRect->bottom = sourceRect->bottom + (_screenHeight - destinationRect->bottom);
                    destinationRect->bottom = _screenHeight;
                }
            }
        }

    }
}
}
