
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00507130
    void TileMapState::placeTower(
        int param_1, uint param_2, uint param_3, undefined4 param_4, uint size, int param_6, undefined4 param_7)
    {
        int uniqueID = DAT_GameCore::instance.uniqueGameObjectTracker;
        int buildingID = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            param_1, param_2, param_3, param_7, (BuildingType)(short)param_4, size, param_1, param_6);
        this->placedBuildingID = buildingID;
        DAT_BuildingsState::instance.buildings[buildingID].uidWhenPlaced = uniqueID;
        int index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, size);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + param_3].addXgetTile
                + param_2 + this->buildingX;
            if (index < 36) {
                DAT_BuildingsState::instance.buildings[buildingID].tileRefs[index] = tile;
            }
            this->HeightLayer[tile] = (byte)param_7;
            if (DAT_TerrainDefinedData::instance.TowerTileOffsetsBySize[size][0] == index) {
                this->LogicLayer[tile] = this->LogicLayer[tile] | L_BUILDING;
            } else if (DAT_TerrainDefinedData::instance.TowerTileOffsetsBySize[size][1] == index) {
                this->LogicLayer[tile] = this->LogicLayer[tile] | L_BUILDING;
            } else if (DAT_TerrainDefinedData::instance.TowerTileOffsetsBySize[size][2] == index) {
                this->LogicLayer[tile] = this->LogicLayer[tile] | L_BUILDING;
            } else if (DAT_TerrainDefinedData::instance.TowerTileOffsetsBySize[size][3] == index) {
                this->LogicLayer[tile] = this->LogicLayer[tile] | L_BUILDING;
            } else {
                this->LogicLayer[tile] = this->LogicLayer[tile] | L_KEEP_NON_MANOR_HOUSE;
            }
            this->BuildingLayer[tile] = (short)buildingID;
            index++;
            this->BuildingWasLayer[tile] = (uchar)param_4;
            this->ChangedLayer[tile] = 2;
        } while (index < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
    }

}
}
