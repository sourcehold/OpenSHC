#include "../../../Rendering.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        using OpenSHC::Audio::MSS::enums::SHC_SoundStream;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00409200
        void BinkControlClass::processBinkFrames()
        {
            for (int binkObjIndex = 0; binkObjIndex < 2; binkObjIndex++) {
                if (this->soundStreamIndex[binkObjIndex] != OpenSHC::Audio::MSS::enums::SND_STR_MUSIC) {
                    if (MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::isSampleOrStreamPlaying,
                            DAT_SoundSystemState::ptr)((SHC_SoundStream)this->soundStreamIndex[binkObjIndex])
                            == FALSE
                        || timeGetTime() - this->startTime[binkObjIndex] > 20000) {
                        this->soundStreamIndex[binkObjIndex] = OpenSHC::Audio::MSS::enums::SND_STR_MUSIC;
                    }
                }

                this->unknown01_zero[binkObjIndex] = 0;
                this->unknown02_zero[binkObjIndex] = 0;

                if (this->binkObjPtrArray[binkObjIndex] == (HBINK)0x0)
                    continue;
                if (BinkWait(this->binkObjPtrArray[binkObjIndex]) != 0)
                    continue;

                BinkDoFrame(this->binkObjPtrArray[binkObjIndex]);

                if ((this->binkObjPtrArray[binkObjIndex]->FrameNum == this->binkObjPtrArray[binkObjIndex]->Frames)
                    && (this->unknownParam03[binkObjIndex] == 0)) {
                    if (this->soundStreamIndex[binkObjIndex] == OpenSHC::Audio::MSS::enums::SND_STR_MUSIC) {
                        if (this->unknownParam07[binkObjIndex] != 2) {
                            this->unknown01_zero[binkObjIndex] = 1;
                            MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::stopBinkPlayback, this)(
                                binkObjIndex);
                            continue;
                        }
                        this->unknown02_zero[binkObjIndex] = 1;
                    } else if (this->unknownParam07[binkObjIndex] == 2) {
                        this->unknown02_zero[binkObjIndex] = 1;
                    }
                } else {
                    BinkNextFrame(this->binkObjPtrArray[binkObjIndex]);
                }

                this->frameReadyToDisplay[binkObjIndex] = TRUE;
            }
        }

    }
}
}
