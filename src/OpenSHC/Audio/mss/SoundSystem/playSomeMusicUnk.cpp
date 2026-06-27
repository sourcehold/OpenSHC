// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../SoundSystem.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047B760
        void SoundSystem::playSomeMusicUnk(char* filename, SoundFlagsAndLoopCount flagsAndLoop)
        {
            if (!this->waveOutOpenUnk_0x8) {
                return;
            }
            strcpy(this->currIdSoundFilenameUnk_0x84, filename);
            int const _volume
                = MACRO_CALL_MEMBER(SFX::SFXState_Func::getSoundVolumeForFilename, DAT_SFXState::ptr)(filename);
            this->currIdSoundFileVolumeUnk_0x150 = _volume;
            this->streamFileVolumeNextUnk_0x48[0] = (this->mbr_0x14c * _volume) / 100;
            MACRO_CALL_MEMBER(SoundSystem_Func::playSoundStreamUnk, this)(enums::SND_STR_MUSIC, filename, flagsAndLoop);
        }
    }

}
}
