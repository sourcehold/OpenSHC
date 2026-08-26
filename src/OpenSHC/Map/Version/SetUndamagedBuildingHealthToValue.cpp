#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Buildings::Building;
    using OpenSHC::Map::Buildings::BuildingLogicalState;

    // FUNCTION: STRONGHOLDCRUSADER 0x0041A060
    void Version::SetUndamagedBuildingHealthToValue()
    {
        for (int _buildingID = 1; _buildingID < 2000; _buildingID += 1) {
            if ((DAT_BuildingsState::instance.buildings[_buildingID].logicalState != ((BuildingLogicalState)0))
                && (DAT_BuildingsState::instance.buildings[_buildingID].currentHealth
                    == DAT_BuildingsState::instance.buildings[_buildingID].maxHealth)) {
                uint health = DAT_BuildingDefinedData::instance
                                  .BuildingHP[(short)DAT_BuildingsState::instance.buildings[_buildingID].buildingType]
                                  .ushortValue;
                DAT_BuildingsState::instance.buildings[_buildingID].maxHealth = health;
                DAT_BuildingsState::instance.buildings[_buildingID].currentHealth = health;
            }
        }
    }

}
}
