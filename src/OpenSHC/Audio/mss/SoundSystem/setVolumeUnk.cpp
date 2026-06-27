#include "../SoundSystem.func.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x00479E60
        void SoundSystem::setVolumeUnk(int streamIndex, int volume)
        {
            if (!this->waveOutOpenUnk_0x8) {
                return;
            }

            if (streamIndex == -1) {
                this->sampleVolume = volume;
                for (int i = 1; i < 32; ++i) {
                    AIL_set_sample_volume(
                        this->sample[i], (this->sampleSndStructVolumePercentage_0x3174[i] * volume) / 100);
                }
                return;
            }
            this->streamVolume[streamIndex] = volume;
            if (!this->streamActiveUnk_0x20[streamIndex]) {
                return;
            }
            if (streamIndex == 0) {
                AIL_set_sample_volume(
                    this->musicSampleUnk_0x170, (this->streamFileVolumeCurrentUnk_0x5c[0] * volume) / 100);
                return;
            }
            AIL_set_stream_volume(
                this->stream_0xc[streamIndex], (this->streamFileVolumeCurrentUnk_0x5c[streamIndex] * volume) / 100);
        }

    }
}
}
