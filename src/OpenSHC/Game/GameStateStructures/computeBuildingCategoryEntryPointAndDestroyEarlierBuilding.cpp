#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/Player/PlayerDataBuildingCategoryEnum.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::Player::PlayerDataBuildingCategoryEnum;
    using OpenSHC::UI::Enums::MenuViewType;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00456FD0
    void GameStateStructures::computeBuildingCategoryEntryPointAndDestroyEarlierBuilding(
        uint buildingID, int playerID, PlayerDataBuildingCategoryEnum category)
    {
        int entryX = 0;
        int entryY = 0;
        DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
        if (category == OpenSHC::Game::Player::PDBCE_KEEP) {
            if (((int)this->playerDataArray[playerID].keep.id > 0)
                && (this->playerDataArray[playerID].keep.id != buildingID)) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding,
                    DAT_BuildingsState::ptr)(this->playerDataArray[playerID].keep.id);
            }
            short orientation = DAT_BuildingsState::instance.buildings[buildingID].orientation;
            entryX = (short)DAT_BuildingsState::instance.buildings[buildingID].x;
            entryY = (short)DAT_BuildingsState::instance.buildings[buildingID].y;
            if (orientation == 4) {
                entryX = entryX + 3;
                entryY = entryY - 1;
            } else if (orientation == 2) {
                entryX = entryX - 1;
                entryY = entryY + 3;
            } else if (orientation == 6) {
                entryX = entryX + 7;
                entryY = entryY + 3;
            } else {
                entryX = entryX + 3;
                entryY = entryY + 7;
            }
            if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
                DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
                if (this->playerDataArray[playerID].stockpile.id != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding,
                        DAT_BuildingsState::ptr)(this->playerDataArray[playerID].stockpile.id);
                }
            }
        } else if (category == OpenSHC::Game::Player::PDBCE_CAMPGROUND) {
            short orientation = DAT_BuildingsState::instance.buildings[buildingID].orientation;
            entryX = (short)DAT_BuildingsState::instance.buildings[buildingID].x;
            entryY = (short)DAT_BuildingsState::instance.buildings[buildingID].y;
            if (orientation == 4) {
                entryX = entryX + 3;
                entryY = entryY + 6;
            } else if (orientation == 2) {
                entryY = entryY + 3;
            } else if (orientation == 6) {
                entryX = entryX + 6;
                entryY = entryY + 3;
            } else {
                entryX = entryX + 3;
            }
        } else if ((category == OpenSHC::Game::Player::PDBCE_STOCKPILE)
            || (category == OpenSHC::Game::Player::PDBCE_ARMORY)
            || (category == OpenSHC::Game::Player::PDBCE_GRANARY)) {
            /*
              a storage building of this kind already exists, keep the old entry
             */
            if ((&this->playerDataArray[playerID].keep)[category].id > 0) {
                DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
                return;
            }
            entryX = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryX;
            entryY = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryY;
        } else {
            if ((category == OpenSHC::Game::Player::PDBCE_MARKETPLACE)
                || (category == OpenSHC::Game::Player::PDBCE_ENGINEERSGUILD)
                || (category == OpenSHC::Game::Player::PDBCE_TUNNELERSGUILD)
                || (category == OpenSHC::Game::Player::PDBCE_BARRACKS)
                || (category == OpenSHC::Game::Player::PDBCE_MERCENARYPOST)) {
                if ((&this->playerDataArray[playerID].keep)[category].id > 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding,
                        DAT_BuildingsState::ptr)((&this->playerDataArray[playerID].keep)[category].id);
                }
            }
            entryX = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryX;
            entryY = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryY;
        }
        if (entryX < 0) {
            return;
        }
        if (entryX > 399) {
            return;
        }
        if (entryY < 0) {
            return;
        }
        if (entryY > 399) {
            return;
        }
        if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[entryY * 400 + entryX] != 0) {
            (&this->playerDataArray[playerID].keep)[category].id = buildingID;
            (&this->playerDataArray[playerID].keep)[category].yEntry = entryY;
            (&this->playerDataArray[playerID].keep)[category].xEntry = entryX;
            (&this->playerDataArray[playerID].keep)[category].tileEntry
                = DAT_ViewportRenderState::instance.translationMatrix[entryY].addXgetTile + entryX;
            (&this->playerDataArray[playerID].keep)[category].areaEntry
                = (short)DAT_TileMapState::instance
                      .PathConnectionLayer[(&this->playerDataArray[playerID].keep)[category].tileEntry];
            DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 0;
        }
    }
}
}
