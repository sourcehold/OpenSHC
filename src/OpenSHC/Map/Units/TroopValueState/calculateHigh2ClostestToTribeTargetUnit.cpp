#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A9F0
        int TroopValueState::calculateHigh2ClostestToTribeTargetUnit(int tribeID)
        {
            int const unitID = DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID;
            int minDistance = 1000;
            int bestIndex = -1;
            // i is zeroed before the guard in the original; declaring it in the for moves the store past the branch
            int i = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.high2) {
                for (; i < DAT_TroopValueState::instance.attackInfo.high2; ++i) {
                    if (DAT_BuildingsState::instance
                                .buildings[DAT_TroopValueState::instance.attackInfo.high2ValuesArray[i].buildingID]
                                .unknownCounterTo10000_0x2b4
                            >= 9999
                        || DAT_TroopValueState::instance.attackInfo.high2ValuesArray[i].unitID != 0) {
                        continue;
                    }
                    int const fromYPosition = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                                                  [DAT_TroopValueState::instance.attackInfo.high2ValuesArray[i].tile2];
                    int const fromXPosition = DAT_TroopValueState::instance.attackInfo.high2ValuesArray[i].tile2
                        - DAT_ViewportRenderState::instance.translationMatrix[fromYPosition].addXgetTile;
                    MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                        DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[unitID].x,
                        DAT_UnitsState::instance.units[unitID].y, fromXPosition, fromYPosition);
                    if (DAT_DirectionAlgorithmState::instance.distanceHigh < minDistance) {
                        minDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                        this->y = fromYPosition;
                        this->x = fromXPosition;
                        this->tile = DAT_TroopValueState::instance.attackInfo.high2ValuesArray[i].tile;
                        bestIndex = i;
                    }
                }
                if (bestIndex <= -1) {
                    return 0;
                }
                DAT_TroopValueState::instance.attackInfo.high2ValuesArray[bestIndex].unitID = unitID;
                return DAT_TroopValueState::instance.attackInfo.high2ValuesArray[bestIndex].tile2;
            }
            return 0;
        }

    }
}
}
