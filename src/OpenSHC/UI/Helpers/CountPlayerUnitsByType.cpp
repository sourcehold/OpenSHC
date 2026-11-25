#include "../Helpers.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitTypeRelatedCounter.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace UI {

    using Map::Units::Unit;

    // FUNCTION: STRONGHOLDCRUSADER 0x00440360
    void Helpers::CountPlayerUnitsByType()
    {
        int const player = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        MACRO_CALL(OS_Func::_memset)(
            DAT_UnitTypeRelatedCounter::instance, 0, sizeof(DAT_UnitTypeRelatedCounter::instance));
        for (int unitID = 1; unitID < DAT_UnitsState::instance.maxUnitCount; ++unitID) {
            Unit const& unit = DAT_UnitsState::instance.units[unitID];
            if (unit.logicalState != Map::Units::ULS_INVISIBLE && unit.owner == player && !unit.isStalked) {
                int const unitType = unit.unitType;
                // Caged dogs and burning animals are not counted.
                if (unitType >= Map::Units::UT_PEASANT
                    && (unitType <= Map::Units::UT_FIREEATER || unitType >= Map::Units::UT_A_ARCHER)) {
                    ++DAT_UnitTypeRelatedCounter::instance[unitType];
                }
            }
        }
    }

}
}
