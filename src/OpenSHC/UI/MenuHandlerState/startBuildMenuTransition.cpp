#include "../MenuHandlerState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F4C80
    void MenuHandlerState::startBuildMenuTransition(int transitionDuration)
    {
        this->buildMenuTransitionStartTime_0x30 = timeGetTime();
        this->buildMenuTransitionDuration_0x34 = transitionDuration;
        this->isBuildMenuTransitioning_0x18 = TRUE;
        this->buildMenuTransitionProgress_0x38 = 0;
        if (this->buildMenuTransitionDirection_0x2c < 0) {
            this->buildMenuTransitionDirection_0x2c = 1;
        } else {
            this->buildMenuTransitionDirection_0x2c = -1;
        }
        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
            OpenSHC::Audio::SFX::SEID_UNKNOWN_0x67);
    }

}
}
