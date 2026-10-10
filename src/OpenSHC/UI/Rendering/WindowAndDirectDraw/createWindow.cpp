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
            HWND__* hWndParent;
            HMENU__* hMenu;
            HINSTANCE__* hInstance;
            void* lpParam;
            WNDCLASSA _wndClassA;
            _wndClassA.lpfnWndProc = MACRO_CALL(Global_Func::WindowMsgProcessingFunc);
            _wndClassA.style = 0;
            _wndClassA.cbClsExtra = 0;
            _wndClassA.cbWndExtra = 0;
            _wndClassA.hInstance = this->hInstanceUnk_0xa8;
            _wndClassA.hIcon = LoadIconA(this->hInstanceUnk_0xa8, (CHAR*)(cursorResource & 0xffff));
            _wndClassA.hCursor = (HICON__*)0x0;
            _wndClassA.hbrBackground = (HBRUSH__*)0x0;
            _wndClassA.lpszMenuName = (CHAR*)0x0;
            _wndClassA.lpszClassName = "FFwinClass";
            ATOM _atom = RegisterClassA(&_wndClassA);
            if (!_atom) {
                return FALSE;
            }
            lpParam = (void*)0x0;
            hMenu = (HMENU__*)0x0;
            hWndParent = (HWND__*)0x0;
            hInstance = this->hInstanceUnk_0xa8;
            int nHeight = GetSystemMetrics(SM_CYSCREEN);
            int nWidth = GetSystemMetrics(SM_CXSCREEN);
            this->windowHandle = CreateWindowExA(
                0, "FFwinClass", windowName, 0x90000000, 0, 0, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
            return (uint)(this->windowHandle != (HWND__*)0x0);
        }

    }
}
}
