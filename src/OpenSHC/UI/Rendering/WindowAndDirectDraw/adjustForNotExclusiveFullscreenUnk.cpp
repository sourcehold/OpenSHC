#include "../WindowAndDirectDraw.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00467E50
        void WindowAndDirectDraw::adjustForNotExclusiveFullscreenUnk(LPRECT destinationRect, LPRECT sourceRect)
        {
            if (this->runGameAsExclusiveFullscreen) {
                return;
            }
            int const screenWidth = GetSystemMetrics(SM_CXSCREEN);
            int const screenHeight = GetSystemMetrics(SM_CYSCREEN);
            if (destinationRect->left < 0) {
                sourceRect->left -= destinationRect->left;
                destinationRect->left = 0;
            }
            if (destinationRect->top < 0) {
                sourceRect->top -= destinationRect->top;
                destinationRect->top = 0;
            }
            if (destinationRect->right > screenWidth) {
                sourceRect->right += (screenWidth - destinationRect->right);
                destinationRect->right = screenWidth;
            }
            if (destinationRect->bottom > screenHeight) {
                sourceRect->bottom += (screenHeight - destinationRect->bottom);
                destinationRect->bottom = screenHeight;
            }
        }

    }
}
}
