#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/UI/Rendering/WindowAndDirectDraw.func.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::ScreenResolutionEnum;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "UnsortedBinkFlagInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004729B0
        void WindowAndDirectDraw::prepareWindowAndDDraw_2Unk(
            BOOLEnum runAsExclusiveFullscreen, ScreenResolutionEnum resEnum)
        {
            dword dVar1;
            dVar1 = this->mbr_0xd0;
            if (this->drawingReady_0x0 != FALSE) {
                this->mbr_0xd0 = 0;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    this->byteSizeofScreenResolution, '\0', (void*)((int)(this->surfacePointer_screenMenu)));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::renderBltAndFlip, this)(1);
            }
            this->mbr_0xd0 = dVar1;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::releaseSurfacesAndDirectDraw, this)(
                TRUE);
            this->runGameAsExclusiveFullscreen = runAsExclusiveFullscreen;
            this->currentGameResolution = resEnum;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::getDeviceCapsAndSetup, this)();
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::setupPreferredScreenResolution, this)();
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::setWindowStyleRectAndPosition, this)();
            this->drawingReady_0x0
                = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::initializeDirectDraw, this)();
            do {
                if (this->drawingReady_0x0 != FALSE) {
                LAB_00472a5f:
                    this->unk_resetViewportRelated = 2;
                    this->field37_0xdc = 1;
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::stopBinkPlayback,
                        DAT_BinkControlState::ptr)(0);
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::stopBinkPlayback,
                        DAT_BinkControlState::ptr)(1);
                }
                if (this->currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
                    this->postWindowCloseMessage = 1;
                    goto LAB_00472a5f;
                }
                this->currentGameResolution = OpenSHC::Rendering::SRE_800x600;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::getDeviceCapsAndSetup, this)();
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::setupPreferredScreenResolution, this)();
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::setWindowStyleRectAndPosition, this)();
                this->drawingReady_0x0
                    = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::initializeDirectDraw, this)();
            } while (true);
        }

    }
}
}
