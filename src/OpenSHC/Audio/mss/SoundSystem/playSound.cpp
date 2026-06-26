#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/string-literals.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x00479DF0
        void SoundSystem::playSound(int soundIndex)
        {
            if (!this->waveOutOpenUnk_0x8 || !this->soundActiveUnk_0x0
                || this->soundFileCurrSampleNum_0x28c[soundIndex] < 0) {
                return;
            }

            AIL_set_named_sample_file(this->sample[this->soundFileCurrSampleNum_0x28c[soundIndex]], s__wav_005a6cc4,
                this->soundFileDataPointerArray_0x122c[soundIndex], this->soundFileSizes_0x21cc[soundIndex], 0);
            AIL_start_sample(this->sample[this->soundFileCurrSampleNum_0x28c[soundIndex]]);
        }

    }
}
}
