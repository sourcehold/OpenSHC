#include "../SFXState.func.hpp"

#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // FUNCTION: STRONGHOLDCRUSADER 0x00449FF0
        void SFXState::resetScheduledSoundRequests()
        {
            for (int i = 0; i < DAT_SoundSystemState::instance.loadedSoundsCountAndIndex_0x316c + 1; ++i) {
                this->DAT_SoundStructures[i].scheduledPlayCounter = 0;
                this->DAT_SoundStructures[i].volumePercentage = 100;
                this->DAT_SoundStructures[i].samplePan = 64;
            }
            this->DAT_SFXCounter1 = 0;
            return;
        }

    }
}
}
