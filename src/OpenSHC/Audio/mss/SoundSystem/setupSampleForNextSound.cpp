#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x00479CF0
        void SoundSystem::setupSampleForNextSound(int soundIndex, int sampleVolumePercentage, int samplePan)
        {
            if (!this->waveOutOpenUnk_0x8 || (this->soundFileCurrSampleNum_0x28c[soundIndex] < 0)) {
                return;
            }

            this->sampleSndStructVolumePercentage_0x3174[this->soundFileCurrSampleNum_0x28c[soundIndex]]
                = sampleVolumePercentage;
            AIL_set_sample_volume(this->sample_0x190[this->soundFileCurrSampleNum_0x28c[soundIndex] + -1],
                (this->sampleVolume * sampleVolumePercentage) / 100);
            AIL_set_sample_pan(this->sample_0x190[this->soundFileCurrSampleNum_0x28c[soundIndex] + -1], samplePan);
            AIL_set_sample_loop_count(this->sample_0x190[this->soundFileCurrSampleNum_0x28c[soundIndex] + -1], 1);
        }

    }
}
}
