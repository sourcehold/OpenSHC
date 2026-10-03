#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/Rendering/WindowAndDirectDraw.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00470040
        void WindowAndDirectDraw::renderBltAndFlip(int param_1)
        {
            HWND__* _windowHandle;
            DWORD _currentTime;
            int iVar1;
            bool bVar2;
            tagRECT _destinationRect;
            tagRECT _sourceRect;
            char local_7d4[2000];
            uint _safetyCookie;
            _safetyCookie = MSVC_SecurityCookie::instance ^ (uint)&_destinationRect;
            iVar1 = 0x80;
            if (99 < param_1) {
                param_1 = param_1 + -100;
            }
            bVar2 = this->mbr_0xd0 != 0;
            if (param_1 != 0) {
                this->windowMoveEventBlitCountdown = 0;
            }
            if ((this->drawingReady_0x0 == FALSE)
                || (_windowHandle = GetForegroundWindow(), _windowHandle != this->windowHandle)) {
                DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                goto LAB_004705e6;
            }
            if (this->windowMoveEventBlitCountdown != 0) {
                DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                this->windowMoveEventBlitCountdown = this->windowMoveEventBlitCountdown - 1;
                goto LAB_004705e6;
            }
            _currentTime = timeGetTime();
            /*
              This may be an actual max fps: 200fps. But only other certain conditions?   -TheRedDaemon
             */
            if (this->unk_resetViewportRelated == 1) {
                bVar2 = false;
                this->mbr_0xd0 = 0;
            } else if ((int)(_currentTime - this->windowRenderTimeUnk_0x1e0) < 5)
                goto LAB_004705e6;
            this->windowRenderTimeUnk_0x1e0 = _currentTime;
            if (!bVar2) {
                _sourceRect.left = 0;
                _sourceRect.top = 0;
                _sourceRect.right = this->gameResolutionX;
                _sourceRect.bottom = this->gameResolutionY;
                if (param_1 == 1) {
                    MACRO_CALL(OpenSHC::OS_Func::_sprintf)(local_7d4, "Vid %d, sys %d",
                        this->directDrawBackbufferSurfacePointer, this->directDrawOffscreenSurfacePointer_screenMenu);
                }
                if (this->runGameAsExclusiveFullscreen == FALSE) {
                    _destinationRect.top = this->clientOnScreenCoords.top;
                    _destinationRect.right = this->clientOnScreenCoords.right;
                    _destinationRect.left = this->clientOnScreenCoords.left;
                    _destinationRect.bottom = this->clientOnScreenCoords.bottom;
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::adjustForNotExclusiveFullscreenUnk, this)(
                        &_destinationRect, &_sourceRect);
                    this->directDrawBackbufferSurfacePointer->Blt(&_destinationRect,
                        this->directDrawOffscreenSurfacePointer_screenMenu, &_sourceRect, 0x1000000, (LPDDBLTFX)0x0);
                } else {
                    this->directDrawBackbufferSurfacePointer->BltFast(
                        0, 0, this->directDrawOffscreenSurfacePointer_screenMenu, (tagRECT*)0xf983e8, 0x10);
                }
            }
            if (this->mbr_0xd0 != 0) {
                if (this->mbr_0xd0 == 2) {
                    iVar1 = 0;
                }
                _sourceRect.left = DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX;
                _sourceRect.right
                    = DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX + this->resolutionX;
                _sourceRect.top = DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY;
                _sourceRect.bottom = (this->resolutionY - iVar1)
                    + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY;
                _destinationRect.left = this->clientOnScreenCoords.left;
                _destinationRect.right = this->clientOnScreenCoords.left + this->resolutionX;
                _destinationRect.top = this->clientOnScreenCoords.top;
                _destinationRect.bottom = (this->clientOnScreenCoords.top - iVar1) + this->resolutionY;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::adjustForNotExclusiveFullscreenUnk,
                    this)(&_destinationRect, &_sourceRect);
                this->directDrawBackbufferSurfacePointer->Blt(&_destinationRect,
                    this->directDrawOffscreenSurfacePointer_mapGame, &_sourceRect, 0x1000000, (LPDDBLTFX)0x0);
                if ((this->unk_resetViewportRelated == 2) && (this->mbr_0xd0 != 2)) {
                    this->mbr_0xcc = this->mbr_0xcc + 1;
                    _sourceRect.top = this->resolutionY + -0x80;
                    _sourceRect.bottom = this->resolutionY;
                    _destinationRect.left = this->clientOnScreenCoords.left;
                    _destinationRect.bottom = this->resolutionY + this->clientOnScreenCoords.top;
                    _destinationRect.right = this->clientOnScreenCoords.left + this->resolutionX;
                    _sourceRect.right = this->resolutionX;
                    _destinationRect.top = _destinationRect.bottom + -0x80;
                    _sourceRect.left = 0;
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::adjustForNotExclusiveFullscreenUnk, this)(
                        &_destinationRect, &_sourceRect);
                    this->directDrawBackbufferSurfacePointer->Blt(&_destinationRect,
                        this->directDrawOffscreenSurfacePointer_screenMenu, &_sourceRect, 0x1000000, (LPDDBLTFX)0x0);
                } else {
                    if (this->unk_resetViewportRelated == 3) {
                        _sourceRect.left = DAT_MenuHandlerState::instance.x + 0x23b;
                        _sourceRect.top = DAT_MenuHandlerState::instance.y + 0x1d1;
                        _sourceRect.right = DAT_MenuHandlerState::instance.x + 0x2b9;
                        _sourceRect.bottom = DAT_MenuHandlerState::instance.y + 0x24f;
                        _destinationRect.left
                            = DAT_MenuHandlerState::instance.x + this->clientOnScreenCoords.left + 0x23b;
                        _destinationRect.top
                            = DAT_MenuHandlerState::instance.y + this->clientOnScreenCoords.top + 0x1d1;
                        _destinationRect.right
                            = DAT_MenuHandlerState::instance.x + this->clientOnScreenCoords.left + 0x2b9;
                        _destinationRect.bottom
                            = DAT_MenuHandlerState::instance.y + this->clientOnScreenCoords.top + 0x24f;
                    } else {
                        if (this->unk_resetViewportRelated != 4)
                            goto LAB_0047040e;
                        _sourceRect.left = DAT_MenuHandlerState::instance.x + 0x298;
                        _sourceRect.top = DAT_MenuHandlerState::instance.y + 0x1d0;
                        _sourceRect.right = DAT_MenuHandlerState::instance.x + 0x318;
                        _sourceRect.bottom = DAT_MenuHandlerState::instance.y + 0x250;
                        _destinationRect.left
                            = DAT_MenuHandlerState::instance.x + this->clientOnScreenCoords.left + 0x298;
                        _destinationRect.top
                            = DAT_MenuHandlerState::instance.y + this->clientOnScreenCoords.top + 0x1d0;
                        _destinationRect.right
                            = DAT_MenuHandlerState::instance.x + this->clientOnScreenCoords.left + 0x318;
                        _destinationRect.bottom
                            = DAT_MenuHandlerState::instance.y + this->clientOnScreenCoords.top + 0x250;
                    }
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::adjustForNotExclusiveFullscreenUnk, this)(
                        &_destinationRect, &_sourceRect);
                    this->directDrawBackbufferSurfacePointer->Blt(&_destinationRect,
                        this->directDrawOffscreenSurfacePointer_screenMenu, &_sourceRect, 0x1000000, (LPDDBLTFX)0x0);
                }
            }
        LAB_0047040e:
            if (this->NOTSelfBufferOrWindowMode_0xf8 == TRUE) {
                this->directDrawPrimarySurfacePointer->Flip((IDirectDrawSurface*)0x0, 1);
                if ((this->unk_resetViewportRelated == 2) && (this->mbr_0xd0 != 2)) {
                    this->mbr_0xcc = this->mbr_0xcc + 1;
                    _sourceRect.top = this->resolutionY + -0x80;
                    _sourceRect.bottom = this->resolutionY;
                    _destinationRect.left = this->clientOnScreenCoords.left;
                    _destinationRect.bottom = this->resolutionY + this->clientOnScreenCoords.top;
                    _destinationRect.right = this->clientOnScreenCoords.left + this->resolutionX;
                    _sourceRect.right = this->resolutionX;
                    _destinationRect.top = _destinationRect.bottom + -0x80;
                    _sourceRect.left = 0;
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::adjustForNotExclusiveFullscreenUnk, this)(
                        &_destinationRect, &_sourceRect);
                    this->directDrawBackbufferSurfacePointer->Blt(&_destinationRect,
                        this->directDrawOffscreenSurfacePointer_screenMenu, &_sourceRect, 0x1000000, (LPDDBLTFX)0x0);
                } else {
                    if (this->unk_resetViewportRelated == 3) {
                        _sourceRect.left = DAT_MenuHandlerState::instance.x + 571;
                        _sourceRect.top = DAT_MenuHandlerState::instance.y + 0x1d1;
                        _sourceRect.right = DAT_MenuHandlerState::instance.x + 697;
                        _sourceRect.bottom = DAT_MenuHandlerState::instance.y + 0x24f;
                        _destinationRect.left
                            = DAT_MenuHandlerState::instance.x + this->clientOnScreenCoords.left + 571;
                        _destinationRect.top
                            = DAT_MenuHandlerState::instance.y + this->clientOnScreenCoords.top + 0x1d1;
                        _destinationRect.right
                            = DAT_MenuHandlerState::instance.x + this->clientOnScreenCoords.left + 0x2b9;
                        _destinationRect.bottom
                            = DAT_MenuHandlerState::instance.y + this->clientOnScreenCoords.top + 0x24f;
                    } else {
                        if (this->unk_resetViewportRelated != 4)
                            goto LAB_004705da;
                        _sourceRect.left = DAT_MenuHandlerState::instance.x + 664;
                        _sourceRect.top = DAT_MenuHandlerState::instance.y + 0x1d0;
                        _sourceRect.right = DAT_MenuHandlerState::instance.x + 0x318;
                        _sourceRect.bottom = DAT_MenuHandlerState::instance.y + 0x250;
                        _destinationRect.left
                            = DAT_MenuHandlerState::instance.x + this->clientOnScreenCoords.left + 0x298;
                        _destinationRect.top
                            = DAT_MenuHandlerState::instance.y + this->clientOnScreenCoords.top + 0x1d0;
                        _destinationRect.right
                            = DAT_MenuHandlerState::instance.x + this->clientOnScreenCoords.left + 0x318;
                        _destinationRect.bottom
                            = DAT_MenuHandlerState::instance.y + this->clientOnScreenCoords.top + 0x250;
                    }
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::adjustForNotExclusiveFullscreenUnk, this)(
                        &_destinationRect, &_sourceRect);
                    this->directDrawBackbufferSurfacePointer->Blt(&_destinationRect,
                        this->directDrawOffscreenSurfacePointer_screenMenu, &_sourceRect, 0x1000000, (LPDDBLTFX)0x0);
                }
            }
        LAB_004705da:
            this->mbr_0xd0 = 0;
            this->unk_resetViewportRelated = 0;
        LAB_004705e6:;
        }

    }
}
}
