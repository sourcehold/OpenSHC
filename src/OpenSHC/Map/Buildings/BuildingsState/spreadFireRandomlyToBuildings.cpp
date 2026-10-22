#include "../BuildingsState.func.hpp"

#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00422C60
        void BuildingsState::spreadFireRandomlyToBuildings(int playerID, int count)
        {
            if (playerID < 1) {
                return;
            }
            if (DAT_GameState::instance.playerDataArray[playerID].campground.id <= 0) {
                return;
            }
            int weight = 0;
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (this->buildings[buildingID].logicalState == 0
                    || this->buildings[buildingID].logicalState == BLS_REMOVE
                    || this->buildings[buildingID].owner != playerID || this->buildings[buildingID].fireDuration != 0
                    || this->buildings[buildingID].cooldownTimer != 0) {
                    continue;
                }
                int const flammability
                    = MACRO_CALL_MEMBER(BuildingsState_Func::getBuildingFlammabilityFactor, this)(buildingID);
                if (flammability != 0 && flammability != 4) {
                    weight += 1;
                }
                if (flammability == 5) {
                    weight += 4;
                }
            }
            if (weight == 0) {
                return;
            }
            for (; count > 0; --count) {
                if (weight <= 0) {
                    return;
                }
                int pick = SEC_RNG::instance.currentNumber2 % weight;
                MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                    if (this->buildings[buildingID].logicalState == 0
                        || this->buildings[buildingID].logicalState == BLS_REMOVE
                        || this->buildings[buildingID].owner != playerID
                        || this->buildings[buildingID].fireDuration != 0
                        || this->buildings[buildingID].cooldownTimer != 0) {
                        continue;
                    }
                    int const flammability
                        = MACRO_CALL_MEMBER(BuildingsState_Func::getBuildingFlammabilityFactor, this)(buildingID);
                    if (flammability == 0 || flammability == 4) {
                        continue;
                    }
                    pick -= 1;
                    if (MACRO_CALL_MEMBER(BuildingsState_Func::getBuildingFlammabilityFactor, this)(buildingID) == 5) {
                        pick -= 4;
                    }
                    if (pick < 0) {
                        MACRO_CALL_MEMBER(BuildingsState_Func::lightUpBuilding, this)(buildingID, 0, 0);
                        MACRO_CALL_MEMBER(UI::MinimapViewState_Func::setSpawnMoment, DAT_MinimapViewState::ptr)(
                            this->buildings[buildingID].x, this->buildings[buildingID].y);
                        // The original sets the index to 2000 to leave the loop and then queries that building.
                        buildingID = 2000;
                        weight -= 1;
                        if (MACRO_CALL_MEMBER(BuildingsState_Func::getBuildingFlammabilityFactor, this)(buildingID)
                            == 5) {
                            weight -= 4;
                        }
                        break;
                    }
                }
            }
        }

    }
}
}
