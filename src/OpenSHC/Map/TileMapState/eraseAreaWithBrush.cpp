#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;

    using OpenSHC::Map::Units::UnitLogicState;

    // FUNCTION: STRONGHOLDCRUSADER 0x00508EC0
    void TileMapState::eraseAreaWithBrush(uint x, uint y, uint brush)
    {
        if (x > 399) {
            return;
        }
        if (y > 399) {
            return;
        }
        if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == 0) {
            return;
        }

        int const brushSize = DAT_TerrainDefinedData::instance.BrushSizeArray[brush];
        uint const savedY = y;
        int const baseTile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
        int tile = baseTile;

        if (brushSize > 0) {
            int index = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(
                    1, index, &tile, (int*)&y, baseTile, savedY);
                if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                    break;
                }
                int const organism = this->OrganismLayer[tile];
                if (organism != 0) {
                    // tree ids come first, rock ids are biased by 2000
                    if (organism >= 2000) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::removeRock, DAT_LandscapeState::ptr)(
                            organism - 2000);
                        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
                            DAT_PathFindingState::ptr)(8, x, y);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::removeTree, DAT_LandscapeState::ptr)(
                            organism);
                        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
                            DAT_PathFindingState::ptr)(3, x, y);
                    }
                    DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
                    DAT_TileMapState::instance.field_0x554a30 = 1;
                }
                index++;
            } while (index < brushSize);
        }

        y = savedY;
        if (brushSize > 0) {
            int index = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(
                    1, index, &tile, (int*)&y, baseTile, savedY);
                if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                    break;
                }
                this->placementOnWall = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::validateBuildingPlacementAtTile, this)(0, x, y);
                if (this->buildingPlacementFail == FALSE) {
                    if (this->placementOnWall == 0) {
                        int const targetID = this->cursorTargetID;
                        if (targetID != -1) {
                            // razing a keep takes the stockpile with it, and the other way round
                            int const owner = DAT_BuildingsState::instance.buildings[targetID].owner;
                            if (targetID
                                    == DAT_GameState::instance.playerDataArray[owner]
                                        .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                                        .id
                                && DAT_GameState::instance.playerDataArray[owner]
                                        .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_STOCKPILE]
                                        .id
                                    != 0) {
                                this->showNoRubbleWhenDestroyingBuilding = 1;
                                MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuildingAndLinkedDuplicates,
                                    DAT_BuildingsState::ptr)(DAT_GameState::instance.playerDataArray[owner]
                                        .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_STOCKPILE]
                                        .id);
                            }
                            if (DAT_BuildingsState::instance.buildings[targetID].buildingType
                                    == OpenSHC::Map::Buildings::BT_STOCKPILE
                                && DAT_GameState::instance.playerDataArray[owner]
                                        .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                                        .id
                                    != 0) {
                                this->showNoRubbleWhenDestroyingBuilding = 1;
                                MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuildingAndLinkedDuplicates,
                                    DAT_BuildingsState::ptr)(DAT_GameState::instance.playerDataArray[owner]
                                        .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                                        .id);
                            }
                            this->showNoRubbleWhenDestroyingBuilding = 1;
                            MACRO_CALL_MEMBER(
                                OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuildingAndLinkedDuplicates,
                                DAT_BuildingsState::ptr)(this->cursorTargetID);
                        }
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::spawnEraserTileEffect, this)(
                            0, DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x);
                    }
                }
                index++;
            } while (index < brushSize);
        }

        y = savedY;
        if (brushSize > 0) {
            int index = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(
                    1, index, &tile, (int*)&y, baseTile, savedY);
                if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                    return;
                }
                for (int unit = DAT_TileMapState::instance.UnitLayer[tile]; unit != 0;
                    unit = DAT_UnitsState::instance.units[unit].nextUnitOnTheSameTile) {
                    DAT_UnitsState::instance.units[unit].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                }
                index++;
            } while (index < brushSize);
        }
    }

}
}
