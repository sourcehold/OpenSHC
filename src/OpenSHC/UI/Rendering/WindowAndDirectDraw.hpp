/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Rendering/WindowAndDirectDraw.hpp'
*/

#pragma once

#include "OpenSHC/Rendering/ColorModeInt.hpp"
#include "OpenSHC/Rendering/ScreenResolutionArrayStruct.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnumInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "WinDef.h"
#include "ddraw.h"
#include "winnt.h"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::ColorModeInt;
        using OpenSHC::Rendering::ScreenResolutionArrayStruct;
        using OpenSHC::Rendering::ScreenResolutionEnumInt;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x000001E4
        class WindowAndDirectDraw {
        public:
            BOOLEnum drawingReady_0x0; // 0x00000000 length: 4
            dword depthBitsPerPixel; // 0x00000004 length: 4
            int screenHorizontalResolutionInPixels; // 0x00000008 length: 4
            int screenVerticalResolutionInPixels; // 0x0000000C length: 4
            int screenWidthOnInit_0x10; // 0x00000010 length: 4
            int screenHeightOnInit_0x14; // 0x00000014 length: 4
            int gameResolutionX; // 0x00000018 length: 4
            int gameResolutionY; // 0x0000001C length: 4
            int mainMenuBorderWidth; // 0x00000020 length: 4
            int mainMenuBorderHeight; // 0x00000024 length: 4
            int gameOnScreenPosX_0x28; // 0x00000028 length: 4
            int gameOnScreenPosY_0x2c; // 0x0000002C length: 4
            int gameInWindowPosX_0x30; // 0x00000030 length: 4
            int gameInWindowPosY_0x34; // 0x00000034 length: 4
            int resolutionX; // 0x00000038 length: 4
            int resolutionY; // 0x0000003C length: 4
            int byteSizeOfOneHorizontalLine; // 0x00000040 length: 4
            int gameResolutionY_3_0x44; // 0x00000044 length: 4
            int byteSizeofScreenResolution; // 0x00000048 length: 4
            int numPixel_GameX_x_3_x_GameY_0x4c; // 0x0000004C length: 4
            dword colorDepth; // 0x00000050 length: 4
            ColorModeInt colorBitMode; // 0x00000054 length: 4
            BOOLEnum runGameAsExclusiveFullscreen; // 0x00000058 length: 4
            ScreenResolutionEnumInt currentGameResolution; // 0x0000005C length: 4
            dword windowMoveEventBlitCountdown; // 0x00000060 length: 4
            dword postWindowCloseMessage; // 0x00000064 length: 4
            ScreenResolutionArrayStruct resolutionSupported_0x68; // 0x00000068 length: 64
            HINSTANCE hInstanceUnk_0xa8; // 0x000000A8 length: 4
            HWND windowHandle; // 0x000000AC length: 4
            RECT clientOnScreenCoords; // 0x000000B0 length: 16
            dword unk_resetViewportRelated; // 0x000000C0 length: 4
            BOOLEnum isNotProcessingInputEvents; // 0x000000C4 length: 4
            BOOLEnum gameFocused; // 0x000000C8 length: 4
            dword mbr_0xcc; // 0x000000CC length: 4
            dword mbr_0xd0; // 0x000000D0 length: 4
            ushort* surfacePointer_screenMenu; // 0x000000D4 length: 4
            ushort* surfacePointer_mapGame; // 0x000000D8 length: 4
            dword field37_0xdc; // 0x000000DC length: 4
            BOOLEnum not_DDCAPS2_CANBOBHARDWARE_0xe0; // 0x000000E0 length: 4
            undefined1 padding_0xe4[8]; // 0x000000E4 length: 8
            IDirectDraw* pointerToIDirectDrawInterface; // 0x000000EC length: 4
            IDirectDrawSurface* directDrawBackbufferSurfacePointer; // 0x000000F0 length: 4
            IDirectDrawSurface* directDrawPrimarySurfacePointer; // 0x000000F4 length: 4
            BOOLEnum NOTSelfBufferOrWindowMode_0xf8; // 0x000000F8 length: 4
            IDirectDrawSurface* directDrawOffscreenSurfacePointer_screenMenu; // 0x000000FC length: 4
            IDirectDrawSurface* directDrawOffscreenSurfacePointer_mapGame; // 0x00000100 length: 4
            DDSURFACEDESC surfDescBink_offSurfScreenMenu_0x104; // 0x00000104 length: 108
            DDSURFACEDESC surfDescBink_offSurfMapGame; // 0x00000170 length: 108
            undefined* unknownSpecificPointer; // 0x000001DC length: 4
            dword windowRenderTimeUnk_0x1e0; // 0x000001E0 length: 4

        private:
            WindowAndDirectDraw(WindowAndDirectDraw const&);
            void operator=(WindowAndDirectDraw const&);

            WindowAndDirectDraw();
            ~WindowAndDirectDraw();

        public:
            // Constructor
            WindowAndDirectDraw* Constructor_WindowAndDirectDraw();

            BOOLEnum createWindow(LPCSTR windowName, uint cursorResource);

            void getDeviceCapsAndSetup();

            void releaseSurfacesAndDirectDraw(BOOLEnum alsoReleaseDDInterfaceUnk);

            void finalizeDirectDrawShutdown();

            void adjustForNotExclusiveFullscreenUnk(LPRECT destinationRect, LPRECT sourceRect);

            BOOLEnum restoreDXSurfaces();

            void cleanDirectDraw();

            void setWindowStyleRectAndPosition();

            void setupPreferredScreenResolution();

            BOOLEnum initializeDirectDraw();

            void createCrusaderWindow(HINSTANCE hInstance, LPCSTR windowName, uint cursorResource);

            void prepareWindowAndDDrawUnk();

            void renderBltAndFlip(int param_1);

            void bltMapGameSurfaceToScreenMenuSurfaceComplete();

            void bltMapGameSurfaceToScreenMenuSurface(RECT sourceRect, RECT destinationRect);

            void bltMapGameSurfaceToScreen(int windowedX, int windowedY, int windowedWidth, int windowedHeigth);

            void bltScreenMenuSurfaceToScreen(int windowedX, int windowedY, int windowedWidth, int windowedHeigth);

            void reinitWindow();

            void prepareWindowAndDDraw_2Unk(BOOLEnum runAsExclusiveFullscreen, ScreenResolutionEnumInt resEnum);

            void takeScreenshot(int param_1);
        };

        static_assert_cpp98_obj(sizeof(WindowAndDirectDraw) == 484, WindowAndDirectDraw);

#pragma pack(pop)

        MACRO_STRUCT_RESOLVER(WindowAndDirectDraw, false, Address::SHC_3BB0A8C1_0x00F98338) pDAT_WindowAndDirectDraw;

    } // namespace Rendering
} // namespace UI
} // namespace OpenSHC
