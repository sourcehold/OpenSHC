#include "../SoundSystem.func.hpp"

#include "OpenSHC/Globals/DAT_SoundEffectsHelperData1.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047A660
        void SoundSystem::setupLossMusic()
        {
            MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundIDWithMultiplier, this)(
                DAT_SoundEffectsHelperData1::ptr->DAT_LossMusicVariation + DE::SHCDE::MUSIC_TUNE_LOSE1, 100);
            ++DAT_SoundEffectsHelperData1::ptr->DAT_LossMusicVariation;
            if (DAT_SoundEffectsHelperData1::ptr->DAT_LossMusicVariation > 1) {
                DAT_SoundEffectsHelperData1::ptr->DAT_LossMusicVariation = 0;
            }
        }

    }
}
}
