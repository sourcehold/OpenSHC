#include "../SoundSystem.func.hpp"

#include "OpenSHC/Audio/mss/SoundFlagsAndLoopCountBitwiseFlagEnum.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // NOTE:
        // This functions seems to reset the 0 indexed stream, most likely the music stream
        // Index 3 seems to be general NPC voices (at least)
        // Assumption:
        // The tested flag here ("FLAG_SOUND_UNKNOWN_FLAG_1" currently) might indicate that playing this sample should
        // lower the music volume, or that the music volume is currently lowered

        // FUNCTION: STRONGHOLDCRUSADER 0x00479B70
        void SoundSystem::meth_0x479b70()
        {
            if (!this->waveOutOpenUnk_0x8) {
                return;
            }

            if (this->streamFlagsUnkAndLoopCount_0x34[3] & FLAG_SOUND_UNKNOWN_FLAG_1 && this->streamActiveUnk_0x20[3]
                && AIL_stream_status(this->stream_0xc[3]) != SMP_PLAYING) {
                this->streamFlagsUnkAndLoopCount_0x34[3] &= ~FLAG_SOUND_UNKNOWN_FLAG_1;
                AIL_set_sample_volume(
                    this->musicSampleUnk_0x170, (this->streamVolume[0] * this->streamFileVolumeNextUnk_0x48[0]) / 100);
            }
            if (this->streamFlagsUnkAndLoopCount_0x34[4] & FLAG_SOUND_UNKNOWN_FLAG_1 && this->streamActiveUnk_0x20[4]
                && AIL_stream_status(this->stream_0xc[4]) != SMP_PLAYING) {
                this->streamFlagsUnkAndLoopCount_0x34[4] &= ~FLAG_SOUND_UNKNOWN_FLAG_1;
                AIL_set_sample_volume(
                    this->musicSampleUnk_0x170, (this->streamVolume[0] * this->streamFileVolumeNextUnk_0x48[0]) / 100);
            }
        }

    }
}
}
