#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
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
            for (int _player = 0; _player < 10; ++_player) {
                DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[_player] = 0;
            }
            for (int _unitID = 1; _unitID < DAT_UnitsState::instance.maxUnitCount; ++_unitID) {
                if (DAT_UnitsState::instance.units[_unitID].logicalState != Map::Units::ULS_INVISIBLE
                    && !DAT_UnitsState::instance.units[_unitID].dying
                    && DAT_UnitsState::instance.units[_unitID].isSelectable_OR_matchTime
                    && DAT_UnitsState::instance.units[_unitID].unitType != Map::Units::UT_E_ENGINEER
                    && DAT_UnitsState::instance.units[_unitID].unitType != Map::Units::UT_TUNNELER
                    && DAT_UnitsState::instance.units[_unitID].unitType != Map::Units::UT_E_LADDER) {
                    int const _playerID = DAT_UnitsState::instance.units[_unitID].owner;
                    DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[_playerID]
                        = DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[_playerID]
                        + MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getValueOfTroopType, this)(
                            (Map::Units::UnitType)DAT_UnitsState::instance.units[_unitID].unitType);
                }
            }
        }

    }
}
}
