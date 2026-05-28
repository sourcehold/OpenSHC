#include "../SoundSystem.func.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047A080
        void SoundSystem::resumeAudioSample()
        {
            if (!(this->waveOutOpenUnk_0x8 && this->digSndDriver_0x4)) {
                return;
            }

            for (int streamIndex = 0; streamIndex < 5; ++streamIndex) {
                if (this->streamPaused_0x15c[streamIndex] == 0) {
                    continue;
                }

                this->streamPaused_0x15c[streamIndex] = 0;
                if (streamIndex == enums::SND_STR_MUSIC) {
                    AIL_resume_sample(this->musicSampleUnk_0x170);
                } else {
                    AIL_pause_stream(this->stream_0xc[streamIndex], 1);
                }
            }

            for (int soundIndex = 1; soundIndex < this->loadedSoundsCountAndIndex_0x316c; ++soundIndex) {
                if (this->soundFileCurrSampleNum_0x28c[soundIndex] < 0 || this->samplePaused_0x31f4[soundIndex] == 0) {
                    continue;
                }

                this->samplePaused_0x31f4[this->soundFileCurrSampleNum_0x28c[soundIndex]] = 0;
                AIL_resume_sample(this->sample_0x190[this->soundFileCurrSampleNum_0x28c[soundIndex] + -1]);
            }
        }

    }
}
}
