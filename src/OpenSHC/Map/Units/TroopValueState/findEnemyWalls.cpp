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

        // FUNCTION: STRONGHOLDCRUSADER 0x00519CC0
        undefined4 TroopValueState::findEnemyWalls(int unitID)
        {
            int const _owner = DAT_UnitsState::instance.units[unitID].owner;
            int _minDistance = 1000;
            int _bestIndex = -1;
            int i = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].hack2) {
                do {
                    if (DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].hackValuesArray[i].size < 9999
                        && !DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].hackValuesArray[i].unitID) {
                        int fromYPosition
                            = (int)DAT_ViewportRenderState::instance
                                  .tileTranslationMatrix_YComponent[DAT_TroopValueState::instance.attackInfo
                                          .playerInfo[_owner - 1]
                                          .hackValuesArray[i]
                                          .tile2];
                        int fromXPosition
                            = DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].hackValuesArray[i].tile2
                            - DAT_ViewportRenderState::instance.translationMatrix[fromYPosition].addXgetTile;
                        MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[unitID].x,
                            (int)(DAT_UnitsState::instance.units[unitID].y), fromXPosition, fromYPosition);
                        int _distance = DAT_DirectionAlgorithmState::instance.distanceHigh
                            + DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].hackValuesArray[i].size
                                * 8;
                        DAT_DirectionAlgorithmState::instance.distanceHigh = _distance;
                        if (_distance < _minDistance) {
                            _minDistance = _distance;
                            this->y = fromYPosition;
                            this->x = fromXPosition;
                            this->tile = DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1]
                                             .hackValuesArray[i]
                                             .tile;
                            _bestIndex = i;
                        }
                    }
                    i = i + 1;
                } while (i < DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].hack2);
                if (-1 < _bestIndex) {
                    DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1].hackValuesArray[_bestIndex].unitID
                        = unitID;
                    return DAT_TroopValueState::instance.attackInfo.playerInfo[_owner - 1]
                        .hackValuesArray[_bestIndex]
                        .tile2;
                }
            }
            return 0;
        }

    }
}
}
