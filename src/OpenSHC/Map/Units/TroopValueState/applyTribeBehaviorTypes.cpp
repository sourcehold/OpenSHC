#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::SomeTribeBehaviorType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00518870
        void TroopValueState::applyTribeBehaviorTypes(
            SomeTribeBehaviorType tribeBehaviorType, SomeTribeBehaviorType tribeBehaviorType2, int off1, int off2)
        {
            int assignedCount = 0;
            // Stored from the local rather than as a literal: the literal form costs the register allocation.
            DAT_TroopValueState::instance.attackInfo.unknownTribeCounterRelated = assignedCount;
            for (int index = 0; index < DAT_TroopValueState::instance.attackInfo.tribeIDArraySize; ++index) {
                int const tribeID = DAT_TroopValueState::instance.attackInfo.tribeIDArray[index];
                if (11 <= DAT_TroopValueState::instance.attackInfo.tribeRelatedArrayValue0UpTo12[index]) {
                    if (tribeBehaviorType2 != (SomeTribeBehaviorType)0) {
                        DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType
                            = (SomeTribeBehaviorTypeShort)tribeBehaviorType2;
                    }
                } else {
                    DAT_TribesState::instance.tribes[tribeID].someUpdateUpperLimit
                        = ((short)index + 1) * (short)off2 + (short)off1;
                    short const someCounter1 = (short)DAT_TroopValueState::instance.attackInfo.someCounter1;
                    DAT_TribesState::instance.tribes[tribeID].someCounter1 = (short)assignedCount;
                    ++assignedCount;
                    DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType
                        = (SomeTribeBehaviorTypeShort)tribeBehaviorType;
                    DAT_TribesState::instance.tribes[tribeID].attackInfo_someCounter1 = someCounter1;
                    DAT_TroopValueState::instance.attackInfo.unknownTribeCounterRelated = assignedCount;
                }
                DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
            }
        }

    }
}
}
