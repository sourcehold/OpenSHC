#include "../TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005221A0
        void TribesState::applyTribeBehaviorType(int attackWave, SomeTribeBehaviorType tribeBehaviorType)
        {
            int const attackInfoCounter1 = DAT_TroopValueState::instance.attackInfo.someCounter1;
            for (int _tribeID = 1; _tribeID < (int)_countof(DAT_TribesState::instance.tribes); ++_tribeID) {
                Tribe& _tribe = DAT_TribesState::instance.tribes[_tribeID];
                if (_tribe.tribeState && _tribe.attackWave == attackWave
                    && _tribe.tribeBehaviorType != tribeBehaviorType
                    && _tribe.attackInfo_someCounter1 != attackInfoCounter1) {
                    _tribe.tribeBehaviorType = tribeBehaviorType;
                    _tribe.unknownAttackRelatedUpdateCounter = 0;
                }
            }
        }

    }
}
}
