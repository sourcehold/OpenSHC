
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_APPLE;

    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_APPLE;

    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x005160C0
    BOOLEnum TileMapState::prepareAreaForBuildingPlacement(
        int playerID, uint x, uint y, MappersEnum commandBuildingType, int buildingWidthOrHeight)
    {
        BOOLEnum result = FALSE;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::storeMinAndMaxHeightOfArea, this)(x, y, buildingWidthOrHeight);

        int index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, buildingWidthOrHeight);
            uint tileY = y + this->buildingY;
            if (x + this->buildingX > 399 || tileY > 399) {
                return FALSE;
            }
            if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[tileY * 400 + x + this->buildingX] == 0) {
                return FALSE;
            }
            int tile = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + this->buildingX + x;
            if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                return FALSE;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                    tile, playerID, (MappersEnum)(short)commandBuildingType, 1)
                == 1) {
                return FALSE;
            }
            index++;
        } while (index < this->constructionTileCount);

        /* the original walks the footprint again through the command parameter */
        commandBuildingType = OpenSHC::Commands::M_MAPPER_NULL;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                commandBuildingType, buildingWidthOrHeight);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile + x + this->buildingX;
            int buildingID = DAT_TileMapState::instance.BuildingLayer[tile];
            bool cleared = false;
            if (buildingID != 0) {
                if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_WOODCUTTERSHUT || DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_OXTETHER || DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_QUARRY || DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_IRONMINE || DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_WHEATFARM || DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_HOPFARM || DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_APPLEFARM || DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_DAIRYFARM) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::giveBackResourceForDestroyedBuilding,
                        DAT_BuildingsState::ptr)(buildingID, playerID, 50);
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingFromTerrain, this)(buildingID);
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::updatePrimaryBuildingPlayerDataReferences,
                        DAT_GameState::ptr)(buildingID);
                    cleared = true;
                }
            } else if ((DAT_TileMapState::instance.LogicLayer[tile] & L_FARM_FIELD_APPLE) != 0) {
                buildingID = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::getFarmThatHasTile,
                    DAT_BuildingsState::ptr)(tile);
                if (buildingID != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::giveBackResourceForDestroyedBuilding,
                        DAT_BuildingsState::ptr)(buildingID, playerID, 0x32);
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingFromTerrain, this)(buildingID);
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::updatePrimaryBuildingPlayerDataReferences,
                        DAT_GameState::ptr)(buildingID);
                    cleared = true;
                }
            }
            if (cleared) {
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x32c, '\0', DAT_BuildingsState::instance.buildings + buildingID);
                result = TRUE;
            }
            commandBuildingType = (MappersEnum)(commandBuildingType + OpenSHC::Commands::M_MAPPER_AREA);
        } while ((int)commandBuildingType < this->constructionTileCount);
        return result;
    }

}
}
