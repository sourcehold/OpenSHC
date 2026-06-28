#include "../SoundSystem.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047B7D0
        void SoundSystem::playOnSfx1SoundStreamUnk(char* soundFileName, SoundFlagsAndLoopCount flagsAndLoopCount)
        {
            this->streamFileVolumeNextUnk_0x48[1]
                = MACRO_CALL_MEMBER(SFX::SFXState_Func::getSoundVolumeForFilename, DAT_SFXState::ptr)(soundFileName);
            MACRO_CALL_MEMBER(SoundSystem_Func::playSoundStreamUnk, this)(
                enums::SND_STR_SFX_1Unk, soundFileName, flagsAndLoopCount);
        }
    }

}
}
