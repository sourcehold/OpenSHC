#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051FA70
        void TroopValueState::recomputeTotalTroopValueOfTroopsNearKeep()
        {
            UnitTypeShort _troopType;
            int _troopValue;
            int _unitID;
            Unit* ptrUnit;
            int _playerID;
            _unitID = 1;
            for (int _player = 0; _player < 10; ++_player) {
                DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueOfTroopsNearKeep[_player] = 0;
            }
            if (1 < DAT_UnitsState::instance.maxUnitCount) {
                ptrUnit = &DAT_UnitsState::instance.units[1];
                do {
                    if (ptrUnit->logicalState != Map::Units::ULS_INVISIBLE && !ptrUnit->dying
                        && ptrUnit->isSelectable_OR_matchTime
                        && (_troopType = ptrUnit->unitType,
                            _troopType != Map::Units::UT_E_ENGINEER && (_troopType != Map::Units::UT_TUNNELER))
                        && _troopType != Map::Units::UT_E_LADDER) {
                        _playerID = ptrUnit->owner;
                        MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)(
                            DAT_GameState::instance.playerDataArray[_playerID].campground.xEntry,
                            DAT_GameState::instance.playerDataArray[_playerID].campground.yEntry, (int)(ptrUnit->x),
                            (int)(ptrUnit->y));
                        if (DAT_DirectionAlgorithmState::instance.distanceHigh <= 40) {
                            _troopValue = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getValueOfTroopType,
                                this)((Map::Units::UnitType)(short)ptrUnit->unitType);
                            DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueOfTroopsNearKeep[_playerID]
                                = DAT_TroopValueState::instance.attackInfo
                                      .playerTotalTroopValueOfTroopsNearKeep[_playerID]
                                + _troopValue;
                        }
                    }
                    _unitID = _unitID + 1;
                    ptrUnit = ptrUnit + 1;
                } while (_unitID < DAT_UnitsState::instance.maxUnitCount);
            }
        }

    }
}
}
