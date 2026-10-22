#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;

        /*
          fixme: there is more data on the stack than used?   decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00521720
        UnitType TribesState::getMajoritySelectedUnitType(int tribeID, int* maximumCount)
        {
            Unit* _pUnit;
            int _maximumTroopType;
            int _index;
            int _countInclusive;
            int _maximumCount;
            int aiStackY_20140[32764];
            int _countOfUnitTypes[80];
            MACRO_CALL(OS_Func::_memset)(_countOfUnitTypes, 0, (size_t)((int)(320)));
            if (1 < DAT_UnitsState::instance.maxUnitCount) {
                _pUnit = &DAT_UnitsState::instance.units[1];
                _countInclusive = DAT_UnitsState::instance.maxUnitCount - 1;
                do {
                    /*
                      bug: shouldn't this check if the unit is part of the tribe !? It checks for   being selected I see
                     */
                    if (_pUnit->logicalState == Map::Units::ULS_NORMAL && !_pUnit->dying
                        && _pUnit->owner == DAT_GameSynchronyState::instance.currentPlayerSlotID && _pUnit->isSelected
                        && (short)_pUnit->unitType < 0x50) {
                        *(int*)((int)_countOfUnitTypes + (short)_pUnit->unitType * 4)
                            = *(int*)((int)_countOfUnitTypes + (short)_pUnit->unitType * 4) + 1;
                    }
                    _pUnit = _pUnit + 1;
                    _countInclusive = _countInclusive + -1;
                } while (_countInclusive);
            }
            _maximumTroopType = 0;
            _maximumCount = -1;
            _index = 1;
            do {
                if (*(int*)((int)_countOfUnitTypes + _index * 4) > _maximumCount) {
                    _maximumTroopType = _index;
                    _maximumCount = *(int*)((int)_countOfUnitTypes + _index * 4);
                }
                _index = _index + Map::Units::UT_PEASANT;
            } while (_index < 80);
            if (_maximumTroopType != (UnitType)0 && maximumCount != (int*)0x0) {
                *maximumCount = _maximumCount;
            }
            return (UnitType)(_maximumTroopType);
        }

    }
}
}
