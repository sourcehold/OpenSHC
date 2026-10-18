#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/Pathfinding/DestinationNeededEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Game {

    using Map::Units::UnitType;
    using Map::Units::Pathfinding::DestinationNeededEnum;
    using Map::Units::States::UnitState;

    // FUNCTION: STRONGHOLDCRUSADER 0x00459490
    void GameStateStructures::spawnDrunkard(int buildingID)
    {
        uint const entryX = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryX;
        uint const entryY = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryY;
        if (entryX > 399 || entryY > 399
            || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[entryY * 400 + entryX] == 0) {
            return;
        }
        int const playerID = DAT_BuildingsState::instance.buildings[buildingID].owner;
        int const tile = DAT_ViewportRenderState::instance.translationMatrix[entryY].addXgetTile + entryX;
        this->playerDataArray[playerID].field640_0x2178 = buildingID;
        int drunkardLimit;
        if (this->playerDataArray[playerID].populationRelatedCrowdingCountUnk < 20) {
            drunkardLimit = 1;
        } else if (this->playerDataArray[playerID].populationRelatedCrowdingCountUnk < 50) {
            drunkardLimit = 2;
        } else if (this->playerDataArray[playerID].populationRelatedCrowdingCountUnk < 100) {
            drunkardLimit = 3;
        } else {
            drunkardLimit = 4;
        }
        int drunkardsToSpawn = (SEC_RNG::instance.currentNumber2 & 3) + 1;
        if (drunkardsToSpawn > drunkardLimit) {
            drunkardsToSpawn = drunkardLimit;
        }
        for (int i = 0; i < drunkardsToSpawn; ++i) {
            int const unitID = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(playerID,
                playerID, DAT_BuildingsState::instance.buildings[buildingID].buildingEntryX * 8,
                DAT_BuildingsState::instance.buildings[buildingID].buildingEntryY * 8,
                DAT_TileMapState::instance.HeightLayer[tile], Map::Units::UT_DRUNK);
            if (unitID != 0) {
                DAT_UnitsState::instance.units[unitID].resourceToDeposit = 0;
                DAT_UnitsState::instance.units[unitID].substate = SEC_RNG::instance.currentNumber2 & 1;
                DAT_UnitsState::instance.units[unitID].state.generic = Map::Units::States::US_IDLEUnk;
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            }
        }
    }

}
}
