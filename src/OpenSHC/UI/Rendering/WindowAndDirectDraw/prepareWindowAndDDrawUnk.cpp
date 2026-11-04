#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"

#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x0046FFB0
        void WindowAndDirectDraw::prepareWindowAndDDrawUnk()
        {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::releaseSurfacesAndDirectDraw, this)(
                TRUE);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::getDeviceCapsAndSetup, this)();
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::setupPreferredScreenResolution, this)();
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::setWindowStyleRectAndPosition, this)();
            this->drawingReady_0x0
                = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::initializeDirectDraw, this)();
            // I think it tries again with the default resolution of 800x600 (assuming the DAT_CurrentResolution is
            // right). If it fails again, it sets another flag and also returns. -TheRedDaemon
            for (; !this->drawingReady_0x0;) {
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
            // The original writes this field through the global instance, not through this.
            DAT_WindowAndDirectDraw::instance.pendingMenuRedraw = 1;
            MACRO_CALL_MEMBER(
                OpenSHC::Rendering::Bink::BinkControlClass_Func::stopBinkPlayback, DAT_BinkControlState::ptr)(0);
            MACRO_CALL_MEMBER(
                OpenSHC::Rendering::Bink::BinkControlClass_Func::stopBinkPlayback, DAT_BinkControlState::ptr)(1);
        }

    }
}
}
