#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::SomeTribeBehaviorType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00518870
        void TroopValueState::applyTribeBehaviorTypes(
            SomeTribeBehaviorType tribeBehaviorType, SomeTribeBehaviorType tribeBehaviorType2, int off1, int off2)
        {
            short sVar1;
            int _index;
            int iVar2;
            int _size;
            int _tribeID;
            iVar2 = 0;
            _index = 0;
            this->attackInfo.unknownTribeCounterRelated = 0;
            if (0 < this->attackInfo.tribeIDArraySize) {
                do {
                    _tribeID = this->attackInfo.tribeIDArray[_index];
                    if (this->attackInfo.tribeRelatedArrayValue0UpTo12[_index] < 11) {
                        DAT_TribesState::instance.tribes[_tribeID].someUpdateUpperLimit
                            = ((short)_index + 1) * (short)off2 + (short)off1;
                        sVar1 = (short)this->attackInfo.someCounter1;
                        DAT_TribesState::instance.tribes[_tribeID].someCounter1 = (short)iVar2;
                        iVar2 = iVar2 + 1;
                        DAT_TribesState::instance.tribes[_tribeID].tribeBehaviorType
                            = (SomeTribeBehaviorTypeShort)tribeBehaviorType;
                        DAT_TribesState::instance.tribes[_tribeID].attackInfo_someCounter1 = sVar1;
                        this->attackInfo.unknownTribeCounterRelated = iVar2;
                    } else if (tribeBehaviorType2 != ((SomeTribeBehaviorType)0)) {
                        DAT_TribesState::instance.tribes[_tribeID].tribeBehaviorType
                            = (SomeTribeBehaviorTypeShort)tribeBehaviorType2;
                    }
                    _size = this->attackInfo.tribeIDArraySize;
                    _index = _index + 1;
                    DAT_TribesState::instance.tribes[_tribeID].unknownAttackRelatedUpdateCounter = 0;
                } while (_index < _size);
            }
        }

    }
}
}
