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
        /*
          the per player counters are cleared one by one, exactly as the original binary does
         */
        DAT_GameState::instance.playerDataArray[1].religionVar1 = 0;
        DAT_GameState::instance.playerDataArray[1].ownsChurchUnk = 0;
        DAT_GameState::instance.playerDataArray[1].ownsCathedralUnk = 0;
        DAT_GameState::instance.playerDataArray[2].religionVar1 = 0;
        DAT_GameState::instance.playerDataArray[2].ownsChurchUnk = 0;
        DAT_GameState::instance.playerDataArray[2].ownsCathedralUnk = 0;
        DAT_GameState::instance.playerDataArray[3].religionVar1 = 0;
        DAT_GameState::instance.playerDataArray[3].ownsChurchUnk = 0;
        DAT_GameState::instance.playerDataArray[3].ownsCathedralUnk = 0;
        DAT_GameState::instance.playerDataArray[4].religionVar1 = 0;
        DAT_GameState::instance.playerDataArray[4].ownsChurchUnk = 0;
        DAT_GameState::instance.playerDataArray[4].ownsCathedralUnk = 0;
        DAT_GameState::instance.playerDataArray[5].religionVar1 = 0;
        DAT_GameState::instance.playerDataArray[5].ownsChurchUnk = 0;
        DAT_GameState::instance.playerDataArray[5].ownsCathedralUnk = 0;
        DAT_GameState::instance.playerDataArray[6].religionVar1 = 0;
        DAT_GameState::instance.playerDataArray[6].ownsChurchUnk = 0;
        DAT_GameState::instance.playerDataArray[6].ownsCathedralUnk = 0;
        DAT_GameState::instance.playerDataArray[7].religionVar1 = 0;
        DAT_GameState::instance.playerDataArray[7].ownsChurchUnk = 0;
        DAT_GameState::instance.playerDataArray[7].ownsCathedralUnk = 0;
        DAT_GameState::instance.playerDataArray[8].religionVar1 = 0;
        DAT_GameState::instance.playerDataArray[8].ownsChurchUnk = 0;
        DAT_GameState::instance.playerDataArray[8].ownsCathedralUnk = 0;
        for (int buildingID = 1; buildingID < DAT_BuildingsState::instance.maxBuildingsCount; buildingID++) {
            if ((DAT_BuildingsState::instance.buildings[buildingID].logicalState != ((BuildingLogicalState)0))
                && (DAT_BuildingsState::instance.buildings[buildingID].logicalState
                    != OpenSHC::Map::Buildings::BLS_REMOVE)) {
                if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_CHAPEL) {
                    DAT_GameState::instance.playerDataArray[DAT_BuildingsState::instance.buildings[buildingID].owner].religionVar1
                        = DAT_GameState::instance.playerDataArray[DAT_BuildingsState::instance.buildings[buildingID].owner].religionVar1
                        + 1;
                } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_CHURCH) {
                    DAT_GameState::instance.playerDataArray[DAT_BuildingsState::instance.buildings[buildingID].owner].ownsChurchUnk
                        = DAT_GameState::instance.playerDataArray[DAT_BuildingsState::instance.buildings[buildingID].owner].ownsChurchUnk
                        + 1;
                } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_CATHEDRAL) {
                    DAT_GameState::instance.playerDataArray[DAT_BuildingsState::instance.buildings[buildingID].owner].ownsCathedralUnk
                        = DAT_GameState::instance.playerDataArray[DAT_BuildingsState::instance.buildings[buildingID].owner]
                              .ownsCathedralUnk
                        + 1;
                }
            }
        }
    }
}
}
