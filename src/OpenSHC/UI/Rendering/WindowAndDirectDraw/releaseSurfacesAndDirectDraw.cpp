#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00467D80
        void WindowAndDirectDraw::releaseSurfacesAndDirectDraw(BOOLEnum alsoReleaseDDInterfaceUnk)
        {
            this->drawingReady_0x0 = FALSE;
            if (alsoReleaseDDInterfaceUnk && this->pointerToIDirectDrawInterface != NULL) {
                this->pointerToIDirectDrawInterface->SetCooperativeLevel(this->windowHandle, 8);
            }
            if (this->directDrawOffscreenSurfacePointer_screenMenu != NULL) {
                this->directDrawOffscreenSurfacePointer_screenMenu->Release();
                this->directDrawOffscreenSurfacePointer_screenMenu = NULL;
            }
            if (this->directDrawOffscreenSurfacePointer_mapGame != NULL) {
                this->directDrawOffscreenSurfacePointer_mapGame->Release();
                this->directDrawOffscreenSurfacePointer_mapGame = NULL;
            }
            if (this->directDrawBackbufferSurfacePointer != NULL) {
                this->directDrawBackbufferSurfacePointer->Release();
                this->directDrawBackbufferSurfacePointer = NULL;
            }
            if (this->directDrawPrimarySurfacePointer != NULL) {
                this->directDrawPrimarySurfacePointer->Release();
                this->directDrawPrimarySurfacePointer = NULL;
            }
            this->surfacePointer_screenMenu = NULL;
            if (alsoReleaseDDInterfaceUnk && this->pointerToIDirectDrawInterface != NULL) {
                this->pointerToIDirectDrawInterface->Release();
                this->pointerToIDirectDrawInterface = NULL;
            }
        }

    }
}
}
