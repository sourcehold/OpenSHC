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
                = DAT_SpeechDefinedData::instance.field5_0x41eb04[ambientSoundIndexUnk].volumeUnk_0x28
                      [DAT_SpeechDefinedData::instance.field5_0x41eb04[ambientSoundIndexUnk].field3_0x44];
            if (ambientSoundIndexUnk == 5) {
                MACRO_CALL_MEMBER(MSS::SoundSystem_Func::playSoundOnSfxSoundStream2, DAT_SoundSystemState::ptr)(
                    DAT_SpeechDefinedData::instance.field5_0x41eb04[ambientSoundIndexUnk].ambientWavs_0x8
                        [DAT_SpeechDefinedData::instance.field5_0x41eb04[ambientSoundIndexUnk].field3_0x44],
                    50);
            } else {
                MACRO_CALL_MEMBER(MSS::SoundSystem_Func::playSoundOnSoundStream2, DAT_SoundSystemState::ptr)(
                    DAT_SpeechDefinedData::instance.field5_0x41eb04[ambientSoundIndexUnk].ambientWavs_0x8
                        [DAT_SpeechDefinedData::instance.field5_0x41eb04[ambientSoundIndexUnk].field3_0x44]);
            }
            DAT_SpeechDefinedData::instance.field5_0x41eb04[ambientSoundIndexUnk].field3_0x44++;
            if (DAT_SpeechDefinedData::instance.field5_0x41eb04[ambientSoundIndexUnk].field3_0x44
                >= DAT_SpeechDefinedData::instance.field5_0x41eb04[ambientSoundIndexUnk].field0_0x0) {
                DAT_SpeechDefinedData::instance.field5_0x41eb04[ambientSoundIndexUnk].field3_0x44 = 0;
            }
        }

    }
}
}
