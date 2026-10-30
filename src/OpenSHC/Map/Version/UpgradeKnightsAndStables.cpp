#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0041A650
    void Version::UpgradeKnightsAndStables()
    {
        for (int buildingID = 0; buildingID < 2000; ++buildingID) {
            if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == Buildings::BT_STABLES) {
                DAT_BuildingsState::instance.buildings[buildingID].randomOutpostField = 0;
                for (int unitID = 0; unitID < 2500; ++unitID) {
                    if (DAT_UnitsState::instance.units[unitID].unitType == Units::UT_E_KNIGHT
                        && DAT_UnitsState::instance.units[unitID].horseOriginStablesBuildingIndexUnk == buildingID
                        && *(int*)&DAT_UnitsState::instance.units[unitID].horseOriginStableIDUnk
                            == DAT_BuildingsState::instance.buildings[buildingID].uid) {
                        DAT_BuildingsState::instance.buildings[buildingID]
                            .insideUnitID[DAT_BuildingsState::instance.buildings[buildingID].randomOutpostField]
                            = (short)unitID;
                        DAT_BuildingsState::instance.buildings[buildingID]
                            .insideUnitUID[DAT_BuildingsState::instance.buildings[buildingID].randomOutpostField]
                            = DAT_UnitsState::instance.units[unitID].uid;
                        DAT_BuildingsState::instance.buildings[buildingID].randomOutpostField += 1;
                        if (DAT_BuildingsState::instance.buildings[buildingID].randomOutpostField >= 4) {
                            break;
                        }
                    }
                }
            }
        }
    }

}
}
