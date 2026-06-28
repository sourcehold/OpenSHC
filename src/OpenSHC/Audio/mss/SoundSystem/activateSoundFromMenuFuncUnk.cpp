#include "../SoundSystem.func.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047B870
        void SoundSystem::activateSoundFromMenuFuncUnk()
        {
            if (!this->waveOutOpenUnk_0x8) {
                return;
            }
            this->soundActiveUnk_0x0 = true;
            MACRO_CALL_MEMBER(SoundSystem_Func::playSomeMusicUnk, this)(
                this->currIdSoundFilenameUnk_0x84, this->streamFlagsUnkAndLoopCount_0x34[0]);
        }
    }

}
}
