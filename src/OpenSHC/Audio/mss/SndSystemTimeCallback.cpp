#include "../mss.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"

#include "OpenSHC/Globals/DAT_SoundEffectsHelperData1.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047B510
        void __stdcall SndSystemTimeCallback(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
        {
            if (DAT_SoundEffectsHelperData1::instance.field14_0x54 || DAT_SoundEffectsHelperData1::instance.field15_0x58
                || !DAT_SoundSystemState::instance.waveOutOpenUnk_0x8) {
                return;
            }
            DAT_SoundEffectsHelperData1::instance.field15_0x58 = TRUE;
            if (!DAT_SoundSystemState::instance.streamPaused_0x15c[0]
                && DAT_SoundSystemState::instance.streamActiveUnk_0x20[0]) {
                if (AIL_sample_status(DAT_SoundSystemState::instance.musicSampleUnk_0x170) != SMP_PLAYING) {
                    MACRO_CALL_MEMBER(SoundSystem_Func::stopMusicPlayback, DAT_SoundSystemState::ptr)();
                } else {
                    MACRO_CALL_MEMBER(SoundSystem_Func::playMusicUnk, DAT_SoundSystemState::ptr)();
                }
            }
            DAT_SoundEffectsHelperData1::instance.field15_0x58 = FALSE;
        }

    }
}
}
