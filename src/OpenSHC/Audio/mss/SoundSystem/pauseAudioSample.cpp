#include "../SoundSystem.func.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x00479FC0
        void SoundSystem::pauseAudioSample()
        {
            if (!(this->waveOutOpenUnk_0x8 && this->digSndDriver_0x4)) {
                return;
            }

            for (int streamIndex = 0; streamIndex < 5; ++streamIndex) {
                if (MACRO_CALL_MEMBER(SoundSystem_Func::isSampleOrStreamPlaying, this)(streamIndex)) {
                    this->streamPaused_0x15c[streamIndex] = 1;
                    if (streamIndex == enums::SND_STR_MUSIC) {
                        AIL_stop_sample(this->musicSampleUnk_0x170);
                    } else {
                        AIL_pause_stream(this->stream_0xc[streamIndex], 0);
                    }
                } else {
                    this->streamPaused_0x15c[streamIndex] = 0;
                }
            }

            for (int soundIndex = 1; soundIndex < this->loadedSoundsCountAndIndex_0x316c; ++soundIndex) {
                if (this->soundFileCurrSampleNum_0x28c[soundIndex] < 0) {
                    continue;
                }
                if (MACRO_CALL_MEMBER(SoundSystem_Func::getAndUpdateSampleStatus, this)(soundIndex)) {
                    this->samplePaused_0x31f4[this->soundFileCurrSampleNum_0x28c[soundIndex]] = 1;
                    AIL_stop_sample(this->sample_0x190[this->soundFileCurrSampleNum_0x28c[soundIndex] + -1]);
                }
            }
        }

    }
}
}
