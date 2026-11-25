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

        // FUNCTION: STRONGHOLDCRUSADER 0x00408FC0
        void BinkControlClass::copyBinkToVideoBuffer(dword videoTarget)
        {
            for (int binkObjIndex = 0; binkObjIndex < 2; ++binkObjIndex) {
                if (this->soundStreamIndex[binkObjIndex] != OpenSHC::Audio::MSS::enums::SND_STR_MUSIC) {
                    if (!MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::isSampleOrStreamPlaying,
                            DAT_SoundSystemState::ptr)((SHC_SoundStream)this->soundStreamIndex[binkObjIndex])
                        || timeGetTime() - this->startTime[binkObjIndex] > 20000) {
                        this->soundStreamIndex[binkObjIndex] = OpenSHC::Audio::MSS::enums::SND_STR_MUSIC;
                    }
                }

                if (this->unknownParam07[binkObjIndex] == videoTarget) {
                    this->unknown01_zero[binkObjIndex] = 0;
                    this->unknown02_zero[binkObjIndex] = 0;
                }

                if (this->binkObjPtrArray[binkObjIndex] == NULL || this->unknownParam07[binkObjIndex] != videoTarget) {
                    continue;
                }

                if (BinkWait(this->binkObjPtrArray[binkObjIndex]) == 0) {
                    BinkDoFrame(this->binkObjPtrArray[binkObjIndex]);

                    if ((this->binkObjPtrArray[binkObjIndex]->FrameNum == this->binkObjPtrArray[binkObjIndex]->Frames)
                        && (this->unknownParam03[binkObjIndex] == 0)) {
                        if (this->soundStreamIndex[binkObjIndex] == OpenSHC::Audio::MSS::enums::SND_STR_MUSIC) {
                            if (videoTarget != 2) {
                                this->unknown01_zero[binkObjIndex] = 1;
                                MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::stopBinkPlayback, this)(
                                    binkObjIndex);
                                continue;
                            }
                            this->unknown02_zero[binkObjIndex] = 1;
                        } else if (videoTarget == 2) {
                            this->unknown02_zero[binkObjIndex] = 1;
                        }
                    } else {
                        BinkNextFrame(this->binkObjPtrArray[binkObjIndex]);
                    }

                    this->frameReadyToDisplay[binkObjIndex] = TRUE;
                }

                if (videoTarget == 2) {
                    DAT_MenuHandlerState::instance.currentMenu->xPosition
                        = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
                    DAT_MenuHandlerState::instance.currentMenu->yPosition
                        = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
                    DAT_MenuHandlerState::instance.x = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
                    DAT_MenuHandlerState::instance.y = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(0, 0, DAT_WindowAndDirectDraw::instance.resolutionX,
                        DAT_WindowAndDirectDraw::instance.resolutionY, COL_BLACK::instance.shortValue);
                }

                if (!this->frameReadyToDisplay[binkObjIndex]) {
                    continue;
                }

                if (this->unknownParam04[binkObjIndex] != 0) {
                    while (DAT_WindowAndDirectDraw::instance.directDrawOffscreenSurfacePointer_mapGame->Lock(NULL,
                               &DAT_WindowAndDirectDraw::instance.surfDescBink_offSurfMapGame, DDLOCK_WAIT, NULL)
                        == DDERR_SURFACELOST) {
                        if (DAT_WindowAndDirectDraw::instance.directDrawOffscreenSurfacePointer_mapGame->Restore()
                            != DD_OK) {
                            goto next_bink;
                        }
                    }
                    BinkCopyToBuffer(this->binkObjPtrArray[binkObjIndex],
                        DAT_WindowAndDirectDraw::instance.surfDescBink_offSurfMapGame.lpSurface,
                        DAT_WindowAndDirectDraw::instance.surfDescBink_offSurfMapGame.lPitch,
                        this->binkObjPtrArray[binkObjIndex]->Height, this->xPos[binkObjIndex], this->yPos[binkObjIndex],
                        this->mapGameSurfaceType | OpenSHC::Rendering::Bink::UBF_BINKCOPYALL);
                    DAT_WindowAndDirectDraw::instance.directDrawOffscreenSurfacePointer_mapGame->Unlock(NULL);
                } else {
                    while (DAT_WindowAndDirectDraw::instance.directDrawOffscreenSurfacePointer_screenMenu->Lock(NULL,
                               &DAT_WindowAndDirectDraw::instance.surfDescBink_offSurfScreenMenu_0x104, DDLOCK_WAIT, NULL)
                        == DDERR_SURFACELOST) {
                        if (DAT_WindowAndDirectDraw::instance.directDrawOffscreenSurfacePointer_screenMenu->Restore()
                            != DD_OK) {
                            goto next_bink;
                        }
                    }
                    BinkCopyToBuffer(this->binkObjPtrArray[binkObjIndex],
                        DAT_WindowAndDirectDraw::instance.surfDescBink_offSurfScreenMenu_0x104.lpSurface,
                        DAT_WindowAndDirectDraw::instance.surfDescBink_offSurfScreenMenu_0x104.lPitch,
                        this->binkObjPtrArray[binkObjIndex]->Height, this->xPos[binkObjIndex], this->yPos[binkObjIndex],
                        this->screenMenuSurfaceType_0x5c | OpenSHC::Rendering::Bink::UBF_BINKCOPYALL);
                    DAT_WindowAndDirectDraw::instance.directDrawOffscreenSurfacePointer_screenMenu->Unlock(NULL);
                }
            next_bink:;
            }
        }

    } // namespace Bink
} // namespace Rendering
} // namespace OpenSHC
