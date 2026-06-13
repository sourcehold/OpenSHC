#include "../SoundSystem.func.hpp"

#include "OpenSHC/Globals/DAT_SoundEffectsHelperData1.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047A630
        void SoundSystem::playWinMusicVariation()
        {
            MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundIDWithMultiplier, this)(
                DAT_SoundEffectsHelperData1::ptr->DAT_WinMusicVariation + DE::SHCDE::MUSIC_TUNE_WIN1, 100);
            ++DAT_SoundEffectsHelperData1::ptr->DAT_WinMusicVariation;
            if (DAT_SoundEffectsHelperData1::ptr->DAT_WinMusicVariation > 2) {
                DAT_SoundEffectsHelperData1::ptr->DAT_WinMusicVariation = 0;
            }
        }

    }
}
}
