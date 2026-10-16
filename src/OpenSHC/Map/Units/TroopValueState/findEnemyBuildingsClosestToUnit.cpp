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

        // FUNCTION: STRONGHOLDCRUSADER 0x00519FB0
        undefined4 TroopValueState::findEnemyBuildingsClosestToUnit(int unitID)
        {
            int fromXPosition;
            int fromYPosition;
            int _minDistance;
            int _bestIndex;
            int i;
            int _owner = (int)DAT_UnitsState::instance.units[unitID].owner;
            _minDistance = 1000;
            _bestIndex = -1;
            i = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].town2) {
                do {
                    if (!DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].townValuesArray[i].unitID) {
                        fromYPosition = (int)DAT_ViewportRenderState::instance
                                            .tileTranslationMatrix_YComponent[DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].townValuesArray[i].tile2];
                        fromXPosition = DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].townValuesArray[i].tile2
                            - DAT_ViewportRenderState::instance.translationMatrix[fromYPosition].addXgetTile;
                        MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[unitID].x,
                            (int)(DAT_UnitsState::instance.units[unitID].y), fromXPosition, fromYPosition);
                        int _distance = DAT_DirectionAlgorithmState::instance.distanceHigh
                            + (100 - DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].townValuesArray[i].size) * 2;
                        DAT_DirectionAlgorithmState::instance.distanceHigh = _distance;
                        if (_distance < _minDistance) {
                            _minDistance = _distance;
                            this->y = fromYPosition;
                            this->x = fromXPosition;
                            this->tile = DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].townValuesArray[i].tile;
                            _bestIndex = i;
                        }
                    }
                    i = i + 1;
                } while (i < DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].town2);
                if (-1 < _bestIndex) {
                    DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].townValuesArray[_bestIndex].unitID = unitID;
                    return DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].townValuesArray[_bestIndex].tile2;
                }
            }
            return (undefined4)(0);
        }

    }
}
}
