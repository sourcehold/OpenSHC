#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00467D80
        void WindowAndDirectDraw::releaseSurfacesAndDirectDraw(BOOLEnum alsoReleaseDDInterfaceUnk)
        {
            this->drawingReady_0x0 = FALSE;
            if ((alsoReleaseDDInterfaceUnk != FALSE) && (this->pointerToIDirectDrawInterface != (IDirectDraw*)0x0)) {
                /*
                  Signature overwrite
                 */
                this->pointerToIDirectDrawInterface->SetCooperativeLevel(this->windowHandle, 8);
            }
            if (this->directDrawOffscreenSurfacePointer_screenMenu != (IDirectDrawSurface*)0x0) {
                /*
                  Signature overwrite
                 */
                this->directDrawOffscreenSurfacePointer_screenMenu->Release();
                this->directDrawOffscreenSurfacePointer_screenMenu = (IDirectDrawSurface*)0x0;
            }
            if (this->directDrawOffscreenSurfacePointer_mapGame != (IDirectDrawSurface*)0x0) {
                /*
                  Signature overwrite
                 */
                this->directDrawOffscreenSurfacePointer_mapGame->Release();
                this->directDrawOffscreenSurfacePointer_mapGame = (IDirectDrawSurface*)0x0;
            }
            if (this->directDrawBackbufferSurfacePointer != (IDirectDrawSurface*)0x0) {
                /*
                  Signature overwrite
                 */
                this->directDrawBackbufferSurfacePointer->Release();
                this->directDrawBackbufferSurfacePointer = (IDirectDrawSurface*)0x0;
            }
            if (this->directDrawPrimarySurfacePointer != (IDirectDrawSurface*)0x0) {
                /*
                  Signature overwrite
                 */
                this->directDrawPrimarySurfacePointer->Release();
                this->directDrawPrimarySurfacePointer = (IDirectDrawSurface*)0x0;
            }
            this->surfacePointer_screenMenu = (ushort*)0x0;
            if ((alsoReleaseDDInterfaceUnk != FALSE) && (this->pointerToIDirectDrawInterface != (IDirectDraw*)0x0)) {
                /*
                  Signature overwrite
                 */
                this->pointerToIDirectDrawInterface->Release();
                this->pointerToIDirectDrawInterface = (IDirectDraw*)0x0;
            }
        }

    }
}
}
