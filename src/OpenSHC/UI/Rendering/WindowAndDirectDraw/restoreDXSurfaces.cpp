#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00467EC0
        BOOLEnum WindowAndDirectDraw::restoreDXSurfaces()
        {
            HRESULT HVar1;
            if (this->NOTSelfBufferOrWindowMode_0xf8 == TRUE) {
                if (this->directDrawPrimarySurfacePointer == (IDirectDrawSurface*)0x0) {
                    return FALSE;
                }
                HVar1 = this->directDrawPrimarySurfacePointer->Restore();
                if (HVar1 != 0) {
                    return FALSE;
                }
            }
            if ((((this->directDrawBackbufferSurfacePointer != (IDirectDrawSurface*)0x0)
                     && (HVar1 = this->directDrawBackbufferSurfacePointer->Restore(), HVar1 == 0))
                    && (this->directDrawOffscreenSurfacePointer_screenMenu != (IDirectDrawSurface*)0x0))
                && (((HVar1 = this->directDrawOffscreenSurfacePointer_screenMenu->Restore(),
                         HVar1 == 0 && (this->directDrawOffscreenSurfacePointer_mapGame != (IDirectDrawSurface*)0x0))
                    && (HVar1 = this->directDrawOffscreenSurfacePointer_mapGame->Restore(), HVar1 == 0)))) {
                return TRUE;
            }
            return FALSE;
        }

    }
}
}
