#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Map::Buildings::BuildingLogicalState;
    using OpenSHC::Map::Buildings::BuildingType;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00458F70
    void GameStateStructures::recomputeReligionBonuses()
    {
        for (int playerID = 1; playerID < 9; playerID++) {
            DAT_GameState::instance.playerDataArray[playerID].religionVar1 = 0;
            DAT_GameState::instance.playerDataArray[playerID].ownsChurchUnk = 0;
            DAT_GameState::instance.playerDataArray[playerID].ownsCathedralUnk = 0;
        }
        for (int buildingID = 1; buildingID < DAT_BuildingsState::instance.maxBuildingsCount; buildingID++) {
            if ((DAT_BuildingsState::instance.buildings[buildingID].logicalState == ((BuildingLogicalState)0))
                || (DAT_BuildingsState::instance.buildings[buildingID].logicalState
                    == OpenSHC::Map::Buildings::BLS_REMOVE)) {
                continue;
            }
            int owner = DAT_BuildingsState::instance.buildings[buildingID].owner;
            if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_CHAPEL) {
                DAT_GameState::instance.playerDataArray[owner].religionVar1 += 1;
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                == OpenSHC::Map::Buildings::BT_CHURCH) {
                DAT_GameState::instance.playerDataArray[owner].ownsChurchUnk += 1;
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                == OpenSHC::Map::Buildings::BT_CATHEDRAL) {
                DAT_GameState::instance.playerDataArray[owner].ownsCathedralUnk += 1;
            }
        }
    }
}
}
