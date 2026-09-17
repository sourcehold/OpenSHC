#include "../SFXState.func.hpp"

#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SFX_Cooldown_WeAreUnderAttack.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044A6E0
        void SFXState::playSFXWeAreUnderAttack()
        {
            if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                return;
            }
            if (60000 <= timeGetTime() - DAT_SFX_Cooldown_WeAreUnderAttack::instance) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                    s_General_Warning10_wav_005a4dd8);
            }
            DAT_SFX_Cooldown_WeAreUnderAttack::instance = timeGetTime();
        }

    }
}
}
