#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0046FF50
        void WindowAndDirectDraw::createCrusaderWindow(HINSTANCE hInstance, LPCSTR windowName, uint cursorResource)
        {
            BOOLEnum _windowCreated;
            this->hInstanceUnk_0xa8 = hInstance;
            _windowCreated = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::createWindow, this)(
                windowName, cursorResource);
            if (_windowCreated) {
                CoInitialize(NULL);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::getDeviceCapsAndSetup, this)();
                if (0 <= (int)this->currentGameResolution) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::setupPreferredScreenResolution, this)();
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::setWindowStyleRectAndPosition, this)();
                this->windowRenderTimeUnk_0x1e0 = timeGetTime();
            }
        }

    }
}
}
