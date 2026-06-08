#include "../SoundSystem.func.hpp"

#include "OpenSHC/Random/RNG.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_SoundEffectsHelperData1.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047A130
        void SoundSystem::mapLoadingAndLaunchGameRelated1()
        {
            DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.field0_0x0 = 1;
            DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.field1_0x4 = SEC_RNG::ptr->currentNumber1 % 4;
            MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
            DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.incrementorUpTo4 = SEC_RNG::ptr->currentNumber1 % 4 + 1;
            DAT_GameCore::ptr->cowPoisonTrackerUnk = 0;
            DAT_GameCore::ptr->someSoundMatchTime_1 = DAT_GameCore::ptr->mapTimeInTicks;
            DAT_GameCore::ptr->battleLevel = 0;
            DAT_GameCore::ptr->battleLevel2 = 0;
            DAT_GameCore::ptr->field36_0x90 = 0;
            DAT_TroopValueState::ptr->attackInfo.field128078_0x469d8 = 0;
            DAT_TroopValueState::ptr->attackInfo.field128080_0x469e0 = 0;
            DAT_TroopValueState::ptr->attackInfo.field128079_0x469dc = 0;
            DAT_SoundEffectsHelperData1::ptr->field8_0x3c = 0;
        }

    }
}
}
