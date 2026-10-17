#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Map::Buildings::BuildingLogicalState;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0045C050
    void GameStateStructures::spawnPoisonCloudsAtRandomStorageOrArmyBuilding(int playerID, int count)
    {
        int targetCount = 0;
        if (this->playerDataArray[playerID].campground.id <= 0) {
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::spawnPoisonCloudsAroundBuilding, this)(
            this->playerDataArray[playerID].campground.id);
        for (int buildingID = 1; buildingID < DAT_BuildingsState::instance.maxBuildingsCount; buildingID++) {
            if ((DAT_BuildingsState::instance.buildings[buildingID].logicalState != ((BuildingLogicalState)0))
                && (DAT_BuildingsState::instance.buildings[buildingID].logicalState
                    != OpenSHC::Map::Buildings::BLS_REMOVE)
                && (DAT_BuildingsState::instance.buildings[buildingID].owner == playerID)) {
                switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
                case OpenSHC::Map::Buildings::BT_MERCENARYPOST:
                case OpenSHC::Map::Buildings::BT_BARRACKS:
                case OpenSHC::Map::Buildings::BT_STOCKPILE:
                case OpenSHC::Map::Buildings::BT_ARMORY:
                case OpenSHC::Map::Buildings::BT_GRANARY:
                case OpenSHC::Map::Buildings::BT_ENGINEERSGUILD:
                case OpenSHC::Map::Buildings::BT_TUNNELERSGUILD:
                    targetCount = targetCount + 1;
                }
            }
        }
        if (targetCount == 0) {
            return;
        }
        for (; count > 0; count = count - 1) {
            int targetsToSkip = (int)SEC_RNG::instance.currentNumber2 % targetCount;
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            for (int buildingID = 1; buildingID < DAT_BuildingsState::instance.maxBuildingsCount; buildingID++) {
                if ((DAT_BuildingsState::instance.buildings[buildingID].logicalState != ((BuildingLogicalState)0))
                    && (DAT_BuildingsState::instance.buildings[buildingID].logicalState
                        != OpenSHC::Map::Buildings::BLS_REMOVE)
                    && (DAT_BuildingsState::instance.buildings[buildingID].owner == playerID)) {
                    switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
                    case OpenSHC::Map::Buildings::BT_MERCENARYPOST:
                    case OpenSHC::Map::Buildings::BT_BARRACKS:
                    case OpenSHC::Map::Buildings::BT_STOCKPILE:
                    case OpenSHC::Map::Buildings::BT_ARMORY:
                    case OpenSHC::Map::Buildings::BT_GRANARY:
                    case OpenSHC::Map::Buildings::BT_ENGINEERSGUILD:
                    case OpenSHC::Map::Buildings::BT_TUNNELERSGUILD:
                        targetsToSkip = targetsToSkip - 1;
                        if (targetsToSkip < 0) {
                            MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::spawnPoisonCloudsAroundBuilding,
                                this)(buildingID);
                            buildingID = 2000;
                        }
                    }
                }
            }
        }
    }
}
}
