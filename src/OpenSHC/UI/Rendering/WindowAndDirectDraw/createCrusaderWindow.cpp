#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/UI/Rendering/WindowAndDirectDraw.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0046FF50
        void WindowAndDirectDraw::createCrusaderWindow(HINSTANCE hInstance, LPCSTR windowName, uint cursorResource)
        {
            BOOLEnum _windowCreated;
            this->hInstanceUnk_0xa8 = hInstance;
            _windowCreated = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::createWindow, this)(
                windowName, cursorResource);
            if (_windowCreated != FALSE) {
                CoInitialize((void*)0x0);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::getDeviceCapsAndSetup, this)();
                if (-1 < (int)this->currentGameResolution) {
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
