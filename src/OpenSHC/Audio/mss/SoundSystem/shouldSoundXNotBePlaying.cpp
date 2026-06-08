#include "../SoundSystem.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x00479AB0
        BOOLEnum SoundSystem::shouldSoundXNotBePlaying()
        {
            if (DAT_GameState::ptr->playerDataArray[DAT_GameSynchronyState::ptr->currentPlayerSlotID]
                    .playerDeathRelated) {
                return FALSE;
            }

            if (MACRO_CALL_MEMBER(SoundSystem_Func::isSampleOrStreamPlaying, this)(enums::SND_STR_SPEECH_1)) {
                return TRUE;
            }
            if (MACRO_CALL_MEMBER(SoundSystem_Func::isSampleOrStreamPlaying, this)(enums::SND_STR_SPEECH_2)) {
                return TRUE;
            }
            return FALSE;
        }

    }
}
}
