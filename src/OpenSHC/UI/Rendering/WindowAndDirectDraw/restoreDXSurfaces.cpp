#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00467EC0
        BOOLEnum WindowAndDirectDraw::restoreDXSurfaces()
        {
            HRESULT _restoreResult;
            if (this->NOTSelfBufferOrWindowMode_0xf8 == TRUE) {
                if (this->directDrawPrimarySurfacePointer == NULL) {
                    return FALSE;
                }
                _restoreResult = this->directDrawPrimarySurfacePointer->Restore();
                if (_restoreResult != 0) {
                    return FALSE;
                }
            }
            if (this->directDrawBackbufferSurfacePointer != NULL
                && (_restoreResult = this->directDrawBackbufferSurfacePointer->Restore(), _restoreResult == 0)
                && this->directDrawOffscreenSurfacePointer_screenMenu != NULL
                && (_restoreResult = this->directDrawOffscreenSurfacePointer_screenMenu->Restore(),
                    _restoreResult == 0 && (this->directDrawOffscreenSurfacePointer_mapGame != NULL))
                && (_restoreResult = this->directDrawOffscreenSurfacePointer_mapGame->Restore(), _restoreResult == 0)) {
                return TRUE;
            }
            return FALSE;
        }

    }
}
}
