#include "../SFXState.func.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // FUNCTION: STRONGHOLDCRUSADER 0x00449CC0
        void SFXState::setSoundWithVariation(int unknownSfxID, int volumePercentage)
        {
            if (this->DAT_SoundStructures2[unknownSfxID].variationCount <= 0) {
                return;
            }
            if (volumePercentage < 0) {
                volumePercentage = 0;
            } else if (127 < volumePercentage) {
                volumePercentage = 127;
            }
            int const variantSoundId = this->DAT_SoundStructures2[unknownSfxID].soundID
                + this->DAT_SoundStructures2[unknownSfxID].variationCounter++;
            if (this->DAT_SoundStructures2[unknownSfxID].variationCounter
                >= this->DAT_SoundStructures2[unknownSfxID].variationCount) {
                this->DAT_SoundStructures2[unknownSfxID].variationCounter = 0;
            }
            this->DAT_SoundStructures[variantSoundId].volumePercentage = volumePercentage;
            ++this->DAT_SoundStructures[variantSoundId].scheduledPlayCounter;
            this->DAT_SoundStructures[variantSoundId].samplePan = 64;
            ++this->DAT_SFXCounter1;
            if (this->DAT_SFXCounter1 > this->highestSFXCounter) {
                this->highestSFXCounter = this->DAT_SFXCounter1;
            }
        }

    }
}
}
