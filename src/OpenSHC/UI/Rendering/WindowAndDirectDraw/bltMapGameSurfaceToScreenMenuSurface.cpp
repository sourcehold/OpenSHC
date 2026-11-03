#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/UI/Rendering/WindowAndDirectDraw.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x004706A0
        void WindowAndDirectDraw::bltMapGameSurfaceToScreenMenuSurface(RECT sourceRect, RECT destinationRect)
        {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::adjustForNotExclusiveFullscreenUnk,
                this)(&destinationRect, &sourceRect);
            this->directDrawOffscreenSurfacePointer_screenMenu->Blt(&destinationRect,
                this->directDrawOffscreenSurfacePointer_mapGame, &sourceRect, 0x1000000, (LPDDBLTFX)0x0);
        }

    }
}
}
