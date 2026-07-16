#include "../SFXState.func.hpp"

#include "OpenSHC/Audio.func.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044AB70
        SFXState* SFXState::Constructor_SFXState()
        {
            for (int i = 0; i < 1000; ++i) {
                this->DAT_SoundStructures[i].scheduledPlayCounter = 0;
                this->DAT_SoundStructures[i].volumePercentage = 100;
                this->DAT_SoundStructures[i].samplePan = 64;
            }
            this->DAT_SFXCounter1 = 0;
            MACRO_CALL_MEMBER(SFXState_Func::Constructor_SFXState_resetAmbientEventCounters, this)();
            this->highestSFXCounter = 0;
            MACRO_CALL(Audio_Func::ResetGreatestLordGenieSpeechState)();
            return this;
        }

        // FUNCTION: STRONGHOLDCRUSADER 0x0044A050
        void SFXState::Constructor_SFXState_resetAmbientEventCounters()
        {
            for (int i = 0; i < 10; ++i) {
                this->ambientEventCounters[i][1] = 0;
                this->ambientEventCounters[i][0] = 0;
            }
        }

    }
}
}
