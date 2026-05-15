#include "OpenSHC/Audio/mss/SoundSystem.func.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x00479B70
        void SoundSystem::meth_0x479b70()
        {
            if (!this->waveOutOpenUnk_0x8) {
                return;
            }

            if ((*((unsigned int*)&this->streamFlagsUnkAndLoopCount_0x34[3]) & 0x20000000)
                && this->streamActiveUnk_0x20[3] && AIL_stream_status(this->stream_0xc[3]) != SMP_PLAYING) {
                unsigned int const copyWithoutFlag
                    = *((unsigned int*)&this->streamFlagsUnkAndLoopCount_0x34[3]) & 0xdfffffff;
                this->streamFlagsUnkAndLoopCount_0x34[3] = *((UnkSoundFlagsAndLoopCount*)&copyWithoutFlag);
                AIL_set_sample_volume(
                    this->musicSampleUnk_0x170, (this->streamVolume[0] * this->streamFileVolumeNextUnk_0x48[0]) / 100);
            }
            if ((*((unsigned int*)&this->streamFlagsUnkAndLoopCount_0x34[4]) & 0x20000000)
                && this->streamActiveUnk_0x20[4] && AIL_stream_status(this->stream_0xc[4]) != SMP_PLAYING) {
                unsigned int const copyWithoutFlag
                    = *((unsigned int*)&this->streamFlagsUnkAndLoopCount_0x34[4]) & 0xdfffffff;
                this->streamFlagsUnkAndLoopCount_0x34[4] = *((UnkSoundFlagsAndLoopCount*)&copyWithoutFlag);
                AIL_set_sample_volume(
                    this->musicSampleUnk_0x170, (this->streamVolume[0] * this->streamFileVolumeNextUnk_0x48[0]) / 100);
            }
        }

    }
}
}
