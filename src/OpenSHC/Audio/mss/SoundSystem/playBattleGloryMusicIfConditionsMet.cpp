#include "../SoundSystem.func.hpp"

#include "OpenSHC/Globals/DAT_SoundEffectsHelperData1.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047A580
        void SoundSystem::playBattleGloryMusicIfConditionsMet()
        {
            if (DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.field0_0x0 == 5
                && DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.field6_0x18 == 0
                && DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.troopValueLevel != 0
                && DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.musicTracker == 0
                && DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.volumeLevel != 1
                && DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.field7_0x1c == 0) {
                DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.musicTracker = 1;
                MACRO_CALL_MEMBER(SoundSystem_Func::setSomeSoundTime, this)();
                MACRO_CALL_MEMBER(SoundSystem_Func::setupVolumeAndSoundIDWithMultiplier, this)(
                    DE::SHCDE::MUSIC_TUNE_BATTLE_L2_GLORY1, 100);
            }
        }

    }
}
}
