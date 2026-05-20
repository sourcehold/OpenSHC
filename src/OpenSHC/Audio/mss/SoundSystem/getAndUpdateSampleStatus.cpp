#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x00479D90
        BOOLEnum SoundSystem::getAndUpdateSampleStatus(int soundIndex)
        {
            if (!this->waveOutOpenUnk_0x8) {
                return FALSE;
            }
            if (this->soundFileCurrSampleNum_0x28c[soundIndex] < 0) {
                return FALSE;
            }

            unsigned int const status
                = AIL_sample_status(this->sample_0x190[this->soundFileCurrSampleNum_0x28c[soundIndex] + -1]);
            if (status == SMP_PLAYING) {
                return TRUE;
            }

            this->sampleSoundIndex_0x20c[this->soundFileCurrSampleNum_0x28c[soundIndex]] = 0;
            this->soundFileCurrSampleNum_0x28c[soundIndex] = -1;
            return FALSE;
        }

    }
}
}
