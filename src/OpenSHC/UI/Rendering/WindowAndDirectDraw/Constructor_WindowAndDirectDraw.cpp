#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::ScreenResolutionEnum;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "WindowsSystemMetricInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004679F0
        WindowAndDirectDraw* WindowAndDirectDraw::Constructor_WindowAndDirectDraw()
        {
            int _screenHeight;
            this->runGameAsExclusiveFullscreen = TRUE;
            this->currentGameResolution = OpenSHC::Rendering::SRE_neg1;
            this->drawingReady_0x0 = FALSE;
            this->windowMoveEventBlitCountdown = 0;
            this->gameFocused = FALSE;
            this->isNotProcessingInputEvents = FALSE;
            this->unk_resetViewportRelated = 1;
            this->mbr_0xcc = 0;
            this->not_DDCAPS2_CANBOBHARDWARE_0xe0 = FALSE;
            this->screenWidthOnInit_0x10 = GetSystemMetrics(SM_CXSCREEN);
            _screenHeight = GetSystemMetrics(SM_CYSCREEN);
            this->postWindowCloseMessage = 0;
            this->pointerToIDirectDrawInterface = (IDirectDraw*)0x0;
            this->directDrawBackbufferSurfacePointer = (IDirectDrawSurface*)0x0;
            this->directDrawPrimarySurfacePointer = (IDirectDrawSurface*)0x0;
            this->directDrawOffscreenSurfacePointer_screenMenu = (IDirectDrawSurface*)0x0;
            this->directDrawOffscreenSurfacePointer_mapGame = (IDirectDrawSurface*)0x0;
            this->surfacePointer_screenMenu = (ushort*)0x0;
            this->surfacePointer_mapGame = (ushort*)0x0;
            this->field37_0xdc = 0;
            this->screenHeightOnInit_0x14 = _screenHeight;
            this->NOTSelfBufferOrWindowMode_0xf8 = TRUE;
            return this;
        }

    }
}
}
