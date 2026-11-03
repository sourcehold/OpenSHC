#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/UI/Rendering/WindowAndDirectDraw.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004706E0
        void WindowAndDirectDraw::bltMapGameSurfaceToScreen(
            int windowedX, int windowedY, int windowedWidth, int windowedHeigth)
        {
            if (this->drawingReady_0x0 == FALSE) {
                return;
            }
            if (GetForegroundWindow() != this->windowHandle) {
                return;
            }
            RECT sourceRect;
            RECT destinationRect;
            int const cameraOffsetX = DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX;
            if (this->NOTSelfBufferOrWindowMode_0xf8 == FALSE) {
                sourceRect.left = windowedX - 32;
                sourceRect.top = windowedY - 8;
                sourceRect.right = windowedWidth + 32;
                sourceRect.bottom = windowedHeigth + 8;
                destinationRect.top = this->clientOnScreenCoords.top
                    - DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY + sourceRect.top;
                destinationRect.bottom = this->clientOnScreenCoords.top
                    - DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY + sourceRect.bottom;
                destinationRect.left = this->clientOnScreenCoords.left - cameraOffsetX + sourceRect.left;
                destinationRect.right = this->clientOnScreenCoords.left - cameraOffsetX + sourceRect.right;
            } else {
                sourceRect.left = 0;
                sourceRect.top = 0;
                sourceRect.right = this->gameResolutionX;
                sourceRect.bottom = this->gameResolutionY;
                destinationRect.left = 0;
                destinationRect.top = 0;
                destinationRect.right = this->gameResolutionX;
                destinationRect.bottom = this->gameResolutionY;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::adjustForNotExclusiveFullscreenUnk,
                this)(&destinationRect, &sourceRect);
            this->directDrawBackbufferSurfacePointer->Blt(
                &destinationRect, this->directDrawOffscreenSurfacePointer_mapGame, &sourceRect, DDBLT_WAIT, NULL);
            if (this->NOTSelfBufferOrWindowMode_0xf8 == TRUE) {
                this->directDrawPrimarySurfacePointer->Flip(NULL, DDFLIP_WAIT);
            }
        }

    }
}
}
