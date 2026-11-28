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

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A780
        int TroopValueState::calculateTile2MoatValueClosestToUnit(int unitID)
        {
            int const owner = DAT_UnitsState::instance.units[unitID].owner;
            int minDistance = 100000;
            int bestIndex = -1;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].moat2; ++i) {
                if (DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].moatValuesArray[i].buildingID >= 5999
                    || DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].moatValuesArray[i].unitID != 0) {
                    continue;
                }
                int const fromYPosition
                    = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                          [DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].moatValuesArray[i].tile2];
                int const fromXPosition
                    = DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].moatValuesArray[i].tile2
                    - DAT_ViewportRenderState::instance.translationMatrix[fromYPosition].addXgetTile;
                MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[unitID].x,
                    DAT_UnitsState::instance.units[unitID].y, fromXPosition, fromYPosition);
                int const distance = DAT_DirectionAlgorithmState::instance.distanceHigh
                    + DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].moatValuesArray[i].buildingID * 8;
                DAT_DirectionAlgorithmState::instance.distanceHigh = distance;
                if (distance < minDistance) {
                    minDistance = distance;
                    this->y = fromYPosition;
                    this->x = fromXPosition;
                    this->tile = DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].moatValuesArray[i].tile;
                    bestIndex = i;
                }
            }
            if (-1 < bestIndex) {
                DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].moatValuesArray[bestIndex].unitID
                    = unitID;
                return DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].moatValuesArray[bestIndex].tile2;
            }
            return 0;
        }

    }
}
}
