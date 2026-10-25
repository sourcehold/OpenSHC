#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Game {

    using Map::Buildings::BuildingLogicalState;

    // FUNCTION: STRONGHOLDCRUSADER 0x004598B0
    void GameStateStructures::recountStablesAndHorses()
    {
        for (int playerID = 1; playerID < 9; ++playerID) {
            this->playerDataArray[playerID].availableHorses = 0;
        }
        for (int buildingID = 1; buildingID < DAT_BuildingsState::instance.maxBuildingsCount; ++buildingID) {
            if (DAT_BuildingsState::instance.buildings[buildingID].logicalState != (BuildingLogicalState)0
                && DAT_BuildingsState::instance.buildings[buildingID].logicalState != Map::Buildings::BLS_REMOVE
                && DAT_BuildingsState::instance.buildings[buildingID].buildingType == Map::Buildings::BT_STABLES) {
                // number of animals - number of animals in use (horses)
                this->playerDataArray[DAT_BuildingsState::instance.buildings[buildingID].owner].availableHorses
                    = this->playerDataArray[DAT_BuildingsState::instance.buildings[buildingID].owner].availableHorses
                    + ((short)(char)DAT_BuildingsState::instance.buildings[buildingID].numberOfAnimals
                        - (short)DAT_BuildingsState::instance.buildings[buildingID].randomOutpostField);
            }
        }
    }

}
}
