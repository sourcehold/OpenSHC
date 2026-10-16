#include "../../../Map.func.hpp"
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
            int iVar2;
            int iVar5;
            int _minDistance;
            int _bestIndex;
            int i;
            int _owner = DAT_UnitsState::instance.units[unitID].owner;
            _minDistance = 1000;
            _bestIndex = -1;
            i = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].some1000ArrayIndex_2) {
                do {
                    if (DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].gateValuesArray[i].buildingID < 5999 && !DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].gateValuesArray[i].unitID) {
                        iVar5 = (int)DAT_ViewportRenderState::instance
                                    .tileTranslationMatrix_YComponent[DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].gateValuesArray[i].tile2];
                        iVar2 = DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].gateValuesArray[i].tile2
                            - DAT_ViewportRenderState::instance.translationMatrix[iVar5].addXgetTile;
                        MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[unitID].x,
                            (int)(DAT_UnitsState::instance.units[unitID].y), iVar2, iVar5);
                        if (DAT_DirectionAlgorithmState::instance.distanceHigh < _minDistance) {
                            _minDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                            this->y = iVar5;
                            this->x = iVar2;
                            this->tile = DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].gateValuesArray[i].tile;
                            _bestIndex = i;
                        }
                    }
                    i = i + 1;
                } while (i < DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].some1000ArrayIndex_2);
                if (-1 < _bestIndex) {
                    undefined4 uVar1 = DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].gateValuesArray[_bestIndex].tile2;
                    DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].gateValuesArray[_bestIndex].unitID = unitID;
                    return (undefined4)(uVar1);
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
                for (; i < DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].some1000ArrayIndex_2; i = i + 1) {
                    if (DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].gateValuesArray[i].buildingID < 5999 && !DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].gateValuesArray[i].unitID) {
                        iVar5 = (int)DAT_ViewportRenderState::instance
                                    .tileTranslationMatrix_YComponent[DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].gateValuesArray[i].tile2];
                        iVar2 = DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].gateValuesArray[i].tile2
                            - DAT_ViewportRenderState::instance.translationMatrix[iVar5].addXgetTile;
                        MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[unitID].x,
                            (int)(DAT_UnitsState::instance.units[unitID].y), iVar2, iVar5);
                        if (DAT_DirectionAlgorithmState::instance.distanceHigh < _minDistance) {
                            _minDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                            this->y = iVar5;
                            this->x = iVar2;
                            this->tile = DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].gateValuesArray[i].tile;
                            _bestIndex = i;
                        }
                    }
                }
            }
            if (-1 < _bestIndex) {
                return DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].gateValuesArray[_bestIndex].tile2;
            }
            return (undefined4)(0);
        }

    }
}
}
