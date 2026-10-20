#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005221A0
        void TribesState::applyTribeBehaviorType(int attackWave, SomeTribeBehaviorType tribeBehaviorType)
        {
            int iVar1 = DAT_TroopValueState::instance.attackInfo.someCounter1;
            /*
              The original walks the global instance, not `this`: it loads the tribe
              address as an absolute (`mov eax, TribesState::instance + 1520`) and ends the
              loop against another absolute rather than a `this`-relative one.
             */
            for (int _tribeID = 1; _tribeID < 1250; _tribeID = _tribeID + 1) {
                Tribe& _tribe = DAT_TribesState::instance.tribes[_tribeID];
                if (_tribe.tribeState && _tribe.attackWave == attackWave
                    && (int)(short)_tribe.tribeBehaviorType != tribeBehaviorType
                    && _tribe.attackInfo_someCounter1 != iVar1) {
                    _tribe.tribeBehaviorType = (SomeTribeBehaviorTypeShort)tribeBehaviorType;
                    _tribe.unknownAttackRelatedUpdateCounter = 0;
                }
            }
        }

    }
}
}
