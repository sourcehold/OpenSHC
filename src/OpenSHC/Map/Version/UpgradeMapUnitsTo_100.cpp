#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0053B380
    void Version::UpgradeMapUnitsTo_100()
    {
        for (DAT_CurrentUnitSlotID::instance = 1; DAT_CurrentUnitSlotID::instance < 2500;
            ++DAT_CurrentUnitSlotID::instance) {
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState == Units::ULS_NORMAL) {
                int buildingID = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceBuildingID_1;
                if (buildingID != 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].unitRefID
                        = (short)DAT_CurrentUnitSlotID::instance;
                    DAT_BuildingsState::instance.buildings[buildingID].unitRefUID
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].uid;
                }
            }
        }
    }

}
}
