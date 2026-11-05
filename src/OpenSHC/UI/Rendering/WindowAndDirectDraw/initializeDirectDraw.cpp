#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Rendering.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"

#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0046FA70
        BOOLEnum WindowAndDirectDraw::initializeDirectDraw()
        {
            if (this->pointerToIDirectDrawInterface == NULL) {
                // Both creates are checked: the emulation-only branch jumps to the same result test.
                HRESULT result;
                if (MACRO_CALL(OpenSHC::Global_Func::TestOSVersion)()) {
                    result
                        = DirectDrawCreate((GUID*)DDCREATE_EMULATIONONLY, &this->pointerToIDirectDrawInterface, NULL);
                    this->NOTSelfBufferOrWindowMode_0xf8 = TRUE;
                } else {
                    result = DirectDrawCreate(NULL, &this->pointerToIDirectDrawInterface, NULL);
                    this->NOTSelfBufferOrWindowMode_0xf8 = TRUE;
                }
                if (result != DD_OK) {
                    return FALSE;
                }
            }

            DDCAPS caps;
            MACRO_CALL(OpenSHC::OS_Func::_memset)(&caps, 0, sizeof(caps));
            caps.dwSize = sizeof(caps);
            this->pointerToIDirectDrawInterface->GetCaps(&caps, NULL);
            if ((caps.dwCaps2 & DDCAPS2_CANBOBHARDWARE) == 0) {
                this->not_DDCAPS2_CANBOBHARDWARE_0xe0 = TRUE;
            }

            this->pointerToIDirectDrawInterface->EnumDisplayModes(
                0, NULL, NULL, MACRO_CALL(OpenSHC::Synchrony_Func::EnumDisplayModesCallback));

            if (this->currentGameResolution < 0
                || this->resolutionSupported_0x68.array[this->currentGameResolution] == 0) {
                this->currentGameResolution = OpenSHC::Rendering::SRE_neg1;
                for (int resolution = OpenSHC::Rendering::SRE_1920x1200; resolution > 0; --resolution) {
                    if (this->resolutionSupported_0x68.array[resolution] != 0) {
                        this->currentGameResolution = resolution;
                        break;
                    }
                }
                if (this->currentGameResolution == OpenSHC::Rendering::SRE_neg1) {
                    if (this->resolutionSupported_0x68.array[OpenSHC::Rendering::SRE_1360x768] != 0) {
                        this->currentGameResolution = OpenSHC::Rendering::SRE_1360x768;
                    } else if (this->resolutionSupported_0x68.array[OpenSHC::Rendering::SRE_1024x600] != 0) {
                        this->currentGameResolution = OpenSHC::Rendering::SRE_1024x600;
                    } else {
                        this->currentGameResolution = OpenSHC::Rendering::SRE_800x600;
                    }
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::setupPreferredScreenResolution, this)();
            }

            if (this->runGameAsExclusiveFullscreen) {
                if (this->pointerToIDirectDrawInterface->SetCooperativeLevel(
                        this->windowHandle, DDSCL_FULLSCREEN | DDSCL_EXCLUSIVE | DDSCL_ALLOWREBOOT)
                        != DD_OK
                    || this->pointerToIDirectDrawInterface->SetDisplayMode(this->resolutionX, this->resolutionY, 16)
                        != DD_OK) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::releaseSurfacesAndDirectDraw, this)(TRUE);
                    return FALSE;
                }
            } else if (this->pointerToIDirectDrawInterface->SetCooperativeLevel(this->windowHandle, DDSCL_NORMAL)
                != DD_OK) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::releaseSurfacesAndDirectDraw, this)(
                    TRUE);
                return FALSE;
            }

            DDSURFACEDESC desc;
            if (!this->NOTSelfBufferOrWindowMode_0xf8) {
                MACRO_CALL(OpenSHC::OS_Func::_memset)(&desc, 0, sizeof(desc));
                desc.dwSize = sizeof(desc);
                desc.dwFlags = DDSD_CAPS;
                desc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
                if (this->pointerToIDirectDrawInterface->CreateSurface(
                        &desc, &this->directDrawBackbufferSurfacePointer, NULL)
                    != DD_OK) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::releaseSurfacesAndDirectDraw, this)(TRUE);
                    return FALSE;
                }
            } else {
                MACRO_CALL(OpenSHC::OS_Func::_memset)(&desc, 0, sizeof(desc));
                desc.dwBackBufferCount = 1;
                desc.dwSize = sizeof(desc);
                desc.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
                desc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
                if (this->pointerToIDirectDrawInterface->CreateSurface(
                        &desc, &this->directDrawPrimarySurfacePointer, NULL)
                    != DD_OK) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::releaseSurfacesAndDirectDraw, this)(TRUE);
                    return FALSE;
                }
                MACRO_CALL(OpenSHC::OS_Func::_memset)(&desc, 0, sizeof(desc));
                desc.dwSize = sizeof(desc);
                desc.dwFlags = DDSD_CAPS;
                desc.ddsCaps.dwCaps = DDSCAPS_BACKBUFFER;
                if (this->directDrawPrimarySurfacePointer->GetAttachedSurface(
                        &desc.ddsCaps, &this->directDrawBackbufferSurfacePointer)
                    != DD_OK) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::releaseSurfacesAndDirectDraw, this)(TRUE);
                    return FALSE;
                }
            }

            MACRO_CALL(OpenSHC::OS_Func::_memset)(&desc, 0, sizeof(desc));
            desc.dwSize = sizeof(desc);
            desc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
            desc.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
            desc.dwHeight = this->resolutionY;
            desc.dwWidth = this->resolutionX;
            if (this->pointerToIDirectDrawInterface->CreateSurface(
                    &desc, &this->directDrawOffscreenSurfacePointer_screenMenu, NULL)
                != DD_OK) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::releaseSurfacesAndDirectDraw, this)(
                    TRUE);
                return FALSE;
            }
            DAT_BinkControlState::instance.screenMenuSurfaceType_0x5c
                = BinkDDSurfaceType(this->directDrawOffscreenSurfacePointer_screenMenu);
            this->surfDescBink_offSurfScreenMenu_0x104 = desc;
            if (this->directDrawOffscreenSurfacePointer_screenMenu->Lock(NULL, &desc, DDLOCK_WAIT, NULL) != DD_OK) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::releaseSurfacesAndDirectDraw, this)(
                    TRUE);
                return FALSE;
            }
            this->surfacePointer_screenMenu = (ushort*)desc.lpSurface;
            this->directDrawOffscreenSurfacePointer_screenMenu->Unlock(NULL);

            MACRO_CALL(OpenSHC::OS_Func::_memset)(&desc, 0, sizeof(desc));
            desc.dwSize = sizeof(desc);
            desc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
            desc.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
            // size of the map rendering surface
            desc.dwHeight = 2076;
            desc.dwWidth = 4056;
            // The original keeps this field's address in a register for both uses below.
            LPDIRECTDRAWSURFACE* const mapGameSurface = &this->directDrawOffscreenSurfacePointer_mapGame;
            if (this->pointerToIDirectDrawInterface->CreateSurface(&desc, mapGameSurface, NULL) != DD_OK) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::releaseSurfacesAndDirectDraw, this)(
                    TRUE);
                return FALSE;
            }
            DAT_BinkControlState::instance.mapGameSurfaceType = BinkDDSurfaceType(*mapGameSurface);
            this->surfDescBink_offSurfMapGame = desc;
            if (this->directDrawOffscreenSurfacePointer_mapGame->Lock(NULL, &desc, DDLOCK_WAIT, NULL) != DD_OK) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::releaseSurfacesAndDirectDraw, this)(
                    TRUE);
                return FALSE;
            }
            this->surfacePointer_mapGame = (ushort*)desc.lpSurface;
            this->directDrawOffscreenSurfacePointer_mapGame->Unlock(NULL);

            MACRO_CALL(OpenSHC::OS_Func::_memset)(&desc, 0, sizeof(desc));
            desc.dwSize = sizeof(desc);
            desc.ddpfPixelFormat.dwSize = sizeof(desc.ddpfPixelFormat);
            desc.dwFlags = DDSD_PIXELFORMAT;
            this->directDrawBackbufferSurfacePointer->GetSurfaceDesc(&desc);
            this->colorBitMode = OpenSHC::Rendering::RGB_555;
            // a 6-bit green mask means RGB565
            if (desc.ddpfPixelFormat.dwGBitMask == 2016) {
                this->colorBitMode = OpenSHC::Rendering::RGB_565;
            }
            MACRO_CALL(OpenSHC::Rendering_Func::InitializeColors)();

            // The original reads these two fields through the global instance, not through this.
            if (DAT_WindowAndDirectDraw::instance.runGameAsExclusiveFullscreen) {
                SetRect(&DAT_WindowAndDirectDraw::instance.clientOnScreenCoords, 0, 0, GetSystemMetrics(SM_CXSCREEN),
                    GetSystemMetrics(SM_CYSCREEN));
                return TRUE;
            }
            GetClientRect(this->windowHandle, &DAT_WindowAndDirectDraw::instance.clientOnScreenCoords);
            ClientToScreen(this->windowHandle, (LPPOINT)&DAT_WindowAndDirectDraw::instance.clientOnScreenCoords.left);
            ClientToScreen(this->windowHandle, (LPPOINT)&DAT_WindowAndDirectDraw::instance.clientOnScreenCoords.right);
            UpdateWindow(this->windowHandle);
            return TRUE;
        }

    }
}
}
