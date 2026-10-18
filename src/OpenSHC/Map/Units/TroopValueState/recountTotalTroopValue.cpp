#include "OpenSHC/Map.func.hpp"

#include "../TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051F9C0
        void TroopValueState::recountTotalTroopValue()
        {
            int _troopTypeValue;
            Unit* _pUnit;
            int remainingUnits;
            int _playerID;
            UnitTypeShort _troopType;
            for (int _player = 0; _player < 10; ++_player) {
                DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[_player] = 0;
            }
            if (1 < DAT_UnitsState::instance.maxUnitCount) {
                _pUnit = &DAT_UnitsState::instance.units[1];
                remainingUnits = DAT_UnitsState::instance.maxUnitCount - 1;
                do {
                    if (_pUnit->logicalState != Map::Units::ULS_INVISIBLE && !_pUnit->dying
                        && _pUnit->isSelectable_OR_matchTime
                        && (_troopType = _pUnit->unitType,
                            _troopType != Map::Units::UT_E_ENGINEER && (_troopType != Map::Units::UT_TUNNELER))
                        && _troopType != Map::Units::UT_E_LADDER) {
                        _troopTypeValue = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getValueOfTroopType,
                            DAT_TroopValueState::ptr)((Map::Units::UnitType)(short)_troopType);
                        _playerID = _pUnit->owner;
                        DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[_playerID]
                            = DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[_playerID]
                            + _troopTypeValue;
                    }
                    _pUnit = _pUnit + 1;
                    remainingUnits = remainingUnits + -1;
                } while (remainingUnits);
            }
        }

    }
}
}
