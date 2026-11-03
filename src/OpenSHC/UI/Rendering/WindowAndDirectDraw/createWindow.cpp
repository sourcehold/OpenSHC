#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00467A90
        BOOLEnum WindowAndDirectDraw::createWindow(LPCSTR windowName, uint cursorResource)
        {
            WNDCLASSA wndClass;
            wndClass.lpfnWndProc = MACRO_CALL(Global_Func::WindowMsgProcessingFunc);
            wndClass.style = 0;
            wndClass.cbClsExtra = 0;
            wndClass.cbWndExtra = 0;
            wndClass.hInstance = this->hInstanceUnk_0xa8;
            wndClass.hIcon = LoadIconA(this->hInstanceUnk_0xa8, MAKEINTRESOURCEA(cursorResource));
            wndClass.hCursor = NULL;
            wndClass.hbrBackground = NULL;
            wndClass.lpszMenuName = NULL;
            wndClass.lpszClassName = "FFwinClass";
            if (!RegisterClassA(&wndClass)) {
                return FALSE;
            }
            this->windowHandle = CreateWindowExA(0, "FFwinClass", windowName, WS_POPUP | WS_VISIBLE, 0, 0,
                GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), NULL, NULL, this->hInstanceUnk_0xa8,
                NULL);
            return this->windowHandle != NULL;
        }

    }
}
}
