#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00518930
        void TroopValueState::assignBehaviorTypeToNearbyTribes(
            SomeTribeBehaviorType param_1, undefined4 param_2, short param_3, short param_4)
        {
            int iVar1;
            int iVar2;
            int iVar3;
            iVar3 = 0;
            this->attackInfo.unknownTribeCounterRelated = 0;
            if (0 < this->attackInfo.tribeIDArraySize) {
                do {
                    iVar1 = this->attackInfo.tribeIDArray[iVar3];
                    if ((this->attackInfo.tribeRelatedArrayValue0UpTo12[iVar3] < 0xb)
                        && (iVar2 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                          calculateCanPlayerUnitsNavigateToAreaFromArea,
                                DAT_PathFindingState::ptr)(DAT_TribesState::instance.tribes[iVar1].owner,
                                (dword)((int)((
                                    int)(short)DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance
                                        .units[DAT_TribesState::instance.tribes[iVar1].selectionTargetUnitID]
                                        .tile])),
                                (dword)((int)(this->attackInfo.someArea)), 1),
                            iVar2 != 0)) {
                        DAT_TribesState::instance.tribes[iVar1].attackInfo_someCounter1
                            = (short)this->attackInfo.someCounter1;
                        DAT_TribesState::instance.tribes[iVar1].someCounter1
                            = (short)this->attackInfo.unknownTribeCounterRelated;
                        this->attackInfo.unknownTribeCounterRelated = this->attackInfo.unknownTribeCounterRelated + 1;
                        DAT_TribesState::instance.tribes[iVar1].someUpdateUpperLimit
                            = ((short)iVar3 + 1) * param_4 + param_3;
                        DAT_TribesState::instance.tribes[iVar1].tribeBehaviorType = (undefined2)param_1;
                        if (4 < this->attackInfo.unknownTribeCounterRelated) {}
                    }
                    iVar2 = this->attackInfo.tribeIDArraySize;
                    iVar3 = iVar3 + 1;
                    DAT_TribesState::instance.tribes[iVar1].unknownAttackRelatedUpdateCounter = 0;
                } while (iVar3 < iVar2);
            }
        }

    }
}
}
