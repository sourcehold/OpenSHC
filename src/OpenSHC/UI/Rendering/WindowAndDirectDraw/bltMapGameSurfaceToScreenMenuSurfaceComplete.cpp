#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/UI/Rendering/WindowAndDirectDraw.func.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00470610
        void WindowAndDirectDraw::bltMapGameSurfaceToScreenMenuSurfaceComplete()
        {
            tagRECT _sourceRect;
            tagRECT _destinationRect;
            _sourceRect.left = DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX;
            _sourceRect.right = DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX
                + DAT_WindowAndDirectDraw::instance.resolutionX;
            _sourceRect.top = DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY;
            _sourceRect.bottom = DAT_WindowAndDirectDraw::instance.resolutionY + -0x80
                + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY;
            _destinationRect.bottom = DAT_WindowAndDirectDraw::instance.resolutionY + -0x80;
            _destinationRect.right = DAT_WindowAndDirectDraw::instance.resolutionX;
            _destinationRect.left = 0;
            _destinationRect.top = 0;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::adjustForNotExclusiveFullscreenUnk,
                this)(&_destinationRect, &_sourceRect);
            DAT_WindowAndDirectDraw::instance.directDrawOffscreenSurfacePointer_screenMenu->Blt(&_destinationRect,
                DAT_WindowAndDirectDraw::instance.directDrawOffscreenSurfacePointer_mapGame, &_sourceRect, 0x1000000,
                (LPDDBLTFX)0x0);
        }

    }
}
}
