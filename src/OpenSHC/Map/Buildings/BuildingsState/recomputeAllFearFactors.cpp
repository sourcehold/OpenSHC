#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040B260
        void BuildingsState::recomputeAllFearFactors()
        {
            // Matching note: The original keeps each 'goodOrBad = -1' as its own block that jumps to a shared
            // compare of goodOrBad; our compiler jump-threads the constants straight into the counters. An inlined
            // helper returning -1/0/1 was tried and made it worse (31% -> 15%).
            for (int p = 1; p < 9; ++p) {
                DAT_GameState::instance.playerDataArray[p].badStuffCount = 0;
                DAT_GameState::instance.playerDataArray[p].goodStuffCount = 0;
                DAT_GameState::instance.playerDataArray[p].fearFactorLevel = 0;
            }

            // Count the good and bad things of every player
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState == 0 || this->buildings[i].logicalState == BLS_REMOVE) {
                    continue;
                }
                int goodOrBad = 0;
                if (this->buildings[i].buildingType == BT_GALLOWS) {
                    goodOrBad = -1;
                } else if (this->buildings[i].buildingType == BT_STOCKS) {
                    goodOrBad = -1;
                } else if (this->buildings[i].buildingType == BT_WITCHHOIST) {
                    goodOrBad = -1;
                } else if (this->buildings[i].buildingType == BT_CESSPIT) {
                    goodOrBad = -1;
                } else if (this->buildings[i].buildingType == BT_BURNINGSTAKE) {
                    goodOrBad = -1;
                } else if (this->buildings[i].buildingType == BT_GIBBET) {
                    goodOrBad = -1;
                } else if (this->buildings[i].buildingType == BT_DUNGEON) {
                    goodOrBad = -1;
                } else if (this->buildings[i].buildingType == BT_STRETCHINGRACK) {
                    goodOrBad = -1;
                } else if (this->buildings[i].buildingType == BT_RACKFLOGGING) {
                    goodOrBad = -1;
                } else if (this->buildings[i].buildingType == BT_CHOPPINGBLOCK) {
                    goodOrBad = -1;
                } else if (this->buildings[i].buildingType == BT_DUNKINGSTOOL) {
                    goodOrBad = -1;
                } else if (this->buildings[i].buildingType == BT_MAYPOLE || this->buildings[i].buildingType == BT_GARDEN
                    || this->buildings[i].buildingType == BT_STATUE || this->buildings[i].buildingType == BT_SHRINE
                    || this->buildings[i].buildingType == BT_DANCINGBEAR) {
                    goodOrBad = 1;
                }
                if (goodOrBad < 0) {
                    ++DAT_GameState::instance.playerDataArray[this->buildings[i].owner].badStuffCount;
                } else if (goodOrBad > 0) {
                    ++DAT_GameState::instance.playerDataArray[this->buildings[i].owner].goodStuffCount;
                }
            }

            // Every 16 peasants need one more good or bad thing for the next fear factor level
            for (int p = 1; p < 9; ++p) {
                int thingsPerLevel = DAT_GameState::instance.playerDataArray[p].currentPopulation / 16 + 1;
                int balance = DAT_GameState::instance.playerDataArray[p].goodStuffCount
                    - DAT_GameState::instance.playerDataArray[p].badStuffCount;
                if (balance < 0) {
                    balance = -balance;
                    int level = -(balance / thingsPerLevel);
                    DAT_GameState::instance.playerDataArray[p].fearFactorLevel = level;
                    DAT_GameState::instance.playerDataArray[p].objectsLeftUntilNextLevel
                        = thingsPerLevel - balance % thingsPerLevel;
                    if (level < -5) {
                        DAT_GameState::instance.playerDataArray[p].fearFactorLevel = -5;
                    }
                } else if (balance > 0) {
                    int level = balance / thingsPerLevel;
                    DAT_GameState::instance.playerDataArray[p].fearFactorLevel = level;
                    DAT_GameState::instance.playerDataArray[p].objectsLeftUntilNextLevel
                        = thingsPerLevel - balance % thingsPerLevel;
                    if (level > 5) {
                        DAT_GameState::instance.playerDataArray[p].fearFactorLevel = 5;
                    }
                } else {
                    DAT_GameState::instance.playerDataArray[p].objectsLeftUntilNextLevel = 0;
                }

                // Track the extremes for the final statistics while the lord is alive
                int lordID = DAT_GameState::instance.playerDataArray[p].lordID;
                if (lordID != 0
                    && DAT_GameState::instance.playerDataArray[p].lordUID == DAT_UnitsState::instance.units[lordID].uid
                    && DAT_UnitsState::instance.units[lordID].logicalState == OpenSHC::Map::Units::ULS_NORMAL) {
                    int level = DAT_GameState::instance.playerDataArray[p].fearFactorLevel;
                    if (level > 0) {
                        if (level > (char)DAT_GameSynchronyState::instance.finalResults.finalMaxGoodThings[p]) {
                            DAT_GameSynchronyState::instance.finalResults.finalMaxGoodThings[p] = level;
                        }
                    } else if (level < 0) {
                        if (level < (char)DAT_GameSynchronyState::instance.finalResults.finalMaxBadThings[p]) {
                            DAT_GameSynchronyState::instance.finalResults.finalMaxBadThings[p] = level;
                        }
                    }
                }
            }
        }

    }
}
}
