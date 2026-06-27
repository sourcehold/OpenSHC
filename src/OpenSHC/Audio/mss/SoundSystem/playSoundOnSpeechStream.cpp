#include "../SoundSystem.func.hpp"

#include "OpenSHC/Audio/MSS/SoundFlagsAndLoopCountBitwiseFlagEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_SFXDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047B5F0
        void SoundSystem::playSoundOnSpeechStream(char* filename)
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
            ++DAT_SFXDefinedData::instance.DAT_LastUsedSpeechStream;
            if (DAT_SFXDefinedData::instance.DAT_LastUsedSpeechStream > 4) {
                DAT_SFXDefinedData::instance.DAT_LastUsedSpeechStream = 3;
            }
            if (this->streamActiveUnk_0x20[DAT_SFXDefinedData::instance.DAT_LastUsedSpeechStream]) {
                MACRO_CALL_MEMBER(SoundSystem_Func::endSoundStream, this)(
                    (SHC_SoundStream)DAT_SFXDefinedData::instance.DAT_LastUsedSpeechStream);
            }
            SHC_SoundStream const speechStream = (SHC_SoundStream)DAT_SFXDefinedData::instance.DAT_LastUsedSpeechStream;
            this->streamFileVolumeNextUnk_0x48[3] = 100;
            this->streamFileVolumeNextUnk_0x48[4] = 100;
            MACRO_CALL_MEMBER(SoundSystem_Func::playSoundStreamUnk, this)(speechStream, filename, 1);
            DAT_SoundSystemState::instance.lastUsedSpeechStreamUnk_0x3284
                = DAT_SFXDefinedData::instance.DAT_LastUsedSpeechStream;
        }

    }
}
}
