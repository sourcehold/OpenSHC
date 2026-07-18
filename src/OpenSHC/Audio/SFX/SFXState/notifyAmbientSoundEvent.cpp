#include "../SFXState.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044A0D0
        void SFXState::notifyAmbientSoundEvent(int ambientSoundType)
        {
            if (DAT_GameCore::instance.gamePausedLogical) {
                return;
            }
            ++this->ambientEventCounters[ambientSoundType][0];
        }

    }
}
}
