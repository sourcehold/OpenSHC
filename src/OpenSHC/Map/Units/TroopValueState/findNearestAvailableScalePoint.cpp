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
        undefined4 TroopValueState::findNearestAvailableScalePoint(int unitID)
        {
            int const _playerID = DAT_UnitsState::instance.units[unitID].owner;
            int _minDistance = 1000;
            int _bestIndex = -1;
            int i = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.playerInfo[_playerID - 1].scale2) {
                do {
                    if (DAT_TroopValueState::instance.attackInfo.playerInfo[_playerID - 1]
                                .scaleValuesArray[i]
                                .buildingID
                            < 5999
                        && DAT_TroopValueState::instance.attackInfo.playerInfo[_playerID - 1].scaleValuesArray[i].unitID
                            == 0) {
                        int fromYPosition
                            = (int)DAT_ViewportRenderState::instance
                                  .tileTranslationMatrix_YComponent[DAT_TroopValueState::instance.attackInfo
                                          .playerInfo[_playerID - 1]
                                          .scaleValuesArray[i]
                                          .tile2];
                        int fromXPosition = DAT_TroopValueState::instance.attackInfo.playerInfo[_playerID - 1]
                                                .scaleValuesArray[i]
                                                .tile2
                            - DAT_ViewportRenderState::instance.translationMatrix[fromYPosition].addXgetTile;
                        MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[unitID].x,
                            (int)(DAT_UnitsState::instance.units[unitID].y), fromXPosition, fromYPosition);
                        if (DAT_DirectionAlgorithmState::instance.distanceHigh < _minDistance) {
                            _minDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                            this->y = fromYPosition;
                            this->x = fromXPosition;
                            this->tile = DAT_TroopValueState::instance.attackInfo.playerInfo[_playerID - 1]
                                             .scaleValuesArray[i]
                                             .tile;
                            _bestIndex = i;
                        }
                    }
                    i = i + 1;
                } while (i < DAT_TroopValueState::instance.attackInfo.playerInfo[_playerID - 1].scale2);
                if (-1 < _bestIndex) {
                    DAT_TroopValueState::instance.attackInfo.playerInfo[_playerID - 1]
                        .scaleValuesArray[_bestIndex]
                        .unitID = unitID;
                    return DAT_TroopValueState::instance.attackInfo.playerInfo[_playerID - 1]
                        .scaleValuesArray[_bestIndex]
                        .tile2;
                }
            }
            return 0;
        }

    }
}
}
