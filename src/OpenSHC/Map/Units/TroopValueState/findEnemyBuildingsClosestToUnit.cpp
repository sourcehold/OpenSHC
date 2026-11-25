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

        // FUNCTION: STRONGHOLDCRUSADER 0x00519FB0
        undefined4 TroopValueState::findEnemyBuildingsClosestToUnit(int unitID)
        {
            int const owner = DAT_UnitsState::instance.units[unitID].owner;
            int minDistance = 1000;
            int bestIndex = -1;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].town2; ++i) {
                if (DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].townValuesArray[i].unitID) {
                    continue;
                }
                int const fromYPosition
                    = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                          [DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].townValuesArray[i].tile2];
                int const fromXPosition
                    = DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].townValuesArray[i].tile2
                    - DAT_ViewportRenderState::instance.translationMatrix[fromYPosition].addXgetTile;
                MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[unitID].x,
                    DAT_UnitsState::instance.units[unitID].y, fromXPosition, fromYPosition);
                // smaller buildings count as further away
                int const distance = DAT_DirectionAlgorithmState::instance.distanceHigh
                    + (100 - DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].townValuesArray[i].size)
                        * 2;
                DAT_DirectionAlgorithmState::instance.distanceHigh = distance;
                if (distance < minDistance) {
                    minDistance = distance;
                    this->y = fromYPosition;
                    this->x = fromXPosition;
                    this->tile = DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].townValuesArray[i].tile;
                    bestIndex = i;
                }
            }
            // "if (bestIndex <= -1) return 0;" moves the cold return block and changes the asm
            if (-1 < bestIndex) {
                DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].townValuesArray[bestIndex].unitID
                    = unitID;
                return DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].townValuesArray[bestIndex].tile2;
            }
            return 0;
        }

    }
}
}
