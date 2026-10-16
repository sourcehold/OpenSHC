#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A5B0
        undefined4 TroopValueState::getClosestWideValueBasedOnPlayer(int playerID)
        {
            int fromXPosition;
            int fromYPosition;
            int _minDistance;
            int _bestIndex;
            int i;
            int iVar1;
            int _owner = DAT_UnitsState::instance.units[playerID].owner;
            _minDistance = 1000;
            _bestIndex = -1;
            int _attackedPlayerID = DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].currentPlayerID_OR_attackedPlayerID_OR_one;
            int destinationXPosition = DAT_GameState::instance.playerDataArray[_attackedPlayerID].campground.xEntry;
            int destinationYPosition = DAT_GameState::instance.playerDataArray[_attackedPlayerID].campground.yEntry;
            i = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].wide2) {
                for (; i < DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].wide2; i = i + 1) {
                    if (DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].wideValuesArray[i].buildingID < 5999 && !DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].wideValuesArray[i].unitID) {
                        fromYPosition = (int)DAT_ViewportRenderState::instance
                                            .tileTranslationMatrix_YComponent[DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].wideValuesArray[i].tile2];
                        fromXPosition = DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].wideValuesArray[i].tile2
                            - DAT_ViewportRenderState::instance.translationMatrix[fromYPosition].addXgetTile;
                        MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[playerID].x,
                            (int)(DAT_UnitsState::instance.units[playerID].y), fromXPosition, fromYPosition);
                        iVar1 = DAT_DirectionAlgorithmState::instance.distanceHigh;
                        MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)(
                            destinationXPosition, destinationYPosition, fromXPosition, fromYPosition);
                        iVar1 = iVar1 + DAT_DirectionAlgorithmState::instance.distanceHigh;
                        if (iVar1 < _minDistance) {
                            this->y = fromYPosition;
                            this->x = fromXPosition;
                            this->tile = DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].wideValuesArray[i].tile;
                            _minDistance = iVar1;
                            _bestIndex = i;
                        }
                    }
                }
                if (-1 < _bestIndex) {
                    DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].wideValuesArray[_bestIndex].unitID = playerID;
                    return DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].wideValuesArray[_bestIndex].tile2;
                }
            }
            return (undefined4)(0);
        }

    }
}
}
