#include "../MissingResourceState.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Audio {

    // FUNCTION: STRONGHOLDCRUSADER 0x00471720
    void MissingResourceState::playResourceLackSFX(int resourceTextElement, ResourceLackSFX resourceType)
    {
        MACRO_CALL(Global_Func::ActivateGameSpeedAndResourceLackDisplayElementUnk)(
            (UI::Enums::DisplayElementID)(resourceTextElement + UI::Enums::DEID_IN_GAME_CHAT_Unk), resourceType, 5000);
        if (MACRO_CALL_MEMBER(MSS::SoundSystem_Func::shouldSoundXNotBePlaying, DAT_SoundSystemState::ptr)()) {
            return;
        }

        int _randomIndex = SEC_RNG::instance.currentNumber1 % 10;
        if (3 < _randomIndex) {
            _randomIndex = 0;
        }
        MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
        switch (resourceType) {
        case SFX::RLSFX_IRON:
            MACRO_CALL_MEMBER(SFX::SFXState_Func::PlaySpeechSFX, DAT_SFXState::ptr)(
                (SFX::SpeechEffectID)(_randomIndex + SFX::SEID_RESOURCE_NEED8));
            break;
        case SFX::RLSFX_PITCH:
            MACRO_CALL_MEMBER(SFX::SFXState_Func::PlaySpeechSFX, DAT_SFXState::ptr)(
                (SFX::SpeechEffectID)(_randomIndex + SFX::SEID_RESOURCE_NEED12));
            break;
        case SFX::RLSFX_GOLD:
            MACRO_CALL_MEMBER(SFX::SFXState_Func::PlaySpeechSFX, DAT_SFXState::ptr)(
                (SFX::SpeechEffectID)(_randomIndex + SFX::SEID_RESOURCE_NEED16));
            break;
        case SFX::RLSFX_PARTIAL_STONEUnk:
            MACRO_CALL_MEMBER(SFX::SFXState_Func::PlaySpeechSFX, DAT_SFXState::ptr)(SFX::SEID_RESOURCE_NEED20);
            break;
        case SFX::RLSFX_WOOD:
            MACRO_CALL_MEMBER(SFX::SFXState_Func::PlaySpeechSFX, DAT_SFXState::ptr)(
                (SFX::SpeechEffectID)(_randomIndex + SFX::SEID_RESOURCE_NEED21));
            break;
        case SFX::RLSFX_STONE:
            MACRO_CALL_MEMBER(SFX::SFXState_Func::PlaySpeechSFX, DAT_SFXState::ptr)(
                (SFX::SpeechEffectID)(_randomIndex + SFX::SEID_RESOURCE_NEED25));
            break;
        }
    }

}
}
