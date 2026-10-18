#include "OpenSHC/Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051B6C0
        void TroopValueState::playAttackAlarmSound()
        {
            MACRO_CALL_MEMBER(
                Audio::MSS::SoundSystem_Func::playBattleGloryMusicIfConditionsMet, DAT_SoundSystemState::ptr)();
            switch (DAT_TroopValueState::instance.attackInfo.attacker) {
            case 5:
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playOnSpeechSfxStream, DAT_SFXState::ptr)("drumhorn.wav");
                break;
            case 2:
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playOnSpeechSfxStream, DAT_SFXState::ptr)(
                    "battlehorn.wav");
                break;
            case 3:
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playOnSpeechSfxStream, DAT_SFXState::ptr)(
                    "battlehorn.wav");
                break;
            case 4:
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playOnSpeechSfxStream, DAT_SFXState::ptr)(
                    "battlehorn.wav");
                break;
            }
            DAT_TroopValueState::instance.attackInfo.attackAlarmPlayed = 1;
        }

    }
}
}
