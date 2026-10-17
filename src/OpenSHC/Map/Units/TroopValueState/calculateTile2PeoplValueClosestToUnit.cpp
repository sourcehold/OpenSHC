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
            int fromYPosition;
            int _minDistance = 1000;
            int _bestIndex = -1;
            int i = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.people2) {
                do {
                    if (DAT_TroopValueState::instance.attackInfo.peopleValuesArray[i].unitID == 0) {
                        fromYPosition = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                                            [DAT_TroopValueState::instance.attackInfo.peopleValuesArray[i].tile2];
                        fromXPosition = DAT_TroopValueState::instance.attackInfo.peopleValuesArray[i].tile2
                            - DAT_ViewportRenderState::instance.translationMatrix[fromYPosition].addXgetTile;
                        MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[unitID].x,
                            (int)(DAT_UnitsState::instance.units[unitID].y), fromXPosition, fromYPosition);
                        if (DAT_DirectionAlgorithmState::instance.distanceHigh < _minDistance) {
                            _minDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                            this->y = fromYPosition;
                            this->x = fromXPosition;
                            this->tile = DAT_TroopValueState::instance.attackInfo.peopleValuesArray[i].tile;
                            _bestIndex = i;
                        }
                    }
                    i = i + 1;
                } while (i < DAT_TroopValueState::instance.attackInfo.people2);
                if (-1 < _bestIndex) {
                    DAT_TroopValueState::instance.attackInfo.peopleValuesArray[_bestIndex].unitID = unitID;
                    return (undefined4)(DAT_TroopValueState::instance.attackInfo.peopleValuesArray[_bestIndex].tile2);
                }
            }
            return (undefined4)(0);
        }

    }
}
}
