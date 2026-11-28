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

        // FUNCTION: STRONGHOLDCRUSADER 0x00519E40
        int TroopValueState::findNearestAvailableScalePoint(int unitID)
        {
            int const playerID = DAT_UnitsState::instance.units[unitID].owner;
            int minDistance = 1000;
            int bestIndex = -1;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale2; ++i) {
                if (5999 <= DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                            .scaleValuesArray[i]
                            .buildingID
                    || DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scaleValuesArray[i].unitID
                        != 0) {
                    continue;
                }
                int const fromYPosition
                    = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                          [DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scaleValuesArray[i].tile2];
                int const fromXPosition
                    = DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scaleValuesArray[i].tile2
                    - DAT_ViewportRenderState::instance.translationMatrix[fromYPosition].addXgetTile;
                MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[unitID].x,
                    DAT_UnitsState::instance.units[unitID].y, fromXPosition, fromYPosition);
                if (DAT_DirectionAlgorithmState::instance.distanceHigh < minDistance) {
                    minDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                    this->y = fromYPosition;
                    this->x = fromXPosition;
                    this->tile
                        = DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scaleValuesArray[i].tile;
                    bestIndex = i;
                }
            }
            if (-1 < bestIndex) {
                DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scaleValuesArray[bestIndex].unitID
                    = unitID;
                return DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                    .scaleValuesArray[bestIndex]
                    .tile2;
            }
            return 0;
        }

    }
}
}
