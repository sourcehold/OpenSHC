
#include "OpenSHC/AI/AIVState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;

    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      WARNING: Enum "MappersEnumShort": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00508250
    void TileMapState::placeQuarry(int playerID, uint x, uint y, undefined4 buildingType, uint buildingSize,
        int buildingOrientation, uint height)
    {
        uint baseY = y;
        int uid = DAT_GameCore::instance.uniqueGameObjectTracker;
        int quarryID = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(playerID, x, y, height,
            (BuildingType)(int)(short)buildingType, buildingSize, playerID, buildingOrientation);
        this->placedBuildingID = quarryID;
        DAT_BuildingsState::instance.buildings[quarryID].uidWhenPlaced = uid;

        int index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, buildingSize);
            /* the original reuses the y parameter to hold the truncated building id */
            y = (short)quarryID;
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + baseY].addXgetTile + x + this->buildingX;
            index++;
            this->HeightLayer[tile] = (byte)height;
            this->LogicLayer[tile] = this->LogicLayer[tile] | L_BUILDING;
            this->BuildingLayer[tile] = (short)y;
            this->BuildingWasLayer[tile] = (uchar)buildingType;
            this->ChangedLayer[tile] = 2;
        } while (index < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(quarryID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(quarryID);

        /* nine attempts at a pile location, moving further from the quarry each time */
        int attempt = 1;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findQuarryPileLocation, DAT_BuildingsState::ptr)(
                playerID, x, baseY, buildingSize, 2, attempt, OpenSHC::Commands::M_MAPPER_QUARRYPILE);
            if (this->buildingPlacementFail == FALSE) {
                break;
            }
            attempt++;
        } while (attempt < 10);
        if (this->buildingPlacementFail != FALSE) {
            return;
        }

        int pileX = x + DAT_BuildingsState::instance.DAT_TempXOffset;
        int pileY = baseY + DAT_BuildingsState::instance.DAT_TempYOffset;
        buildingSize = 0;
        height = 1000;
        uint highest = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(buildingSize, 2);
            uint tileHeight = this->HeightLayer[DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + pileY].addXgetTile
                + pileX + this->buildingX];
            if (highest < tileHeight) {
                highest = tileHeight;
            }
            if (tileHeight < height) {
                height = tileHeight;
            }
            buildingSize = buildingSize + 1;
        } while ((int)buildingSize < this->constructionTileCount);
        int pileHeight = (int)(highest - height) / 2 + height;

        buildingSize = 0;
        int pileID = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(playerID, pileX, pileY,
            pileHeight, OpenSHC::Map::Buildings::BT_QUARRYSTOCKPILE, 2, playerID, buildingOrientation);
        MACRO_CALL_MEMBER(OpenSHC::AI::AIVState_Func::incrementStructureHeatMapTile, DAT_AIVState::ptr)(
            pileX, pileY);
        DAT_BuildingsState::instance.buildings[pileID].uidWhenPlaced = uid;
        DAT_BuildingsState::instance.buildings[quarryID].quarryStockpileID = (short)pileID;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(buildingSize, 2);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + pileY].addXgetTile + pileX + this->buildingX;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(tile);
            this->HeightLayer[tile] = (byte)pileHeight;
            this->LogicLayer[tile] = this->LogicLayer[tile] | L_BUILDING;
            this->BuildingLayer[tile] = (short)pileID;
            buildingSize = buildingSize + 1;
            this->BuildingWasLayer[tile] = (uchar)buildingType;
            this->ChangedLayer[tile] = 2;
        } while ((int)buildingSize < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(pileID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(pileID);

        if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID
            && DAT_GameState::instance.playerDataArray[playerID].availablePeasantsAtFire
                < DAT_BuildingsState::instance.buildings[pileID].buildingTypeBasedEmployeeCount
            && (DAT_GameState::instance.playerDataArray[playerID].populationCap
                    <= DAT_GameState::instance.playerDataArray[playerID].currentPopulation
                || DAT_GameState::instance.playerDataArray[playerID].popularity < 5000)) {
            /* "Not enough workers available to run this building." */
            MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                DAT_BottomLeftTextDisplayState::ptr)(
                1, 0x4d, 1, OpenSHC::UI::TextMessageBLLookupStructUnion(), 100, 6000);
        }
    }

}
}
