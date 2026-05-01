/**
  path: 'OpenSHC/UI/Rendering/WindowAndDirectDraw.func.hpp'
*/

#include "OpenSHC/Rendering/ScreenResolutionEnumInt.hpp"
#include "OpenSHC/UI/Rendering/WindowAndDirectDraw.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "WinDef.h"
#include "winnt.h"
namespace OpenSHC {
namespace UI {
    namespace Rendering {
        namespace WindowAndDirectDraw_Func {

            using OpenSHC::Rendering::ScreenResolutionEnumInt;
            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (WindowAndDirectDraw::*)(LPCSTR, uint), false,
                Address::SHC_3BB0A8C1_0x00467A90, &WindowAndDirectDraw::createWindow)
            createWindow;

            MACRO_FUNCTION_RESOLVER(void (WindowAndDirectDraw::*)(), false, Address::SHC_3BB0A8C1_0x00467B40,
                &WindowAndDirectDraw::getDeviceCapsAndSetup)
            getDeviceCapsAndSetup;

            MACRO_FUNCTION_RESOLVER(void (WindowAndDirectDraw::*)(BOOLEnum), false, Address::SHC_3BB0A8C1_0x00467D80,
                &WindowAndDirectDraw::releaseSurfacesAndDirectDraw)
            releaseSurfacesAndDirectDraw;

            MACRO_FUNCTION_RESOLVER(void (WindowAndDirectDraw::*)(), false, Address::SHC_3BB0A8C1_0x00467E40,
                &WindowAndDirectDraw::finalizeDirectDrawShutdown)
            finalizeDirectDrawShutdown;

            MACRO_FUNCTION_RESOLVER(void (WindowAndDirectDraw::*)(LPRECT, LPRECT), false,
                Address::SHC_3BB0A8C1_0x00467E50, &WindowAndDirectDraw::adjustForNotExclusiveFullscreenUnk)
            adjustForNotExclusiveFullscreenUnk;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (WindowAndDirectDraw::*)(), false, Address::SHC_3BB0A8C1_0x00467EC0,
                &WindowAndDirectDraw::restoreDXSurfaces)
            restoreDXSurfaces;

            MACRO_FUNCTION_RESOLVER(void (WindowAndDirectDraw::*)(), false, Address::SHC_3BB0A8C1_0x0046F730,
                &WindowAndDirectDraw::cleanDirectDraw)
            cleanDirectDraw;

            MACRO_FUNCTION_RESOLVER(void (WindowAndDirectDraw::*)(), false, Address::SHC_3BB0A8C1_0x0046F750,
                &WindowAndDirectDraw::setWindowStyleRectAndPosition)
            setWindowStyleRectAndPosition;

            MACRO_FUNCTION_RESOLVER(void (WindowAndDirectDraw::*)(), false, Address::SHC_3BB0A8C1_0x0046F880,
                &WindowAndDirectDraw::setupPreferredScreenResolution)
            setupPreferredScreenResolution;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (WindowAndDirectDraw::*)(), false, Address::SHC_3BB0A8C1_0x0046FA70,
                &WindowAndDirectDraw::initializeDirectDraw)
            initializeDirectDraw;

            MACRO_FUNCTION_RESOLVER(void (WindowAndDirectDraw::*)(HINSTANCE, LPCSTR, uint), false,
                Address::SHC_3BB0A8C1_0x0046FF50, &WindowAndDirectDraw::createCrusaderWindow)
            createCrusaderWindow;

            MACRO_FUNCTION_RESOLVER(void (WindowAndDirectDraw::*)(), false, Address::SHC_3BB0A8C1_0x0046FFB0,
                &WindowAndDirectDraw::prepareWindowAndDDrawUnk)
            prepareWindowAndDDrawUnk;

            MACRO_FUNCTION_RESOLVER(void (WindowAndDirectDraw::*)(int), false, Address::SHC_3BB0A8C1_0x00470040,
                &WindowAndDirectDraw::renderBltAndFlip)
            renderBltAndFlip;

            MACRO_FUNCTION_RESOLVER(void (WindowAndDirectDraw::*)(), false, Address::SHC_3BB0A8C1_0x00470610,
                &WindowAndDirectDraw::bltMapGameSurfaceToScreenMenuSurfaceComplete)
            bltMapGameSurfaceToScreenMenuSurfaceComplete;

            MACRO_FUNCTION_RESOLVER(void (WindowAndDirectDraw::*)(RECT, RECT), false, Address::SHC_3BB0A8C1_0x004706A0,
                &WindowAndDirectDraw::bltMapGameSurfaceToScreenMenuSurface)
            bltMapGameSurfaceToScreenMenuSurface;

            MACRO_FUNCTION_RESOLVER(void (WindowAndDirectDraw::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x004706E0, &WindowAndDirectDraw::bltMapGameSurfaceToScreen)
            bltMapGameSurfaceToScreen;

            MACRO_FUNCTION_RESOLVER(void (WindowAndDirectDraw::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x004707F0, &WindowAndDirectDraw::bltScreenMenuSurfaceToScreen)
            bltScreenMenuSurfaceToScreen;

            MACRO_FUNCTION_RESOLVER(void (WindowAndDirectDraw::*)(), false, Address::SHC_3BB0A8C1_0x004708F0,
                &WindowAndDirectDraw::reinitWindow)
            reinitWindow;

            MACRO_FUNCTION_RESOLVER(void (WindowAndDirectDraw::*)(BOOLEnum, ScreenResolutionEnumInt), false,
                Address::SHC_3BB0A8C1_0x004729B0, &WindowAndDirectDraw::prepareWindowAndDDraw_2Unk)
            prepareWindowAndDDraw_2Unk;

            MACRO_FUNCTION_RESOLVER(void (WindowAndDirectDraw::*)(int), false, Address::SHC_3BB0A8C1_0x00479540,
                &WindowAndDirectDraw::takeScreenshot)
            takeScreenshot;

        } // namespace WindowAndDirectDraw_Func
    } // namespace Rendering
} // namespace UI
} // namespace OpenSHC
