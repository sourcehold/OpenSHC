#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005242B0
        UnitType TribesState::getMajorityArcherTypeEuropeanOrArabian(int tribeID)
        {
            int europeanArcherCount = 0;
            int arabArcherCount = 0;
            int const size = this->tribes[tribeID].size;
            if (size > 0) {
                int i = 0;
                do {
                    int const unitID = MACRO_CALL_MEMBER(TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID, i);
                    ++i;
                    if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                        && DAT_UnitsState::instance.units[unitID].dying == 0) {
                        if (DAT_UnitsState::instance.units[unitID].unitType == UT_A_ARCHER) {
                            ++arabArcherCount;
                        }
                        if (DAT_UnitsState::instance.units[unitID].unitType == UT_E_ARCHER) {
                            ++europeanArcherCount;
                        }
                    }
                } while (i < size);
                if (arabArcherCount > europeanArcherCount) {
                    return UT_A_ARCHER;
                }
            }
            return UT_E_ARCHER;
        }

    } // namespace Units
} // namespace Map
} // namespace OpenSHC
