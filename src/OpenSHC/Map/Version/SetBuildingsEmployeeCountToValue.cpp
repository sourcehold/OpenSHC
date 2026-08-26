#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Buildings::Building;
    using OpenSHC::Map::Buildings::BuildingLogicalState;

    // FUNCTION: STRONGHOLDCRUSADER 0x0041A390
    void Version::SetBuildingsEmployeeCountToValue()
    {
        for (int _buildingID = 1; _buildingID < 2000; _buildingID++) {
            if (DAT_BuildingsState::instance.buildings[_buildingID].logicalState != ((BuildingLogicalState)0)) {
                DAT_BuildingsState::instance.buildings[_buildingID].buildingTypeBasedEmployeeCount
                    = DAT_BuildingDefinedData::instance
                          .EmployeeCountPerBuildingType[DAT_BuildingsState::instance.buildings[_buildingID]
                                  .buildingType]
                          .shortValue;
            }
        }
    }

}
}
