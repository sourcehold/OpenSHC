#include "../SoundSystem.func.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // NOTE:
        // Quick test showed usage for SND_STR_MUSIC (0) and SND_STR_SFX_2Unk (2), but this might be coincidental
        // Test showed usage mostly for fading music out, during gameplay or during menu switches

        // FUNCTION: STRONGHOLDCRUSADER 0x00479AF0
        void SoundSystem::setStreamAndSampleVolumeUnk(SHC_SoundStreamInt sndStreamIndex, int volumeParam)
        {
            if (!(this->waveOutOpenUnk_0x8 && this->streamActiveUnk_0x20[sndStreamIndex])) {
                return;
            }

            if (sndStreamIndex == enums::SND_STR_MUSIC) {
                AIL_set_sample_volume(this->musicSampleUnk_0x170, (this->streamVolume[0] * volumeParam) / 100);
            } else {
                AIL_set_stream_volume(
                    this->stream_0xc[sndStreamIndex], (this->streamVolume[sndStreamIndex] * volumeParam) / 100);
            }
            this->streamFileVolumeCurrentUnk_0x5c[sndStreamIndex] = volumeParam;
        }

    }
}
}
