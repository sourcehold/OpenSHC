#include "../TroopValueState.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/string-macros.hpp"

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
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playOnSpeechSfxStream, DAT_SFXState::ptr)(
                    S_DRUMHORN_WAV_005ABB58);
                break;
            case 2:
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playOnSpeechSfxStream, DAT_SFXState::ptr)(
                    S_BATTLEHORN_WAV_005A77D8);
                break;
            case 3:
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playOnSpeechSfxStream, DAT_SFXState::ptr)(
                    S_BATTLEHORN_WAV_005A77D8);
                break;
            case 4:
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playOnSpeechSfxStream, DAT_SFXState::ptr)(
                    S_BATTLEHORN_WAV_005A77D8);
                break;
            }
            DAT_TroopValueState::instance.attackInfo.attackAlarmPlayed = TRUE;
        }

    }
}
}
