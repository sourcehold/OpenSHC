#include "../SoundSystem.func.hpp"

#include "OpenSHC/Globals/DAT_SoundEffectsHelperData1.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x00479C80
        void SoundSystem::findSamplePlaceForSoundUnk(int soundIndex)
        {
            if (this->soundFileCurrSampleNum_0x28c[soundIndex] >= 0) {
                return;
            }

            DAT_SoundEffectsHelperData1::ptr->DAT_NumberOfUsedSoundSamplePlaces = 0;

            for (int i = 1; i < 32; ++i) {
                if (this->sampleSoundIndex_0x20c[i]) {
                    ++DAT_SoundEffectsHelperData1::ptr->DAT_NumberOfUsedSoundSamplePlaces;
                }
            }

            for (int i = 1; i < 32; ++i) {
                if (this->sampleSoundIndex_0x20c[i]) {
                    continue;
                }
                this->sampleSoundIndex_0x20c[i] = soundIndex;
                this->soundFileCurrSampleNum_0x28c[soundIndex] = i;
                return;
            }
        }

    }
}
}
