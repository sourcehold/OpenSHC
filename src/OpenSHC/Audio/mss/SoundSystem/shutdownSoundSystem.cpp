#include "../SoundSystem.func.hpp"

#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"

#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_SFXDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SoundEffectsHelperData1.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047A690
        void SoundSystem::shutdownSoundSystem()
        {
            if (!this->waveOutOpenUnk_0x8) {
                return;
            }

            MACRO_CALL_MEMBER(Rendering::Bink::BinkControlClass_Func::stopAllBinkPlayback, DAT_BinkControlState::ptr)();
            if (DAT_SFXDefinedData::ptr->SND_SomeTimerIdentifier != 0xffffffff) {
                timeKillEvent(DAT_SFXDefinedData::ptr->SND_SomeTimerIdentifier);
                timeEndPeriod(DAT_SoundEffectsHelperData1::ptr->SND_SomeTimerResolution);
                DAT_SFXDefinedData::ptr->SND_SomeTimerIdentifier = 0xffffffff;
            }
            for (int i = 0; i < 5; ++i) {
                UnkSoundFlagsAndLoopCount const unkSoundFlagsAndLoopCount = { 0, 0, 0, 0, 0 };
                this->streamFlagsUnkAndLoopCount_0x34[i] = unkSoundFlagsAndLoopCount;
                MACRO_CALL_MEMBER(SoundSystem_Func::endSoundStream, this)(i);
            }
            for (int i = 0; i < 31; ++i) {
                AIL_end_sample(this->sample_0x190[i]);
                AIL_release_sample_handle(this->sample_0x190[i]);
            }
            for (int i = 1; i < this->loadedSoundsCountAndIndex_0x316c; ++i) {
                if (this->soundFileDataPointerArray_0x122c[i]) {
                    AIL_mem_free_lock(this->soundFileDataPointerArray_0x122c[i]);
                }
            }
            AIL_mem_free_lock(this->sampleBufferPtrUnk_0x17c[0]);
            AIL_mem_free_lock(this->sampleBufferPtrUnk_0x17c[1]);
            AIL_release_sample_handle(this->musicSampleUnk_0x170);
            AIL_close_digital_driver(this->digSndDriver_0x4);
            AIL_shutdown();
            this->waveOutOpenUnk_0x8 = FALSE;
        }

    }
}
}
