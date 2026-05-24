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
                for (int i = 0; i < 31; ++i) {
                    // TODO: A lot of structures of SoundSystem use an 32 element array. sample_0x190 for example
                    //   uses 31 and might be "missing" its first element. The 0 seems to be used for "something" else
                    //   in general. So either we should one day treat all these as "a value and a 31 element array" or
                    //   like a single 32 array.
                    AIL_set_sample_volume(
                        this->sample_0x190[i], (this->sampleSndStructVolumePercentage_0x3174[i + 1] * volume) / 100);
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
