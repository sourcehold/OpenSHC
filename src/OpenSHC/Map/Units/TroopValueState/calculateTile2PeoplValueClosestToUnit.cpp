#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A140
        undefined4 TroopValueState::calculateTile2PeoplValueClosestToUnit(int unitID)
        {
            int minDistance = 1000;
            int bestIndex = -1;
            int i = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.people2) {
                for (; i < DAT_TroopValueState::instance.attackInfo.people2; ++i) {
                    if (DAT_TroopValueState::instance.attackInfo.peopleValuesArray[i].unitID != 0) {
                        continue;
                    }
                    int const fromYPosition = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                                                  [DAT_TroopValueState::instance.attackInfo.peopleValuesArray[i].tile2];
                    int const fromXPosition = DAT_TroopValueState::instance.attackInfo.peopleValuesArray[i].tile2
                        - DAT_ViewportRenderState::instance.translationMatrix[fromYPosition].addXgetTile;
                    MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                        DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[unitID].x,
                        DAT_UnitsState::instance.units[unitID].y, fromXPosition, fromYPosition);
                    if (DAT_DirectionAlgorithmState::instance.distanceHigh < minDistance) {
                        minDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                        this->y = fromYPosition;
                        this->x = fromXPosition;
                        this->tile = DAT_TroopValueState::instance.attackInfo.peopleValuesArray[i].tile;
                        bestIndex = i;
                    }
                }
                if (bestIndex <= -1) {
                    return 0;
                }
                DAT_TroopValueState::instance.attackInfo.peopleValuesArray[bestIndex].unitID = unitID;
                return DAT_TroopValueState::instance.attackInfo.peopleValuesArray[bestIndex].tile2;
            }
            return 0;
        }

    }
}
}
