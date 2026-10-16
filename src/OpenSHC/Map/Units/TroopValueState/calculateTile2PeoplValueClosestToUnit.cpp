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

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A140
        undefined4 TroopValueState::calculateTile2PeoplValueClosestToUnit(int unitID)
        {
            int fromXPosition;
            int* piVar1;
            int fromYPosition;
            int _index;
            int _minDistance;
            int _minIndex;
            _minDistance = 1000;
            _minIndex = -1;
            _index = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.people2) {
                piVar1 = &DAT_TroopValueState::instance.attackInfo.peopleValuesArray[0].tile2;
                do {
                    if (piVar1[2] == 0) {
                        fromYPosition
                            = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[*piVar1];
                        fromXPosition
                            = *piVar1 - DAT_ViewportRenderState::instance.translationMatrix[fromYPosition].addXgetTile;
                        MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[unitID].x,
                            (int)(DAT_UnitsState::instance.units[unitID].y), fromXPosition, fromYPosition);
                        if (DAT_DirectionAlgorithmState::instance.distanceHigh < _minDistance) {
                            DAT_TroopValueState::instance.tile = ((AttackInfoSubArrayElement1*)(piVar1 + -1))->tile;
                            _minDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                            _minIndex = _index;
                            DAT_TroopValueState::instance.x = fromXPosition;
                            DAT_TroopValueState::instance.y = fromYPosition;
                        }
                    }
                    _index = _index + 1;
                    piVar1 = piVar1 + 4;
                } while (_index < DAT_TroopValueState::instance.attackInfo.people2);
                if (-1 < _minIndex) {
                    DAT_TroopValueState::instance.attackInfo.peopleValuesArray[_minIndex].unitID = unitID;
                    return (undefined4)(DAT_TroopValueState::instance.attackInfo.peopleValuesArray[_minIndex].tile2);
                }
            }
            return (undefined4)(0);
        }

    }
}
}
