#include "../SoundSystem.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Audio/MSS/SoundFlagsAndLoopCountBitwiseFlagEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_SFXDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047B670
        void SoundSystem::playSpeechSfx(char* soundFileName)
        {
            if (!this->waveOutOpenUnk_0x8) {
                return;
            }
            if ((this->streamFlagsUnkAndLoopCount_0x34[enums::SND_STR_SPEECH_1] & FLAG_SOUND_UNINTERRUPTABLE)
                && MACRO_CALL_MEMBER(SoundSystem_Func::isSampleOrStreamPlaying, this)(enums::SND_STR_SPEECH_1)) {
                return;
            }
            if (DAT_GameCore::instance.gameMode_2 == Game::GM_CRUSADER_TUTORIAL) {
                return;
            }
            ++DAT_SFXDefinedData::instance.field6_0x4e0;
            if (DAT_SFXDefinedData::instance.field6_0x4e0 > 4) {
                DAT_SFXDefinedData::instance.field6_0x4e0 = 3;
            }
            if (this->streamActiveUnk_0x20[DAT_SFXDefinedData::instance.field6_0x4e0]) {
                MACRO_CALL_MEMBER(SoundSystem_Func::endSoundStream, this)(
                    (SHC_SoundStream)DAT_SFXDefinedData::instance.field6_0x4e0);
            }
            int const nextVolume
                = MACRO_CALL_MEMBER(SFX::SFXState_Func::getSoundVolumeForFilename, DAT_SFXState::ptr)(soundFileName);
            this->streamFileVolumeNextUnk_0x48[3] = nextVolume;
            this->streamFileVolumeNextUnk_0x48[4] = nextVolume;
            MACRO_CALL_MEMBER(SoundSystem_Func::playSoundStreamUnk, this)(
                (SHC_SoundStream)DAT_SFXDefinedData::instance.field6_0x4e0, soundFileName, 1);
            DAT_SoundSystemState::instance.lastUsedSpeechStreamUnk_0x3284 = DAT_SFXDefinedData::instance.field6_0x4e0;
        }
    }

}
}
