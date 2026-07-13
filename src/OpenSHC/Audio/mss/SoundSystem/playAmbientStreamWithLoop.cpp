#include "../SoundSystem.func.hpp"

#include "OpenSHC/Audio/MSS/SoundFlagsAndLoopCountBitwiseFlagEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_SFXDefinedData.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047B700
        void SoundSystem::playAmbientStreamWithLoop(char* param_1)
        {
            if (!this->waveOutOpenUnk_0x8) {
                return;
            }
            if (this->streamActiveUnk_0x20[DAT_SFXDefinedData::instance.field7_0x4e4]) {
                MACRO_CALL_MEMBER(SoundSystem_Func::endSoundStream, this)(
                    (SHC_SoundStream)DAT_SFXDefinedData::instance.field7_0x4e4);
            }
            SHC_SoundStream const soundStream = (SHC_SoundStream)DAT_SFXDefinedData::instance.field7_0x4e4;
            this->streamFileVolumeNextUnk_0x48[3] = 100;
            this->streamFileVolumeNextUnk_0x48[4] = 100;
            if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_UNUSED_EXTREME_AD) {
                MACRO_CALL_MEMBER(SoundSystem_Func::playSoundStreamUnk, this)(soundStream, param_1, 1);
            } else {
                MACRO_CALL_MEMBER(SoundSystem_Func::playSoundStreamUnk, this)(
                    soundStream, param_1, FLAG_SOUND_UNKNOWN_FLAG_1 | 1);
            }
        }
    }

}
}
