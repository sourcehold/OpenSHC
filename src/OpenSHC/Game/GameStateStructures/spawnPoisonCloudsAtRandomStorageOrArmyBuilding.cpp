#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Game {

    using Map::Buildings::BuildingLogicalState;

    // FUNCTION: STRONGHOLDCRUSADER 0x0045C050
    void GameStateStructures::spawnPoisonCloudsAtRandomStorageOrArmyBuilding(int playerID, int count)
    {
        int targetCount = 0;
        if (this->playerDataArray[playerID].campground.id <= 0) {
            return;
        }
        MACRO_CALL_MEMBER(GameStateStructures_Func::spawnPoisonCloudsAroundBuilding, this)(
            this->playerDataArray[playerID].campground.id);
        for (int buildingID = 1; buildingID < DAT_BuildingsState::instance.maxBuildingsCount; ++buildingID) {
            if (DAT_BuildingsState::instance.buildings[buildingID].logicalState != (BuildingLogicalState)0
                && DAT_BuildingsState::instance.buildings[buildingID].logicalState != Map::Buildings::BLS_REMOVE
                && DAT_BuildingsState::instance.buildings[buildingID].owner == playerID) {
                switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
                case Map::Buildings::BT_MERCENARYPOST:
                case Map::Buildings::BT_BARRACKS:
                case Map::Buildings::BT_STOCKPILE:
                case Map::Buildings::BT_ARMORY:
                case Map::Buildings::BT_GRANARY:
                case Map::Buildings::BT_ENGINEERSGUILD:
                case Map::Buildings::BT_TUNNELERSGUILD:
                    ++targetCount;
                }
            }
        }
        if (targetCount == 0) {
            return;
        }
        for (; count > 0; count = count - 1) {
            int targetsToSkip = (int)SEC_RNG::instance.currentNumber2 % targetCount;
            MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            for (int buildingID = 1; buildingID < DAT_BuildingsState::instance.maxBuildingsCount; ++buildingID) {
                if (DAT_BuildingsState::instance.buildings[buildingID].logicalState != (BuildingLogicalState)0
                    && DAT_BuildingsState::instance.buildings[buildingID].logicalState != Map::Buildings::BLS_REMOVE
                    && DAT_BuildingsState::instance.buildings[buildingID].owner == playerID) {
                    switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
                    case Map::Buildings::BT_MERCENARYPOST:
                    case Map::Buildings::BT_BARRACKS:
                    case Map::Buildings::BT_STOCKPILE:
                    case Map::Buildings::BT_ARMORY:
                    case Map::Buildings::BT_GRANARY:
                    case Map::Buildings::BT_ENGINEERSGUILD:
                    case Map::Buildings::BT_TUNNELERSGUILD:
                        --targetsToSkip;
                        if (targetsToSkip < 0) {
                            MACRO_CALL_MEMBER(GameStateStructures_Func::spawnPoisonCloudsAroundBuilding, this)(
                                buildingID);
                            buildingID = 2000;
                        }
                    }
                }
            }
        }
    }

}
}
