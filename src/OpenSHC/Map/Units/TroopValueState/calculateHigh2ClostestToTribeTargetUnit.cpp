#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A9F0
        int TroopValueState::calculateHigh2ClostestToTribeTargetUnit(int tribeID)
        {
            int const _unitID = (int)DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID;
            int _minDistance = 1000;
            int _bestIndex = -1;
            int i = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.high2) {
                for (; i < DAT_TroopValueState::instance.attackInfo.high2; i = i + 1) {
                    if (DAT_BuildingsState::instance
                                .buildings[DAT_TroopValueState::instance.attackInfo.high2ValuesArray[i].buildingID]
                                .unknownCounterTo10000_0x2b4
                            < 9999
                        && DAT_TroopValueState::instance.attackInfo.high2ValuesArray[i].unitID == 0) {
                        int fromYPosition = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                                                [DAT_TroopValueState::instance.attackInfo.high2ValuesArray[i].tile2];
                        int fromXPosition = DAT_TroopValueState::instance.attackInfo.high2ValuesArray[i].tile2
                            - DAT_ViewportRenderState::instance.translationMatrix[fromYPosition].addXgetTile;
                        MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[_unitID].x,
                            (int)(DAT_UnitsState::instance.units[_unitID].y), fromXPosition, fromYPosition);
                        if (DAT_DirectionAlgorithmState::instance.distanceHigh < _minDistance) {
                            _minDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                            this->y = fromYPosition;
                            this->x = fromXPosition;
                            this->tile = DAT_TroopValueState::instance.attackInfo.high2ValuesArray[i].tile;
                            _bestIndex = i;
                        }
                    }
                }
                if (-1 < _bestIndex) {
                    DAT_TroopValueState::instance.attackInfo.high2ValuesArray[_bestIndex].unitID = _unitID;
                    return DAT_TroopValueState::instance.attackInfo.high2ValuesArray[_bestIndex].tile2;
                }
            }
            return 0;
        }

    }
}
}
