#include "../SFXState.func.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // FUNCTION: STRONGHOLDCRUSADER 0x00449C40
        void SFXState::setUpSFXToPlayUnk(SoundEffectID sfxOffsetInArray)
        {
            if (this->DAT_SoundStructures2[sfxOffsetInArray].variationCount <= 0) {
                return;
            }
            int const variantSoundId = this->DAT_SoundStructures2[sfxOffsetInArray].soundID
                + this->DAT_SoundStructures2[sfxOffsetInArray].variationCounter++;
            if (this->DAT_SoundStructures2[sfxOffsetInArray].variationCounter
                >= this->DAT_SoundStructures2[sfxOffsetInArray].variationCount) {
                this->DAT_SoundStructures2[sfxOffsetInArray].variationCounter = 0;
            }
            ++this->DAT_SoundStructures[variantSoundId].scheduledPlayCounter;
            this->DAT_SoundStructures[variantSoundId].volumePercentage
                = this->DAT_SoundStructures[variantSoundId].baseVolumePercentageUnk;
            this->DAT_SoundStructures[variantSoundId].samplePan = 64;
            ++this->DAT_SFXCounter1;
            if (this->DAT_SFXCounter1 > this->highestSFXCounter) {
                this->highestSFXCounter = this->DAT_SFXCounter1;
            }
        }

    }
}
}
