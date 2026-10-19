#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x005242B0
        UnitType TribesState::getMajorityArcherTypeEuropeanOrArabian(int selectionID)
        {
            int _unitID;
            int iVar2 = (int)this->tribes[selectionID].size;
            int _unitSelectionIndex = 0;
            int _europeanArcherCount = 0;
            int _arabArcherCount = 0;
            if (0 < iVar2) {
                do {
                    _unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        selectionID, _unitSelectionIndex);
                    _unitSelectionIndex = _unitSelectionIndex + 1;
                    if ((DAT_UnitsState::instance.units[_unitID].logicalState == Map::Units::ULS_NORMAL)
                        && (DAT_UnitsState::instance.units[_unitID].dying == 0)) {
                        UnitTypeShort UVar1 = DAT_UnitsState::instance.units[_unitID].unitType;
                        if (UVar1 == Map::Units::UT_A_ARCHER) {
                            _arabArcherCount = _arabArcherCount + 1;
                        }
                        if (UVar1 == Map::Units::UT_E_ARCHER) {
                            _europeanArcherCount = _europeanArcherCount + 1;
                        }
                    }
                } while (_unitSelectionIndex < iVar2);
                if (_arabArcherCount > _europeanArcherCount) {
                    return Map::Units::UT_A_ARCHER;
                }
            }
            return Map::Units::UT_E_ARCHER;
        }

    }
}
}
