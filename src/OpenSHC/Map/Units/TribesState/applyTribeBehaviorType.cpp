#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005221A0
        void TribesState::applyTribeBehaviorType(int attackWave, SomeTribeBehaviorType tribeBehaviorType)
        {
            Tribe* psVar2;
            int iVar1 = DAT_TroopValueState::instance.attackInfo.someCounter1;
            psVar2 = &this->tribes[1];
            do {
                if (psVar2->tribeState && psVar2->attackWave == attackWave
                    && (int)(short)psVar2->tribeBehaviorType != tribeBehaviorType
                    && psVar2->attackInfo_someCounter1 != iVar1) {
                    psVar2->tribeBehaviorType = (SomeTribeBehaviorTypeShort)tribeBehaviorType;
                    psVar2->unknownAttackRelatedUpdateCounter = 0;
                }
                psVar2 = psVar2 + 0x19a;
            } while ((int)psVar2 < 0x176261c);
        }

    }
}
}
