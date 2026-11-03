#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00467E50
        void WindowAndDirectDraw::adjustForNotExclusiveFullscreenUnk(LPRECT destinationRect, LPRECT sourceRect)
        {
            if (this->runGameAsExclusiveFullscreen == FALSE) {
                int _screenWidth = GetSystemMetrics(SM_CXSCREEN);
                int _screenHeight = GetSystemMetrics(SM_CYSCREEN);
                if (destinationRect->left < 0) {
                    sourceRect->left = sourceRect->left - destinationRect->left;
                    destinationRect->left = 0;
                }
                if (destinationRect->top < 0) {
                    sourceRect->top = sourceRect->top - destinationRect->top;
                    destinationRect->top = 0;
                }
                if (destinationRect->right > _screenWidth) {
                    sourceRect->right = sourceRect->right + (_screenWidth - destinationRect->right);
                    destinationRect->right = _screenWidth;
                }
                if (destinationRect->bottom > _screenHeight) {
                    sourceRect->bottom = sourceRect->bottom + (_screenHeight - destinationRect->bottom);
                    destinationRect->bottom = _screenHeight;
                }
            }
        }

    }
}
}
