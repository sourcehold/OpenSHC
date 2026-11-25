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

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A330
        undefined4 TroopValueState::findEnemyTowersOrGates(int unitID)
        {
            int const owner = DAT_UnitsState::instance.units[unitID].owner;
            int minDistance = 1000;
            int bestIndex = -1;
            // one counter shared by the three loops: a fresh one per loop changes the stack layout
            int i;
            for (i = 0; i < DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].some1000ArrayIndex_2; ++i) {
                if (5999 <= DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].gateValuesArray[i].buildingID
                    || DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].gateValuesArray[i].unitID) {
                    continue;
                }
                int const fromYPosition
                    = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                          [DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].gateValuesArray[i].tile2];
                int const fromXPosition
                    = DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].gateValuesArray[i].tile2
                    - DAT_ViewportRenderState::instance.translationMatrix[fromYPosition].addXgetTile;
                MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[unitID].x,
                    DAT_UnitsState::instance.units[unitID].y, fromXPosition, fromYPosition);
                if (DAT_DirectionAlgorithmState::instance.distanceHigh < minDistance) {
                    minDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                    this->y = fromYPosition;
                    this->x = fromXPosition;
                    this->tile = DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].gateValuesArray[i].tile;
                    bestIndex = i;
                }
            }
            if (-1 < bestIndex) {
                undefined4 const bestTile
                    = DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].gateValuesArray[bestIndex].tile2;
                DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].gateValuesArray[bestIndex].unitID
                    = unitID;
                return bestTile;
            }
            // no free gate left: release every claim and search again
            for (i = 0; i < DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].some1000ArrayIndex_2; ++i) {
                DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].gateValuesArray[i].unitID = 0;
            }
            minDistance = 1000;
            for (i = 0; i < DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].some1000ArrayIndex_2; ++i) {
                if (5999 <= DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].gateValuesArray[i].buildingID
                    || DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].gateValuesArray[i].unitID) {
                    continue;
                }
                int const fromYPosition
                    = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                          [DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].gateValuesArray[i].tile2];
                int const fromXPosition
                    = DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].gateValuesArray[i].tile2
                    - DAT_ViewportRenderState::instance.translationMatrix[fromYPosition].addXgetTile;
                MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[unitID].x,
                    DAT_UnitsState::instance.units[unitID].y, fromXPosition, fromYPosition);
                if (DAT_DirectionAlgorithmState::instance.distanceHigh < minDistance) {
                    minDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                    this->y = fromYPosition;
                    this->x = fromXPosition;
                    this->tile = DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].gateValuesArray[i].tile;
                    bestIndex = i;
                }
            }
            if (-1 < bestIndex) {
                return DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].gateValuesArray[bestIndex].tile2;
            }
            return 0;
        }

    }
}
}
