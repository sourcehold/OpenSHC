#include "../BinkControlClass.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/Rendering/Bink/UnsortedBinkFlag.hpp"
#include "OpenSHC/UI/Menu.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        using OpenSHC::Audio::MSS::enums::SHC_SoundStream;

        // The original inlined this per-video body into the loop.
        static __forceinline void copyBinkToVideoBuffer_copyFrame(
            BinkControlClass* self, int binkObjIndex, dword videoTarget)
        {
            if (self->soundStreamIndex[binkObjIndex] != OpenSHC::Audio::MSS::enums::SND_STR_MUSIC) {
                if (!MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::isSampleOrStreamPlaying,
                        DAT_SoundSystemState::ptr)((SHC_SoundStream)self->soundStreamIndex[binkObjIndex])
                    || timeGetTime() - self->startTime[binkObjIndex] > 20000) {
                    self->soundStreamIndex[binkObjIndex] = OpenSHC::Audio::MSS::enums::SND_STR_MUSIC;
                }
            }
            if (self->unknownParam07[binkObjIndex] == videoTarget) {
                self->unknown01_zero[binkObjIndex] = 0;
                self->unknown02_zero[binkObjIndex] = 0;
            }
            if (self->binkObjPtrArray[binkObjIndex] == NULL || self->unknownParam07[binkObjIndex] != videoTarget) {
                return;
            }
            if (BinkWait(self->binkObjPtrArray[binkObjIndex]) == 0) {
                BinkDoFrame(self->binkObjPtrArray[binkObjIndex]);

                if ((self->binkObjPtrArray[binkObjIndex]->FrameNum == self->binkObjPtrArray[binkObjIndex]->Frames)
                    && (self->unknownParam03[binkObjIndex] == 0)) {
                    if (self->soundStreamIndex[binkObjIndex] == OpenSHC::Audio::MSS::enums::SND_STR_MUSIC
                        && videoTarget != 2) {
                        self->unknown01_zero[binkObjIndex] = 1;
                        MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::stopBinkPlayback, self)(
                            binkObjIndex);
                        return;
                    }
                    if (videoTarget == 2) {
                        self->unknown02_zero[binkObjIndex] = 1;
                    }
                } else {
                    BinkNextFrame(self->binkObjPtrArray[binkObjIndex]);
                }
                self->frameReadyToDisplay[binkObjIndex] = TRUE;
            }
            if (videoTarget == 2) {
                int const menuBorderHeight = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
                int const menuBorderWidth = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
                OpenSHC::UI::Menu* const menu = DAT_MenuHandlerState::instance.currentMenu;
                menu->xPosition = menuBorderWidth;
                menu->yPosition = menuBorderHeight;
                DAT_MenuHandlerState::instance.y = menuBorderHeight;
                DAT_MenuHandlerState::instance.x = menuBorderWidth;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(0, 0, DAT_WindowAndDirectDraw::instance.resolutionX,
                    DAT_WindowAndDirectDraw::instance.resolutionY, COL_BLACK::instance.shortValue);
            }
            if (!self->frameReadyToDisplay[binkObjIndex]) {
                return;
            }
            if (self->unknownParam04[binkObjIndex] != 0) {
                for (int i = 0; DAT_WindowAndDirectDraw::instance.directDrawOffscreenSurfacePointer_mapGame->Lock(NULL,
                                    &DAT_WindowAndDirectDraw::instance.surfDescBink_offSurfMapGame, DDLOCK_WAIT, NULL)
                    == DDERR_SURFACELOST;
                    i++) {
                    if (DAT_WindowAndDirectDraw::instance.directDrawOffscreenSurfacePointer_mapGame->Restore()
                        != DD_OK) {
                        return;
                    }
                }
                BinkCopyToBuffer(self->binkObjPtrArray[binkObjIndex],
                    DAT_WindowAndDirectDraw::instance.surfDescBink_offSurfMapGame.lpSurface,
                    DAT_WindowAndDirectDraw::instance.surfDescBink_offSurfMapGame.lPitch,
                    self->binkObjPtrArray[binkObjIndex]->Height, self->xPos[binkObjIndex], self->yPos[binkObjIndex],
                    self->mapGameSurfaceType | OpenSHC::Rendering::Bink::UBF_BINKCOPYALL);
                DAT_WindowAndDirectDraw::instance.directDrawOffscreenSurfacePointer_mapGame->Unlock(NULL);
            } else {
                for (int i = 0;
                    DAT_WindowAndDirectDraw::instance.directDrawOffscreenSurfacePointer_screenMenu->Lock(NULL,
                        &DAT_WindowAndDirectDraw::instance.surfDescBink_offSurfScreenMenu_0x104, DDLOCK_WAIT, NULL)
                    == DDERR_SURFACELOST;
                    i++) {
                    if (DAT_WindowAndDirectDraw::instance.directDrawOffscreenSurfacePointer_screenMenu->Restore()
                        != DD_OK) {
                        return;
                    }
                }
                BinkCopyToBuffer(self->binkObjPtrArray[binkObjIndex],
                    DAT_WindowAndDirectDraw::instance.surfDescBink_offSurfScreenMenu_0x104.lpSurface,
                    DAT_WindowAndDirectDraw::instance.surfDescBink_offSurfScreenMenu_0x104.lPitch,
                    self->binkObjPtrArray[binkObjIndex]->Height, self->xPos[binkObjIndex], self->yPos[binkObjIndex],
                    self->screenMenuSurfaceType_0x5c | OpenSHC::Rendering::Bink::UBF_BINKCOPYALL);
                DAT_WindowAndDirectDraw::instance.directDrawOffscreenSurfacePointer_screenMenu->Unlock(NULL);
            }
        }

        // FUNCTION: STRONGHOLDCRUSADER 0x00408FC0
        void BinkControlClass::copyBinkToVideoBuffer(dword videoTarget)
        {
            for (int binkObjIndex = 0; binkObjIndex < countof(this->binkObjPtrArray); ++binkObjIndex) {
                copyBinkToVideoBuffer_copyFrame(this, binkObjIndex, videoTarget);
            }
        }

    } // namespace Bink
} // namespace Rendering
} // namespace OpenSHC
