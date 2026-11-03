#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::ScreenResolutionEnum;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004729B0
        void WindowAndDirectDraw::prepareWindowAndDDraw_2Unk(
            BOOLEnum runAsExclusiveFullscreen, ScreenResolutionEnum resEnum)
        {
            if (this->drawingReady_0x0) {
                dword const pendingBltMode = this->pendingBltMode;
                this->pendingBltMode = 0;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    this->byteSizeofScreenResolution, 0, this->surfacePointer_screenMenu);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::renderBltAndFlip, this)(1);
                this->pendingBltMode = pendingBltMode;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::releaseSurfacesAndDirectDraw, this)(
                TRUE);
            this->runGameAsExclusiveFullscreen = runAsExclusiveFullscreen;
            this->currentGameResolution = resEnum;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::getDeviceCapsAndSetup, this)();
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::setupPreferredScreenResolution, this)();
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::setWindowStyleRectAndPosition, this)();
            this->drawingReady_0x0
                = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::initializeDirectDraw, this)();
            // If DirectDraw can't start in the chosen resolution, retry once in 800x600, else ask to close.
            while (!this->drawingReady_0x0) {
                if (this->currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
                    this->postWindowCloseMessage = 1;
                    break;
                }
                this->currentGameResolution = OpenSHC::Rendering::SRE_800x600;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::getDeviceCapsAndSetup, this)();
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::setupPreferredScreenResolution, this)();
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::setWindowStyleRectAndPosition, this)();
                this->drawingReady_0x0
                    = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::initializeDirectDraw, this)();
            }
            this->unk_resetViewportRelated = 2;
            DAT_WindowAndDirectDraw::instance.pendingMenuRedraw = 1;
            MACRO_CALL_MEMBER(
                OpenSHC::Rendering::Bink::BinkControlClass_Func::stopBinkPlayback, DAT_BinkControlState::ptr)(0);
            MACRO_CALL_MEMBER(
                OpenSHC::Rendering::Bink::BinkControlClass_Func::stopBinkPlayback, DAT_BinkControlState::ptr)(1);
        }

    }
}
}
