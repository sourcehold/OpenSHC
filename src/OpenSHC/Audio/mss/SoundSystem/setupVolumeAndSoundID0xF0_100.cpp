#include "../SoundSystem.func.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047A310
        void SoundSystem::setupVolumeAndSoundID0xF0_100()
        {
            MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundIDWithMultiplier, this)(
                DE::SHCDE::MUSIC_TUNE_HAPPY2, 100);

            if (this->sec_Section1055_0x3274 != 0 && this->sec_Section1055_0x3274 != 0xf) {
                MACRO_CALL_MEMBER(SoundSystem_Func::setSomeSoundTime, this)();
            }
        }
    }

}
}
