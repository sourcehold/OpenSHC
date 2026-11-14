#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_STOCKPILEUnk;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x00508540
    void TileMapState::placeStockpile(int playerID, int x, int y, undefined4 buildingType,
        undefined4 unusedBuildingSize, int variation, int averageHeight)
    {
        int const uid = DAT_GameCore::instance.uniqueGameObjectTracker;

        int buildingID;
        for (int part = 0; part < countof(DAT_TerrainDefinedData::instance.Stockpile_BuildingPartsOffsets); part++) {
            buildingID = MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(playerID,
                DAT_TerrainDefinedData::instance.Stockpile_BuildingPartsOffsets[part].x + x,
                DAT_TerrainDefinedData::instance.Stockpile_BuildingPartsOffsets[part].y + y, averageHeight + 10,
                (BuildingType)(short)buildingType, 2, playerID, variation);
            DAT_BuildingsState::instance.buildings[buildingID].uidWhenPlaced = uid;
            DAT_BuildingsState::instance.buildings[buildingID].field_0x190 = part + 1;
            int index = 0;
            while (true) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, 2);
                int tile
                    = DAT_ViewportRenderState::instance
                          .translationMatrix[DAT_TerrainDefinedData::instance.Stockpile_BuildingPartsOffsets[part].y
                              + this->buildingY + y]
                          .addXgetTile
                    + DAT_TerrainDefinedData::instance.Stockpile_BuildingPartsOffsets[part].x + x + this->buildingX;
                this->HeightLayer[tile] = (byte)(averageHeight + 10);
                // the stockpile body itself cannot be walked over
                this->LogicLayer[tile] |= L_STOCKPILEUnk | L_WALL_OR_GATEHOUSE | L_BUILDING;
                this->WallOwnerLayer[tile] = this->WallOwnerLayer[tile] & 0xf8 | (byte)(playerID - 1);
                this->BuildingLayer[tile] = (ushort)buildingID;
                this->BuildingWasLayer[tile] = (uchar)buildingType;
                this->ChangedLayer[tile] = 2;
                index++;
                if (index >= this->constructionTileCount) {
                    break;
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
        }

        this->placedBuildingID = buildingID;
        // the surrounding tiles carry the stockpile graphic but stay walkable
        for (int slot = 0; slot != countof(DAT_TerrainDefinedData::instance.StockpilePathableOffsets); slot++) {
            int tile = DAT_ViewportRenderState::instance
                           .translationMatrix[DAT_TerrainDefinedData::instance.StockpilePathableOffsets[slot].y + y]
                           .addXgetTile
                + DAT_TerrainDefinedData::instance.StockpilePathableOffsets[slot].x + x;
            this->LogicLayer[tile] |= L_STOCKPILEUnk | L_WALL_OR_GATEHOUSE;
            this->HeightLayer[tile] = (byte)(averageHeight + 10);
            this->AlphaGFXLayer[tile] = (ushort)buildingID;
            this->BuildingWasLayer[tile] = (uchar)buildingType;
            this->WallOwnerLayer[tile] = this->WallOwnerLayer[tile] & 0xf8 | (byte)(playerID - 1);
            this->ChangedLayer[tile] = 2;
        }

        if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID
            && DAT_BuildingsState::instance.buildings[buildingID].buildingTypeBasedEmployeeCount
                > DAT_GameState::instance.playerDataArray[playerID].availablePeasantsAtFire
            && (DAT_GameState::instance.playerDataArray[playerID].populationCap
                    <= DAT_GameState::instance.playerDataArray[playerID].currentPopulation
                || DAT_GameState::instance.playerDataArray[playerID].popularity < 5000)) {
            MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                DAT_BottomLeftTextDisplayState::ptr)(1, OpenSHC::DE::SHCDE::TEXT_PANEL_FEEDBACK, 1, 0, 100, 6000);
        }
    }

}
}
