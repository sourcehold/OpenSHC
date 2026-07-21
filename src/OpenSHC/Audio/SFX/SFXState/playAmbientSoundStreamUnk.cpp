#include "../SFXState.func.hpp"

#include "OpenSHC/Audio/mss/SoundSystem.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_SpeechDefinedData.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044A0F0
        void SFXState::playAmbientSoundStreamUnk(AmbientSFXType ambientSoundIndexUnk)
        {
            if (MACRO_CALL_MEMBER(MSS::SoundSystem_Func::isSampleOrStreamPlaying, DAT_SoundSystemState::ptr)(
                    MSS::enums::SND_STR_SFX_1Unk)) {
                return;
            }
            DAT_SoundSystemState::instance.streamFileVolumeNextUnk_0x48[1]
                = DAT_SpeechDefinedData::instance.field5_0x41eb04[ambientSoundIndexUnk].volumeUnk_0x28
                      [DAT_SpeechDefinedData::instance.field5_0x41eb04[ambientSoundIndexUnk].field3_0x44];
            if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_HISTORIC_MISSION_PICTURE
                || DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_HISTORIC_MISSION_INTRO
                || DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_HISTORIC_CAMPAIGN_INTRO) {
                DAT_SoundSystemState::instance.streamFileVolumeNextUnk_0x48[1] = 127;
            }
            if (ambientSoundIndexUnk == ASFXT_BATTLE_OR_INTENSE || ambientSoundIndexUnk == ASFXT_HEAVY) {
                MACRO_CALL_MEMBER(MSS::SoundSystem_Func::playOnSfx1SoundStreamUnk, DAT_SoundSystemState::ptr)(
                    DAT_SpeechDefinedData::instance.field5_0x41eb04[ambientSoundIndexUnk].ambientWavs_0x8
                        [DAT_SpeechDefinedData::instance.field5_0x41eb04[ambientSoundIndexUnk].field3_0x44],
                    50);
            } else {
                MACRO_CALL_MEMBER(
                    MSS::SoundSystem_Func::playOnSfx1SoundStreamOnceOrOnRepeatUnk, DAT_SoundSystemState::ptr)(
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
