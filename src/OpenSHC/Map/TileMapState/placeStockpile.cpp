#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"

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
        byte wallOwner = (char)playerID - 1;
        int uid = DAT_GameCore::instance.uniqueGameObjectTracker;
        int type = (short)buildingType;
        byte height = (char)averageHeight + 10;

        int buildingID;
        for (int part = 0; part < 4; part++) {
            buildingID = MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(playerID,
                DAT_TerrainDefinedData::instance.Stockpile_BuildingPartsOffsets[part].x + x,
                DAT_TerrainDefinedData::instance.Stockpile_BuildingPartsOffsets[part].y + y, averageHeight + 10,
                (BuildingType)type, 2, playerID, variation);
            DAT_BuildingsState::instance.buildings[buildingID].uidWhenPlaced = uid;
            DAT_BuildingsState::instance.buildings[buildingID].field_0x190 = part + 1;
            int index = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, 2);
                index++;
                int tile
                    = DAT_ViewportRenderState::instance
                          .translationMatrix[DAT_TerrainDefinedData::instance.Stockpile_BuildingPartsOffsets[part].y
                              + this->buildingY + y]
                          .addXgetTile
                    + DAT_TerrainDefinedData::instance.Stockpile_BuildingPartsOffsets[part].x + x + this->buildingX;
                this->HeightLayer[tile] = height;
                // the stockpile body itself cannot be walked over
                this->LogicLayer[tile] = this->LogicLayer[tile] | (L_STOCKPILEUnk | L_WALL_OR_GATEHOUSE | L_BUILDING);
                this->WallOwnerLayer[tile] = this->WallOwnerLayer[tile] & 0xf8 | wallOwner;
                this->BuildingLayer[tile] = (ushort)buildingID;
                this->BuildingWasLayer[tile] = (uchar)buildingType;
                this->ChangedLayer[tile] = 2;
            } while (index < this->constructionTileCount);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
        }

        this->placedBuildingID = buildingID;
        // the surrounding tiles carry the stockpile graphic but stay walkable
        for (int slot = 0; slot != 9; slot++) {
            int tile = DAT_ViewportRenderState::instance
                           .translationMatrix[DAT_TerrainDefinedData::instance.StockpilePathableOffsets[slot].y + y]
                           .addXgetTile
                + DAT_TerrainDefinedData::instance.StockpilePathableOffsets[slot].x + x;
            this->LogicLayer[tile] |= (L_STOCKPILEUnk | L_WALL_OR_GATEHOUSE);
            this->HeightLayer[tile] = height;
            this->AlphaGFXLayer[tile] = (ushort)buildingID;
            this->BuildingWasLayer[tile] = (uchar)buildingType;
            this->WallOwnerLayer[tile] = this->WallOwnerLayer[tile] & 0xf8 | wallOwner;
            this->ChangedLayer[tile] = 2;
        }

        if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID
            && DAT_BuildingsState::instance.buildings[buildingID].buildingTypeBasedEmployeeCount
                > DAT_GameState::instance.playerDataArray[playerID].availablePeasantsAtFire
            && (DAT_GameState::instance.playerDataArray[playerID].populationCap
                    <= DAT_GameState::instance.playerDataArray[playerID].currentPopulation
                || DAT_GameState::instance.playerDataArray[playerID].popularity < 5000)) {
            MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                DAT_BottomLeftTextDisplayState::ptr)(1, 0x4d, 1, 0, 100, 6000);
        }
    }

}
}
