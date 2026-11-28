#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00467EC0
        BOOLEnum WindowAndDirectDraw::restoreDXSurfaces()
        {
            if (this->NOTSelfBufferOrWindowMode_0xf8 == TRUE) {
                if (this->directDrawPrimarySurfacePointer == NULL) {
                    return FALSE;
                }
                if (this->directDrawPrimarySurfacePointer->Restore() != DD_OK) {
                    return FALSE;
                }
            }
            if (this->directDrawBackbufferSurfacePointer == NULL
                || this->directDrawBackbufferSurfacePointer->Restore() != DD_OK) {
                return FALSE;
            }
            if (this->directDrawOffscreenSurfacePointer_screenMenu == NULL
                || this->directDrawOffscreenSurfacePointer_screenMenu->Restore() != DD_OK) {
                return FALSE;
            }
            if (this->directDrawOffscreenSurfacePointer_mapGame == NULL
                || this->directDrawOffscreenSurfacePointer_mapGame->Restore() != DD_OK) {
                return FALSE;
            }
            return TRUE;
        }

    }
}
}
