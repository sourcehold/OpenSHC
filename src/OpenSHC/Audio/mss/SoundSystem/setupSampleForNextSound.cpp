#include "../SoundSystem.func.hpp"

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
            AIL_set_sample_volume(this->sample[this->soundFileCurrSampleNum_0x28c[soundIndex]],
                (this->sampleVolume * sampleVolumePercentage) / 100);
            AIL_set_sample_pan(this->sample[this->soundFileCurrSampleNum_0x28c[soundIndex]], samplePan);
            AIL_set_sample_loop_count(this->sample[this->soundFileCurrSampleNum_0x28c[soundIndex]], 1);
        }

    }
}
}
