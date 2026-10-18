#include "OpenSHC/Map.func.hpp"
#include "../TroopValueState.func.hpp"

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
            int _size;
            int _assignedCount = 0;
            DAT_TroopValueState::instance.attackInfo.unknownTribeCounterRelated = _assignedCount;
            int _index = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.tribeIDArraySize) {
                do {
                    int const _tribeID = DAT_TroopValueState::instance.attackInfo.tribeIDArray[_index];
                    if (11 <= DAT_TroopValueState::instance.attackInfo.tribeRelatedArrayValue0UpTo12[_index]) {
                        if (tribeBehaviorType2 != (SomeTribeBehaviorType)0) {
                            DAT_TribesState::instance.tribes[_tribeID].tribeBehaviorType
                                = (SomeTribeBehaviorTypeShort)tribeBehaviorType2;
                        }
                    } else {
                        DAT_TribesState::instance.tribes[_tribeID].someUpdateUpperLimit
                            = ((short)_index + 1) * (short)off2 + (short)off1;
                        short const _someCounter1 = (short)DAT_TroopValueState::instance.attackInfo.someCounter1;
                        DAT_TribesState::instance.tribes[_tribeID].someCounter1 = (short)_assignedCount;
                        _assignedCount = _assignedCount + 1;
                        DAT_TribesState::instance.tribes[_tribeID].tribeBehaviorType
                            = (SomeTribeBehaviorTypeShort)tribeBehaviorType;
                        DAT_TribesState::instance.tribes[_tribeID].attackInfo_someCounter1 = _someCounter1;
                        DAT_TroopValueState::instance.attackInfo.unknownTribeCounterRelated = _assignedCount;
                    }
                    _size = DAT_TroopValueState::instance.attackInfo.tribeIDArraySize;
                    _index = _index + 1;
                    DAT_TribesState::instance.tribes[_tribeID].unknownAttackRelatedUpdateCounter = 0;
                } while (_index < _size);
            }
        }

    }
}
}
