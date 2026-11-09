#include "../WindowAndDirectDraw.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x0046FF50
        void WindowAndDirectDraw::createCrusaderWindow(HINSTANCE hInstance, LPCSTR windowName, uint cursorResource)
        {
            this->hInstanceUnk_0xa8 = hInstance;
            if (!MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::createWindow, this)(
                    windowName, cursorResource)) {
                return;
            }
            CoInitialize(NULL);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::getDeviceCapsAndSetup, this)();
            if (this->currentGameResolution >= 0) {
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::setupPreferredScreenResolution, this)();
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::setWindowStyleRectAndPosition, this)();
            this->windowRenderTimeUnk_0x1e0 = timeGetTime();
        }

    }
}
}
