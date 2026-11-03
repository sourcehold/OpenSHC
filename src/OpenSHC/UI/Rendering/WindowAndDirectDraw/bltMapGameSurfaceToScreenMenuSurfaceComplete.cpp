#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/UI/Rendering/WindowAndDirectDraw.func.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00470610
        void WindowAndDirectDraw::bltMapGameSurfaceToScreenMenuSurfaceComplete()
        {
            RECT sourceRect;
            RECT destinationRect;
            sourceRect.left = DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX;
            sourceRect.top = DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY;
            sourceRect.right = DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX
                + DAT_WindowAndDirectDraw::instance.resolutionX;
            sourceRect.bottom = DAT_WindowAndDirectDraw::instance.resolutionY - 128
                + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY;
            destinationRect.bottom = DAT_WindowAndDirectDraw::instance.resolutionY - 128;
            destinationRect.right = DAT_WindowAndDirectDraw::instance.resolutionX;
            destinationRect.left = 0;
            destinationRect.top = 0;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::adjustForNotExclusiveFullscreenUnk,
                this)(&destinationRect, &sourceRect);
            this->directDrawOffscreenSurfacePointer_screenMenu->Blt(
                &destinationRect, this->directDrawOffscreenSurfacePointer_mapGame, &sourceRect, DDBLT_WAIT, NULL);
        }

    }
}
}
