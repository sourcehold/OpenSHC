#include "../SoundSystem.func.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x00479F30
        void SoundSystem::deactivateSoundFromMenuFuncUnk()
        {
            if (!this->waveOutOpenUnk_0x8) {
                return;
            }

            for (int i = 0; i < 5; ++i) {
                unsigned int const copy = *((unsigned int*)&this->streamFlagsUnkAndLoopCount_0x34[i]) & 0x7fffffff;
                this->streamFlagsUnkAndLoopCount_0x34[i] = *((UnkSoundFlagsAndLoopCount*)&copy);
                MACRO_CALL_MEMBER(SoundSystem_Func::endSoundStream, this)(i);
            }

            for (int i = 0; i < 31; ++i) {
                AIL_end_sample(this->sample_0x190[i]);
                this->sampleSoundIndex_0x20c[i + 1] = 0;
            }

            for (int i = 1; i < this->loadedSoundsCountAndIndex_0x316c; ++i) {
                this->soundFileCurrSampleNum_0x28c[i] = -1;
            }
            this->soundActiveUnk_0x0 = 0;
        }

    }
}
}
