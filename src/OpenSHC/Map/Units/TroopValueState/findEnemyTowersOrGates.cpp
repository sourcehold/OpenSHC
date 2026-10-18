#include "OpenSHC/Map.func.hpp"
#include "../TroopValueState.func.hpp"

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
            int fromXPosition;
            int fromYPosition;
            int const _owner = DAT_UnitsState::instance.units[unitID].owner;
            int _minDistance = 1000;
            int _bestIndex = -1;
            int i = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].some1000ArrayIndex_2) {
                do {
                    if (DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].gateValuesArray[i].buildingID
                            < 5999
                        && !DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].gateValuesArray[i].unitID) {
                        fromYPosition = (int)DAT_ViewportRenderState::instance
                                            .tileTranslationMatrix_YComponent[DAT_TroopValueState::instance.attackInfo
                                                    .playerInfo[_owner - 1]
                                                    .gateValuesArray[i]
                                                    .tile2];
                        fromXPosition
                            = DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].gateValuesArray[i].tile2
                            - DAT_ViewportRenderState::instance.translationMatrix[fromYPosition].addXgetTile;
                        MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[unitID].x,
                            (int)(DAT_UnitsState::instance.units[unitID].y), fromXPosition, fromYPosition);
                        if (DAT_DirectionAlgorithmState::instance.distanceHigh < _minDistance) {
                            _minDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                            this->y = fromYPosition;
                            this->x = fromXPosition;
                            this->tile = DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1]
                                             .gateValuesArray[i]
                                             .tile;
                            _bestIndex = i;
                        }
                    }
                    i = i + 1;
                } while (i < DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].some1000ArrayIndex_2);
                if (-1 < _bestIndex) {
                    undefined4 _bestTile = DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1]
                                               .gateValuesArray[_bestIndex]
                                               .tile2;
                    DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].gateValuesArray[_bestIndex].unitID
                        = unitID;
                    return _bestTile;
                }
            }
            i = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].some1000ArrayIndex_2) {
                do {
                    DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].gateValuesArray[i].unitID = 0;
                    i = i + 1;
                } while (i < DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].some1000ArrayIndex_2);
            }
            _minDistance = 1000;
            i = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].some1000ArrayIndex_2) {
                for (; i < DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].some1000ArrayIndex_2;
                    i = i + 1) {
                    if (DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].gateValuesArray[i].buildingID
                            < 5999
                        && !DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].gateValuesArray[i].unitID) {
                        fromYPosition = (int)DAT_ViewportRenderState::instance
                                            .tileTranslationMatrix_YComponent[DAT_TroopValueState::instance.attackInfo
                                                    .playerInfo[_owner - 1]
                                                    .gateValuesArray[i]
                                                    .tile2];
                        fromXPosition
                            = DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].gateValuesArray[i].tile2
                            - DAT_ViewportRenderState::instance.translationMatrix[fromYPosition].addXgetTile;
                        MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[unitID].x,
                            (int)(DAT_UnitsState::instance.units[unitID].y), fromXPosition, fromYPosition);
                        if (DAT_DirectionAlgorithmState::instance.distanceHigh < _minDistance) {
                            _minDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                            this->y = fromYPosition;
                            this->x = fromXPosition;
                            this->tile = DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1]
                                             .gateValuesArray[i]
                                             .tile;
                            _bestIndex = i;
                        }
                    }
                }
            }
            if (-1 < _bestIndex) {
                return DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1]
                    .gateValuesArray[_bestIndex]
                    .tile2;
            }
            return 0;
        }

    }
}
}
