#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Map::Buildings::BuildingLogicalState;
    using OpenSHC::Map::Buildings::BuildingType;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004572A0
    void GameStateStructures::validateBuildingCategoryReference(int playerID, int buildingCategory)
    {
        int buildingID = (&this->playerDataArray[playerID].keep)[buildingCategory].id;
        if (buildingID - 1U >= 1999) {
            (&this->playerDataArray[playerID].keep)[buildingCategory].id = 0;
            return;
        }
        if (buildingCategory == 0) {
            if ((DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    != OpenSHC::Map::Buildings::BT_MANORHOUSE)
                && (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    != OpenSHC::Map::Buildings::BT_STONEKEEP)
                && (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    != OpenSHC::Map::Buildings::BT_STRONGHOLD)
                && (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    != OpenSHC::Map::Buildings::BT_KEEPFOUR)
                && (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    != OpenSHC::Map::Buildings::BT_KEEPFIVE)) {
                this->playerDataArray[playerID].keep.id = 0;
                return;
            }
        } else if (buildingCategory == 1) {
            if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                != OpenSHC::Map::Buildings::BT_STOCKPILE) {
                this->playerDataArray[playerID].stockpile.id = 0;
                return;
            }
        } else if (buildingCategory == 2) {
            if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                != OpenSHC::Map::Buildings::BT_GRANARY) {
                this->playerDataArray[playerID].granary.id = 0;
                return;
            }
        } else if (buildingCategory == 3) {
            if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                != OpenSHC::Map::Buildings::BT_ARMORY) {
                this->playerDataArray[playerID].armory.id = 0;
                return;
            }
        } else if (buildingCategory == 5) {
            if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                != OpenSHC::Map::Buildings::BT_BARRACKS) {
                this->playerDataArray[playerID].barracks.id = 0;
                return;
            }
        } else if (buildingCategory == 0xb) {
            if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                != OpenSHC::Map::Buildings::BT_MERCENARYPOST) {
                this->playerDataArray[playerID].mercenaryPost.id = 0;
                return;
            }
        } else if (buildingCategory == 0xc) {
            if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                != OpenSHC::Map::Buildings::BT_OILSMELTER) {
                this->playerDataArray[playerID].oilSmelter.id = 0;
                return;
            }
        } else if (buildingCategory == 7) {
            if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                != OpenSHC::Map::Buildings::BT_MARKETPLACE) {
                this->playerDataArray[playerID].marketplace.id = 0;
                return;
            }
        } else if (buildingCategory == 9) {
            if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                != OpenSHC::Map::Buildings::BT_ENGINEERSGUILD) {
                this->playerDataArray[playerID].engineersGuild.id = 0;
                return;
            }
        } else if ((buildingCategory == 10)
            && (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                != OpenSHC::Map::Buildings::BT_TUNNELERSGUILD)) {
            this->playerDataArray[playerID].tunnelersGuild.id = 0;
            return;
        }
        if ((DAT_BuildingsState::instance.buildings[buildingID].logicalState == ((BuildingLogicalState)0))
            || (DAT_BuildingsState::instance.buildings[buildingID].uid == 0)
            || (DAT_TileMapState::instance.BuildingLayer[DAT_BuildingsState::instance.buildings[buildingID]
                        .currentTilePositionAdjusted]
                != buildingID)) {
            (&this->playerDataArray[playerID].keep)[buildingCategory].id = 0;
        }
    }
}
}
