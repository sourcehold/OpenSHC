#include "../SoundSystem.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047B830
        void SoundSystem::playSoundOnStream3Unk(char* filename, SoundFlagsAndLoopCount flagsAndLoopCount)
        {
            if (!this->waveOutOpenUnk_0x8) {
                return;
            }
            int const volume
                = MACRO_CALL_MEMBER(SFX::SFXState_Func::getSoundVolumeForFilename, DAT_SFXState::ptr)(filename);
            this->streamFileVolumeNextUnk_0x48[3] = volume;
            this->streamFileVolumeNextUnk_0x48[4] = volume;
            MACRO_CALL_MEMBER(SoundSystem_Func::playSoundStreamUnk, this)(
                enums::SND_STR_SPEECH_1, filename, flagsAndLoopCount);
            DAT_SoundSystemState::instance.lastUsedSpeechStreamUnk_0x3284 = 3;
        }
    }

}
}
