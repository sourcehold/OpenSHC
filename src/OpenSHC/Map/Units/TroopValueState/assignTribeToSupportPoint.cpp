#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051B190
        int TroopValueState::assignTribeToSupportPoint(int x, int y, int tribeID)
        {
            int const pointIndex = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findSupportPointIndex,
                DAT_PathFindingState::ptr)(200, x, y, tribeID);
            if (pointIndex) {
                short const oldPointIndex = DAT_TribesState::instance.tribes[tribeID].supportPointIndex;
                DAT_TribesState::instance.tribes[tribeID].oldSupportPointIndex = oldPointIndex;
                DAT_TroopValueState::instance.attackInfo.supportPointsArray[oldPointIndex].tribeID = 0;
                DAT_TroopValueState::instance.attackInfo.supportPointsArray[oldPointIndex].tribeUID = 0;
                DAT_TribesState::instance.tribes[tribeID].supportPointIndex = pointIndex;
                int const pointY = DAT_TroopValueState::instance.attackInfo.supportPointsArray[pointIndex].y;
                DAT_TroopValueState::instance.attackInfo.supportPointsArray[pointIndex].tribeUID
                    = DAT_TribesState::instance.tribes[tribeID].uid;
                DAT_TroopValueState::instance.attackInfo.supportPointsArray[pointIndex].tribeID = tribeID;
                DAT_TroopValueState::instance.attackInfo.supportPointsArray[pointIndex].three = 3;
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(tribeID,
                    DAT_TroopValueState::instance.attackInfo.supportPointsArray[pointIndex].x, pointY, 0, 0,
                    Map::Units::Instructions::UMSE_0);
                return pointIndex;
            }
            return 0;
        }

    }
}
}
