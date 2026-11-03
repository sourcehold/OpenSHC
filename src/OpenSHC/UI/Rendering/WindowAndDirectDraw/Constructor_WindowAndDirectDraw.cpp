#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::ScreenResolutionEnum;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004679F0
        WindowAndDirectDraw* WindowAndDirectDraw::Constructor_WindowAndDirectDraw()
        {
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
            int _screenHeight = GetSystemMetrics(SM_CYSCREEN);
            this->postWindowCloseMessage = 0;
            this->pointerToIDirectDrawInterface = NULL;
            this->directDrawBackbufferSurfacePointer = NULL;
            this->directDrawPrimarySurfacePointer = NULL;
            this->directDrawOffscreenSurfacePointer_screenMenu = NULL;
            this->directDrawOffscreenSurfacePointer_mapGame = NULL;
            this->surfacePointer_screenMenu = NULL;
            this->surfacePointer_mapGame = NULL;
            this->pendingMenuRedraw = 0;
            this->screenHeightOnInit_0x14 = _screenHeight;
            this->NOTSelfBufferOrWindowMode_0xf8 = TRUE;
            return this;
        }

    }
}
}
