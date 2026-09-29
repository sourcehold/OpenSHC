#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x005346D0
        int UnitsState::selectNewBlessingTarget(int unitID)
        {
            short _playerID = this->units[unitID].owner;
            short _x = this->units[unitID].x;
            short _y = this->units[unitID].y;
            int _bestUnitID = 0;
            int _highestPreference = 0;
            for (int _targetUnitID = 1; _targetUnitID < (int)this->maxUnitCount; ++_targetUnitID) {
                if (this->units[_targetUnitID].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                    continue;
                }
                if (this->units[_targetUnitID].dying != 0) {
                    continue;
                }
                if (this->units[_targetUnitID].owner != _playerID) {
                    continue;
                }
                if (DAT_UnitPropertiesDefinedData::instance.NotBlessableUnits[this->units[_targetUnitID].unitType]
                    != 0) {
                    continue;
                }
                if (this->units[_targetUnitID].blessedAmount >= 4000) {
                    continue;
                }
                int _distance = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(
                    _x, _y, this->units[_targetUnitID].x, this->units[_targetUnitID].y);
                if (_distance >= 40) {
                    continue;
                }
                int _preference = ((4000 - this->units[_targetUnitID].blessedAmount) >> 6) - _distance / 2;
                if (_highestPreference < _preference) {
                    _highestPreference = _preference;
                    _bestUnitID = _targetUnitID;
                }
            }
            return _bestUnitID;
        }

    }
}
}
