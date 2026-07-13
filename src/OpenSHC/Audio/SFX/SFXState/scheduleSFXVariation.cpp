#include "../SFXState.func.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // FUNCTION: STRONGHOLDCRUSADER 0x00449D50
        void SFXState::scheduleSFXVariation(int sfxGroupID, int variationIndex)
        {
            if (variationIndex > this->DAT_SoundStructures2[sfxGroupID].variationCount - 1 || variationIndex < 0) {
                return;
            }
            int const soundId = this->DAT_SoundStructures2[sfxGroupID].soundID + variationIndex;
            this->DAT_SoundStructures[soundId].scheduledPlayCounter++;
            this->DAT_SoundStructures[soundId].volumePercentage
                = this->DAT_SoundStructures[soundId].baseVolumePercentageUnk;
            this->DAT_SoundStructures[soundId].samplePan = 64;
            ++this->DAT_SFXCounter1 = this->DAT_SFXCounter1;
            if (this->DAT_SFXCounter1 > this->highestSFXCounter) {
                this->highestSFXCounter = this->DAT_SFXCounter1;
            }
        }

    }
}
}
