#include "../SoundSystem.func.hpp"

#include "OpenSHC/Audio/mss.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_SFXDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SoundEffectsHelperData1.hpp"

// not using copied helper
#undef AIL_startup

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047C400
        void SoundSystem::initMiles()
        {
            AIL_set_redist_directory(s_miles_005a6cfc);
            MACRO_CALL(MSS_Func::RegisterMilesAILShutdown)();
            AIL_startup();
            DAT_SoundEffectsHelperData1::instance.SND_Waveformat.wFormatTag = WAVE_FORMAT_PCM;
            DAT_SoundEffectsHelperData1::instance.SND_Waveformat.nChannels = 2;
            DAT_SoundEffectsHelperData1::instance.SND_Waveformat.nSamplesPerSec = 44100;
            DAT_SoundEffectsHelperData1::instance.SND_Waveformat.nAvgBytesPerSec = 176400;
            DAT_SoundEffectsHelperData1::instance.SND_Waveformat.nBlockAlign = 4;
            DAT_SoundEffectsHelperData1::instance.SND_Waveformat.wBitsPerSample = 16;
            BOOL const _waveOpenErrorUnk = AIL_waveOutOpen(
                &this->digSndDriver_0x4, 0, -1, &DAT_SoundEffectsHelperData1::instance.SND_Waveformat);
            if (_waveOpenErrorUnk == AIL_NO_ERROR) {
                this->waveOutOpenUnk_0x8 = TRUE;
            } else {
                this->waveOutOpenUnk_0x8 = FALSE;
            }
            if (!this->waveOutOpenUnk_0x8) {
                return;
            }

            MACRO_CALL_MEMBER(Rendering::Bink::BinkControlClass_Func::zeroBinkPtrAndLoadBinkSoundSystem,
                DAT_BinkControlState::ptr)(this->digSndDriver_0x4);
            this->streamActiveUnk_0x20[0] = 0;
            this->streamActiveUnk_0x20[1] = 0;
            this->streamActiveUnk_0x20[2] = 0;
            this->streamActiveUnk_0x20[3] = 0;
            this->streamActiveUnk_0x20[4] = 0;
            for (int i = 0; i < 32; ++i) {
                this->sample[i] = AIL_allocate_sample_handle(this->digSndDriver_0x4);
                this->sampleSoundIndex_0x20c[i] = 0;
            }
            this->loadedSoundsCountAndIndex_0x316c = 1;
            for (int i = 0; i < 1000; ++i) {
                this->soundFileCurrSampleNum_0x28c[i] = -1;
            }
            this->mbr_0x14c = 100;
            this->mbr_0x154 = 0;
            this->musicSampleUnk_0x170 = AIL_allocate_sample_handle(this->digSndDriver_0x4);
            this->sampleBufferSizeUnk_0x184
                = AIL_minimum_sample_buffer_size(this->digSndDriver_0x4, 22050, DIG_F_STEREO_16);
            if (this->sampleBufferSizeUnk_0x184 < 0x10000) {
                this->sampleBufferSizeUnk_0x184 = 0x10000;
            }
            this->sampleBufferPtrUnk_0x17c[0] = AIL_mem_alloc_lock(this->sampleBufferSizeUnk_0x184);
            this->sampleBufferPtrUnk_0x17c[1] = AIL_mem_alloc_lock(this->sampleBufferSizeUnk_0x184);
            this->musicSampleFileHandleUnk_0x174 = -1;
            this->musicFileHandle_0x178 = -1;
            this->currentSoundID_0x3278 = -1;
            this->sec_Section1055_0x3274 = 0;
            this->mbr_0x3288 = 0;

            timecaps_tag _timeCaps;
            MMRESULT const _err = timeGetDevCaps(&_timeCaps, sizeof(timecaps_tag));
            if (_err != MMSYSERR_NOERROR) {
                return;
            }
            unsigned int const uPeriod = min(max(_timeCaps.wPeriodMin, 10), _timeCaps.wPeriodMax);
            DAT_SoundEffectsHelperData1::instance.SND_SomeTimerResolution = uPeriod;
            timeBeginPeriod(uPeriod);
            DAT_SFXDefinedData::instance.SND_SomeTimerIdentifier
                = timeSetEvent(50, uPeriod, MSS_Func::SndSystemTimeCallback::get(), 0, 0x1);
        }

    }
}
}
