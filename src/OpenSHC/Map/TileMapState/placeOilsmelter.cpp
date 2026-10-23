
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;

    using OpenSHC::Map::Buildings::BuildingType;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00508030
    void TileMapState::placeOilsmelter(int playerID, uint x, uint y, undefined4 height, uint sizeIndex,
        int buildingTypeLike, undefined4 param_7)
    {
        int uid = DAT_GameCore::instance.uniqueGameObjectTracker;

        if (buildingTypeLike == 0xf) {
            buildingTypeLike = 0;
        } else {
            buildingTypeLike = buildingTypeLike / 2;
        }

        /* the id is kept zero-extended for the layer stores and sign-extended for the array index */
        ushort smelterID = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(playerID, x, y,
            param_7, (BuildingType)(int)(short)height, sizeIndex, playerID, 0xf);
        int buildingID = (short)smelterID;
        this->placedBuildingID = buildingID;
        DAT_BuildingsState::instance.buildings[buildingID].uidWhenPlaced = uid;

        int index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, sizeIndex);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile + this->buildingX + x;
            this->HeightLayer[tile] = (byte)param_7;
            this->LogicLayer[tile] = this->LogicLayer[tile] | L_BUILDING;
            this->BuildingLayer[tile] = smelterID;
            index++;
            this->BuildingWasLayer[tile] = (uchar)height;
            this->ChangedLayer[tile] = 2;
        } while (index < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);

        /* the campfire sits at a fixed offset from the smelter, chosen by the smelter's size */
        x = x + DAT_TerrainDefinedData::instance.field63_0x19c[buildingTypeLike].x;
        y = y + DAT_TerrainDefinedData::instance.field63_0x19c[buildingTypeLike].y;
        ushort campfire = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(playerID, x, y,
            param_7, OpenSHC::Map::Buildings::BT_CAMPFIRE, 4, playerID, 0xf);
        int campfireID = (short)campfire;
        DAT_BuildingsState::instance.buildings[campfireID].uidWhenPlaced = uid;
        DAT_BuildingsState::instance.buildings[campfireID].quarryStockpileID = (short)this->placedBuildingID;
        DAT_BuildingsState::instance.buildings[buildingID].quarryStockpileID = smelterID;

        index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                index, DAT_BuildingsState::instance.buildings[campfireID].widthOrHeight);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile + this->buildingX + x;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(tile);
            this->HeightLayer[tile] = (byte)param_7;
            this->BuildingLayer[tile] = campfire;
            index++;
            this->BuildingWasLayer[tile] = (uchar)height;
            this->ChangedLayer[tile] = 2;
        } while (index < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setTileRefsForOilSmelter, DAT_BuildingsState::ptr)(campfireID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(campfireID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(campfireID);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(8, x, y);
    }

}
}
