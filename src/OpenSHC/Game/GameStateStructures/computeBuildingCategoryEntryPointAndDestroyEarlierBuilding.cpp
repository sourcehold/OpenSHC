#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Game {

    using Player::Enums::BuildingEntryInfoEnum;
    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x00456FD0
    void GameStateStructures::computeBuildingCategoryEntryPointAndDestroyEarlierBuilding(
        uint buildingID, int playerID, BuildingEntryInfoEnum category)
    {
        int entryX = 0;
        int entryY = 0;
        DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
        if (category == Player::Enums::BEIE_KEEP) {
            if (this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_KEEP].id > 0
                && this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_KEEP].id != buildingID) {
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(
                    this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_KEEP].id);
            }
            short orientation = DAT_BuildingsState::instance.buildings[buildingID].orientation;
            entryX = DAT_BuildingsState::instance.buildings[buildingID].x;
            entryY = DAT_BuildingsState::instance.buildings[buildingID].y;
            if (orientation == 4) {
                entryX += 3;
                --entryY;
            } else if (orientation == 2) {
                --entryX;
                entryY += 3;
            } else if (orientation == 6) {
                entryX += 7;
                entryY += 3;
            } else {
                entryX += 3;
                entryY += 7;
            }
            if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
                DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
                if (this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_STOCKPILE].id != 0) {
                    MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(
                        this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_STOCKPILE].id);
                }
            }
        } else {
            // The original reads the building entrance once for all of these categories and jumps to it, the
            // same goes for the destroy call. Writing the read out in every arm (MSVC merges the copies only after
            // register allocation) makes buildingID look hot enough to keep in a register: 33.5% instead of 64.0%.
            int existingID;
            if (category == Player::Enums::BEIE_MARKETPLACE) {
                existingID = this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_MARKETPLACE].id;
            } else if (category == Player::Enums::BEIE_ENGINEERSGUILD) {
                existingID = this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_ENGINEERSGUILD].id;
            } else if (category == Player::Enums::BEIE_TUNNELERSGUILD) {
                existingID = this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_TUNNELERSGUILD].id;
            } else if (category == Player::Enums::BEIE_STOCKPILE) {
                // a storage building of this kind already exists, keep the old entry
                if (this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_STOCKPILE].id > 0) {
                    return;
                }
                goto readEntry;
            } else if (category == Player::Enums::BEIE_ARMORY) {
                // a storage building of this kind already exists, keep the old entry
                if (this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_ARMORY].id > 0) {
                    return;
                }
                goto readEntry;
            } else if (category == Player::Enums::BEIE_GRANARY) {
                // a storage building of this kind already exists, keep the old entry
                if (this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_GRANARY].id > 0) {
                    return;
                }
                goto readEntry;
            } else if (category == Player::Enums::BEIE_BARRACKS) {
                existingID = this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_BARRACKS].id;
            } else if (category == Player::Enums::BEIE_MERCENARYPOST) {
                existingID = this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_MERCENARYPOST].id;
            } else if (category == Player::Enums::BEIE_OILSMELTER) {
                goto readEntry;
            } else if (category == Player::Enums::BEIE_CAMPGROUND) {
                short orientation = DAT_BuildingsState::instance.buildings[buildingID].orientation;
                entryX = DAT_BuildingsState::instance.buildings[buildingID].x;
                entryY = DAT_BuildingsState::instance.buildings[buildingID].y;
                if (orientation == 4) {
                    entryX += 3;
                    entryY += 6;
                } else if (orientation == 2) {
                    entryY += 3;
                } else if (orientation == 6) {
                    entryX += 6;
                    entryY += 3;
                } else {
                    entryX += 3;
                }
                goto checkEntry;
            } else {
                goto checkEntry;
            }
            if (existingID > 0) {
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(
                    existingID);
            }
        readEntry:
            entryX = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryX;
            entryY = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryY;
        }
    checkEntry:
        if (entryX < 0) {
            return;
        }
        if (entryX >= 400) {
            return;
        }
        if (entryY < 0) {
            return;
        }
        if (entryY >= 400) {
            return;
        }
        if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[entryY * 400 + entryX] != 0) {
            this->playerDataArray[playerID].buildingEntryInfos[category].id = buildingID;
            this->playerDataArray[playerID].buildingEntryInfos[category].yEntry = entryY;
            this->playerDataArray[playerID].buildingEntryInfos[category].xEntry = entryX;
            this->playerDataArray[playerID].buildingEntryInfos[category].tileEntry
                = DAT_ViewportRenderState::instance.translationMatrix[entryY].addXgetTile + entryX;
            this->playerDataArray[playerID].buildingEntryInfos[category].areaEntry
                = DAT_TileMapState::instance
                      .PathConnectionLayer[this->playerDataArray[playerID].buildingEntryInfos[category].tileEntry];
            DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 0;
        }
    }

}
}
