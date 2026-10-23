#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040E990
        uint BuildingsState::getActiveEngineerForBuilding(int buildingID)
        {
            int unitID = DAT_BuildingsState::instance.buildings[buildingID].workerID[0];
            if (DAT_BuildingsState::instance.buildings[buildingID].workerUID[0]
                != DAT_UnitsState::instance.units[unitID].uid) {
                return 0;
            }
            if (DAT_UnitsState::instance.units[unitID].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                return 0;
            }
            if (DAT_UnitsState::instance.units[unitID].unitType != OpenSHC::Map::Units::UT_E_ENGINEER) {
                return 0;
            }
            if (DAT_UnitsState::instance.units[unitID].dying != 0) {
                return 0;
            }
            if (DAT_UnitsState::instance.units[unitID].workplaceBuildingID_1 != buildingID) {
                return 0;
            }
            return DAT_UnitsState::instance.units[unitID].field252_0x3c4 != 0 ? unitID : 0;
        }

    }
}
}
