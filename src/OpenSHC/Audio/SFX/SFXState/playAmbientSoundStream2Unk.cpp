#include "../SFXState.func.hpp"

#include "OpenSHC/Audio/mss/SoundSystem.func.hpp"

#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_SpeechDefinedData.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044A1B0
        void SFXState::playAmbientSoundStream2Unk(int ambientSoundIndexUnk)
        {
            if (MACRO_CALL_MEMBER(MSS::SoundSystem_Func::isSampleOrStreamPlaying, DAT_SoundSystemState::ptr)(
                    MSS::enums::SND_STR_SFX_2Unk)) {
                return;
            }
            DAT_SoundSystemState::instance.streamFileVolumeNextUnk_0x48[2]
                = DAT_SpeechDefinedData::instance.AmbientSounds[ambientSoundIndexUnk].volumeUnk_0x28
                      [DAT_SpeechDefinedData::instance.AmbientSounds[ambientSoundIndexUnk].variationIndex];
            if (ambientSoundIndexUnk == 5) {
                MACRO_CALL_MEMBER(MSS::SoundSystem_Func::playSoundOnSfxSoundStream2, DAT_SoundSystemState::ptr)(
                    DAT_SpeechDefinedData::instance.AmbientSounds[ambientSoundIndexUnk].ambientWavs_0x8
                        [DAT_SpeechDefinedData::instance.AmbientSounds[ambientSoundIndexUnk].variationIndex],
                    50);
            } else {
                MACRO_CALL_MEMBER(MSS::SoundSystem_Func::playSoundOnSoundStream2, DAT_SoundSystemState::ptr)(
                    DAT_SpeechDefinedData::instance.AmbientSounds[ambientSoundIndexUnk].ambientWavs_0x8
                        [DAT_SpeechDefinedData::instance.AmbientSounds[ambientSoundIndexUnk].variationIndex]);
            }
            DAT_SpeechDefinedData::instance.AmbientSounds[ambientSoundIndexUnk].variationIndex++;
            if (DAT_SpeechDefinedData::instance.AmbientSounds[ambientSoundIndexUnk].variationIndex
                >= DAT_SpeechDefinedData::instance.AmbientSounds[ambientSoundIndexUnk].variationCount) {
                DAT_SpeechDefinedData::instance.AmbientSounds[ambientSoundIndexUnk].variationIndex = 0;
            }
        }

    }
}
}
