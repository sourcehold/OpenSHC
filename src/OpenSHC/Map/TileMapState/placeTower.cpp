#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x00507130
    void TileMapState::placeTower(
        int playerID, uint x, uint y, undefined4 buildingType, uint size, int variation, undefined4 averageHeight)
    {
        int uniqueID = DAT_GameCore::instance.uniqueGameObjectTracker;
        int index = 0;
        int buildingID = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            playerID, x, y, averageHeight, (BuildingType)(short)buildingType, size, playerID, variation);
        this->placedBuildingID = buildingID;
        DAT_BuildingsState::instance.buildings[buildingID].uidWhenPlaced = uniqueID;
        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, size);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile + x
                + this->buildingX;
            if (index < countof(DAT_BuildingsState::instance.buildings[buildingID].tileRefs)) {
                DAT_BuildingsState::instance.buildings[buildingID].tileRefs[index] = tile;
            }
            this->HeightLayer[tile] = (byte)averageHeight;
            if (DAT_TerrainDefinedData::instance.TowerTileOffsetsBySize[size][0] == index) {
                this->LogicLayer[tile] |= L_BUILDING;
            } else if (DAT_TerrainDefinedData::instance.TowerTileOffsetsBySize[size][1] == index) {
                this->LogicLayer[tile] |= L_BUILDING;
            } else if (DAT_TerrainDefinedData::instance.TowerTileOffsetsBySize[size][2] == index) {
                this->LogicLayer[tile] |= L_BUILDING;
            } else if (DAT_TerrainDefinedData::instance.TowerTileOffsetsBySize[size][3] == index) {
                this->LogicLayer[tile] |= L_BUILDING;
            } else {
                this->LogicLayer[tile] |= L_KEEP_NON_MANOR_HOUSE;
            }
            this->BuildingLayer[tile] = (short)buildingID;
            index++;
            this->BuildingWasLayer[tile] = (uchar)buildingType;
            this->ChangedLayer[tile] = 2;
            if (index >= this->constructionTileCount) {
                break;
            }
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
    }

}
}
