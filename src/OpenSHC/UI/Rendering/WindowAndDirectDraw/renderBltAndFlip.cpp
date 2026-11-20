#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // Blits the menu bar (mode 2) or one of two menu panels (modes 3 and 4) from the screen menu surface over the
        // map. The original has this code twice, word for word: after the map blit and again after the flip.
        static __forceinline void blitMenuOverlayUnk(
            WindowAndDirectDraw* window, RECT& sourceRect, RECT& destinationRect)
        {
            if (window->unk_resetViewportRelated == 2 && DAT_WindowAndDirectDraw::instance.pendingBltMode != 2) {
                window->mbr_0xcc++;
                sourceRect.top = DAT_WindowAndDirectDraw::instance.resolutionY - 128;
                sourceRect.bottom = DAT_WindowAndDirectDraw::instance.resolutionY;
                destinationRect.left = window->clientOnScreenCoords.left;
                destinationRect.bottom
                    = DAT_WindowAndDirectDraw::instance.resolutionY + window->clientOnScreenCoords.top;
                destinationRect.right
                    = window->clientOnScreenCoords.left + DAT_WindowAndDirectDraw::instance.resolutionX;
                sourceRect.right = DAT_WindowAndDirectDraw::instance.resolutionX;
                destinationRect.top = destinationRect.bottom - 128;
                sourceRect.left = 0;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::adjustForNotExclusiveFullscreenUnk,
                    window)(&destinationRect, &sourceRect);
                window->directDrawBackbufferSurfacePointer->Blt(&destinationRect,
                    window->directDrawOffscreenSurfacePointer_screenMenu, &sourceRect, DDBLT_WAIT, NULL);
                return;
            }
            if (window->unk_resetViewportRelated == 3) {
                sourceRect.left = DAT_MenuHandlerState::instance.x + 571;
                sourceRect.top = DAT_MenuHandlerState::instance.y + 465;
                sourceRect.right = DAT_MenuHandlerState::instance.x + 697;
                sourceRect.bottom = DAT_MenuHandlerState::instance.y + 591;
                destinationRect.left = DAT_MenuHandlerState::instance.x + window->clientOnScreenCoords.left + 571;
                destinationRect.top = DAT_MenuHandlerState::instance.y + window->clientOnScreenCoords.top + 465;
                destinationRect.right = DAT_MenuHandlerState::instance.x + window->clientOnScreenCoords.left + 697;
                destinationRect.bottom = DAT_MenuHandlerState::instance.y + window->clientOnScreenCoords.top + 591;
            } else if (window->unk_resetViewportRelated == 4) {
                sourceRect.left = DAT_MenuHandlerState::instance.x + 664;
                sourceRect.top = DAT_MenuHandlerState::instance.y + 464;
                sourceRect.right = DAT_MenuHandlerState::instance.x + 792;
                sourceRect.bottom = DAT_MenuHandlerState::instance.y + 592;
                destinationRect.left = DAT_MenuHandlerState::instance.x + window->clientOnScreenCoords.left + 664;
                destinationRect.top = DAT_MenuHandlerState::instance.y + window->clientOnScreenCoords.top + 464;
                destinationRect.right = DAT_MenuHandlerState::instance.x + window->clientOnScreenCoords.left + 792;
                destinationRect.bottom = DAT_MenuHandlerState::instance.y + window->clientOnScreenCoords.top + 592;
            } else {
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::adjustForNotExclusiveFullscreenUnk,
                window)(&destinationRect, &sourceRect);
            window->directDrawBackbufferSurfacePointer->Blt(
                &destinationRect, window->directDrawOffscreenSurfacePointer_screenMenu, &sourceRect, DDBLT_WAIT, NULL);
        }

        // FUNCTION: STRONGHOLDCRUSADER 0x00470040
        void WindowAndDirectDraw::renderBltAndFlip(int request)
        {
            RECT destinationRect;
            RECT sourceRect;
            int menuBarHeight = 128;
            BOOL mapBltPending = FALSE;
            if (request >= 100) {
                request -= 100;
            }
            if (this->pendingBltMode != 0) {
                mapBltPending = TRUE;
            }
            if (request != 0) {
                this->windowMoveEventBlitCountdown = 0;
            }
            if (!this->drawingReady_0x0) {
                DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                return;
            }
            if (GetForegroundWindow() != this->windowHandle) {
                DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                return;
            }
            if (this->windowMoveEventBlitCountdown != 0) {
                DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                this->windowMoveEventBlitCountdown--;
                return;
            }
            DWORD const now = timeGetTime();
            // This may be an actual max fps: 200fps. But only other certain conditions? -TheRedDaemon
            if (this->unk_resetViewportRelated == 1) {
                mapBltPending = FALSE;
                this->pendingBltMode = 0;
            } else if ((int)(now - this->windowRenderTimeUnk_0x1e0) < 5) {
                return;
            }
            this->windowRenderTimeUnk_0x1e0 = now;
            if (!mapBltPending) {
                sourceRect.left = 0;
                sourceRect.top = 0;
                sourceRect.right = this->gameResolutionX;
                sourceRect.bottom = this->gameResolutionY;
                if (request == 1) {
                    char debugText[2000];
                    MACRO_CALL(OpenSHC::OS_Func::_sprintf)(debugText, s_Vid__d__sys__d_005a6208,
                        this->directDrawBackbufferSurfacePointer, this->directDrawOffscreenSurfacePointer_screenMenu);
                }
                if (this->runGameAsExclusiveFullscreen) {
                    this->directDrawBackbufferSurfacePointer->BltFast(0, 0,
                        this->directDrawOffscreenSurfacePointer_screenMenu, &this->clientOnScreenCoords,
                        DDBLTFAST_WAIT);
                } else {
                    destinationRect = this->clientOnScreenCoords;
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::adjustForNotExclusiveFullscreenUnk, this)(
                        &destinationRect, &sourceRect);
                    this->directDrawBackbufferSurfacePointer->Blt(&destinationRect,
                        this->directDrawOffscreenSurfacePointer_screenMenu, &sourceRect, DDBLT_WAIT, NULL);
                }
            }
            if (this->pendingBltMode != 0) {
                if (this->pendingBltMode == 2) {
                    menuBarHeight = 0;
                }
                sourceRect.left = DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX;
                sourceRect.right = DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX
                    + DAT_WindowAndDirectDraw::instance.resolutionX;
                sourceRect.top = DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY;
                sourceRect.bottom = DAT_WindowAndDirectDraw::instance.resolutionY - menuBarHeight
                    + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY;
                destinationRect.left = this->clientOnScreenCoords.left;
                destinationRect.right = this->clientOnScreenCoords.left + DAT_WindowAndDirectDraw::instance.resolutionX;
                destinationRect.top = this->clientOnScreenCoords.top;
                destinationRect.bottom
                    = this->clientOnScreenCoords.top - menuBarHeight + DAT_WindowAndDirectDraw::instance.resolutionY;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::adjustForNotExclusiveFullscreenUnk,
                    this)(&destinationRect, &sourceRect);
                this->directDrawBackbufferSurfacePointer->Blt(
                    &destinationRect, this->directDrawOffscreenSurfacePointer_mapGame, &sourceRect, DDBLT_WAIT, NULL);
                blitMenuOverlayUnk(this, sourceRect, destinationRect);
            }
            if (this->NOTSelfBufferOrWindowMode_0xf8 == TRUE) {
                this->directDrawPrimarySurfacePointer->Flip(NULL, DDFLIP_WAIT);
                blitMenuOverlayUnk(this, sourceRect, destinationRect);
            }
            DAT_WindowAndDirectDraw::instance.pendingBltMode = 0;
            this->unk_resetViewportRelated = 0;
        }

    }
}
}
