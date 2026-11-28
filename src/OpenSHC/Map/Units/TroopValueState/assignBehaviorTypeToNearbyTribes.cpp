#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00518930
        void TroopValueState::assignBehaviorTypeToNearbyTribes(
            SomeTribeBehaviorType param_1, undefined4 param_2, short param_3, short param_4)
        {
            DAT_TroopValueState::instance.attackInfo.unknownTribeCounterRelated = 0;
            for (int _index = 0; _index < DAT_TroopValueState::instance.attackInfo.tribeIDArraySize; ++_index) {
                int const _tribeID = DAT_TroopValueState::instance.attackInfo.tribeIDArray[_index];
                int const _area = (short)DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance
                        .units[DAT_TribesState::instance.tribes[_tribeID].selectionTargetUnitID]
                        .tile];
                if (DAT_TroopValueState::instance.attackInfo.tribeRelatedArrayValue0UpTo12[_index] < 11
                    && MACRO_CALL_MEMBER(
                        Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                        DAT_PathFindingState::ptr)(DAT_TribesState::instance.tribes[_tribeID].owner, _area,
                        DAT_TroopValueState::instance.attackInfo.someArea, 1)) {
                    DAT_TribesState::instance.tribes[_tribeID].attackInfo_someCounter1
                        = (short)DAT_TroopValueState::instance.attackInfo.someCounter1;
                    DAT_TribesState::instance.tribes[_tribeID].someCounter1
                        = (short)DAT_TroopValueState::instance.attackInfo.unknownTribeCounterRelated;
                    DAT_TroopValueState::instance.attackInfo.unknownTribeCounterRelated
                        = DAT_TroopValueState::instance.attackInfo.unknownTribeCounterRelated + 1;
                    DAT_TribesState::instance.tribes[_tribeID].someUpdateUpperLimit
                        = ((short)_index + 1) * param_4 + param_3;
                    DAT_TribesState::instance.tribes[_tribeID].tribeBehaviorType = (undefined2)param_1;
                    if (DAT_TroopValueState::instance.attackInfo.unknownTribeCounterRelated >= 5) {
                        return;
                    }
                }
                DAT_TribesState::instance.tribes[_tribeID].unknownAttackRelatedUpdateCounter = 0;
            }
        }

    }
}
}
