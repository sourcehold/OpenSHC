// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../SoundSystem.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047b250
        void SoundSystem::meth_0x47b250(char* filename)
        {
            if (!this->waveOutOpenUnk_0x8) {
                return;
            }
            strcpy(this->currIdSoundFilenameUnk_0x84, filename);
            this->currIdSoundFileVolumeUnk_0x150
                = MACRO_CALL_MEMBER(SFX::SFXState_Func::getSoundVolumeForFilename, DAT_SFXState::ptr)(filename);
            if (this->mbr_0x154 == 1) {
                this->streamFileVolumeNextUnk_0x48[0] = 0;
            } else {
                this->streamFileVolumeNextUnk_0x48[0] = (this->mbr_0x14c * this->currIdSoundFileVolumeUnk_0x150) / 100;
            }
            UnkSoundFlagsAndLoopCount const unkSoundFlagsAndLoopCount = {};
            MACRO_CALL_MEMBER(SoundSystem_Func::playSoundStreamUnk, this)(
                enums::SND_STR_MUSIC, filename, unkSoundFlagsAndLoopCount);
            this->streamFileVolumeNextUnk_0x48[0] = (this->mbr_0x14c * this->currIdSoundFileVolumeUnk_0x150) / 100;
        }

    }
}
}
