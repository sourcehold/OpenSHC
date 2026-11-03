#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Game {

    using Map::Buildings::BuildingLogicalState;

    // FUNCTION: STRONGHOLDCRUSADER 0x004572A0
    void GameStateStructures::validateBuildingCategoryReference(int playerID, int buildingCategory)
    {
        int const buildingID = this->playerDataArray[playerID].buildingEntryInfos[buildingCategory].id;
        if (buildingID > 0 && buildingID <= 1999) {
            if (buildingCategory == Player::Enums::BEIE_KEEP) {
                if (DAT_BuildingsState::instance.buildings[buildingID].buildingType != Map::Buildings::BT_MANORHOUSE
                    && DAT_BuildingsState::instance.buildings[buildingID].buildingType != Map::Buildings::BT_STONEKEEP
                    && DAT_BuildingsState::instance.buildings[buildingID].buildingType != Map::Buildings::BT_STRONGHOLD
                    && DAT_BuildingsState::instance.buildings[buildingID].buildingType != Map::Buildings::BT_KEEPFOUR
                    && DAT_BuildingsState::instance.buildings[buildingID].buildingType != Map::Buildings::BT_KEEPFIVE) {
                    this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_KEEP].id = 0;
                    return;
                }
            } else if (buildingCategory == Player::Enums::BEIE_STOCKPILE) {
                if (DAT_BuildingsState::instance.buildings[buildingID].buildingType != Map::Buildings::BT_STOCKPILE) {
                    this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_STOCKPILE].id = 0;
                    return;
                }
            } else if (buildingCategory == Player::Enums::BEIE_GRANARY) {
                if (DAT_BuildingsState::instance.buildings[buildingID].buildingType != Map::Buildings::BT_GRANARY) {
                    this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_GRANARY].id = 0;
                    return;
                }
            } else if (buildingCategory == Player::Enums::BEIE_ARMORY) {
                if (DAT_BuildingsState::instance.buildings[buildingID].buildingType != Map::Buildings::BT_ARMORY) {
                    this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_ARMORY].id = 0;
                    return;
                }
            } else if (buildingCategory == Player::Enums::BEIE_BARRACKS) {
                if (DAT_BuildingsState::instance.buildings[buildingID].buildingType != Map::Buildings::BT_BARRACKS) {
                    this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_BARRACKS].id = 0;
                    return;
                }
            } else if (buildingCategory == Player::Enums::BEIE_MERCENARYPOST) {
                if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    != Map::Buildings::BT_MERCENARYPOST) {
                    this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_MERCENARYPOST].id = 0;
                    return;
                }
            } else if (buildingCategory == Player::Enums::BEIE_OILSMELTER) {
                if (DAT_BuildingsState::instance.buildings[buildingID].buildingType != Map::Buildings::BT_OILSMELTER) {
                    this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_OILSMELTER].id = 0;
                    return;
                }
            } else if (buildingCategory == Player::Enums::BEIE_MARKETPLACE) {
                if (DAT_BuildingsState::instance.buildings[buildingID].buildingType != Map::Buildings::BT_MARKETPLACE) {
                    this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_MARKETPLACE].id = 0;
                    return;
                }
            } else if (buildingCategory == Player::Enums::BEIE_ENGINEERSGUILD) {
                if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    != Map::Buildings::BT_ENGINEERSGUILD) {
                    this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_ENGINEERSGUILD].id = 0;
                    return;
                }
            } else if (buildingCategory == Player::Enums::BEIE_TUNNELERSGUILD
                && DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    != Map::Buildings::BT_TUNNELERSGUILD) {
                this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_TUNNELERSGUILD].id = 0;
                return;
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].logicalState == (BuildingLogicalState)0
                || DAT_BuildingsState::instance.buildings[buildingID].uid == 0
                || DAT_TileMapState::instance
                        .BuildingLayer[DAT_BuildingsState::instance.buildings[buildingID].currentTilePositionAdjusted]
                    != buildingID) {
                this->playerDataArray[playerID].buildingEntryInfos[buildingCategory].id = 0;
            }
        } else {
            this->playerDataArray[playerID].buildingEntryInfos[buildingCategory].id = 0;
        }
    }

}
}
