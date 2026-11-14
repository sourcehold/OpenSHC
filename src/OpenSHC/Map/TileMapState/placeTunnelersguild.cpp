#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;

    // FUNCTION: STRONGHOLDCRUSADER 0x00507E00
    void TileMapState::placeTunnelersguild(int playerID, uint x, uint y, undefined4 buildingType, uint buildingSize,
        int orientation, undefined4 averageHeight)
    {
        int const uniqueID = DAT_GameCore::instance.uniqueGameObjectTracker;
        int index = 0;
        int partIndex;
        if (orientation == 15) {
            partIndex = 0;
        } else {
            partIndex = orientation / 2;
        }
        ushort placedID = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            playerID, x, y, averageHeight, (BuildingType)(short)buildingType, buildingSize, playerID, 15);
        int buildingID = (short)placedID;
        this->placedBuildingID = buildingID;
        DAT_BuildingsState::instance.buildings[buildingID].uidWhenPlaced = uniqueID;
        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                index, buildingSize);
            int const tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            DAT_BuildingsState::instance.buildings[buildingID].tileRefs[index] = tile;
            this->HeightLayer[tile] = (byte)averageHeight;
            this->LogicLayer[tile] |= L_BUILDING;
            this->BuildingLayer[tile] = placedID;
            this->BuildingWasLayer[tile] = (uchar)buildingType;
            this->ChangedLayer[tile] = 2;
            index++;
            if (index >= this->constructionTileCount) {
                break;
            }
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);

        x += DAT_TerrainDefinedData::instance.BuildingPartsOffsets[partIndex][1].x;
        y += DAT_TerrainDefinedData::instance.BuildingPartsOffsets[partIndex][1].y;
        placedID = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            playerID, x, y, averageHeight, OpenSHC::Map::Buildings::BT_PARADEGROUND5, 5, playerID, 15);
        buildingID = (short)placedID;
        DAT_BuildingsState::instance.buildings[buildingID].uidWhenPlaced = uniqueID;
        DAT_BuildingsState::instance.buildings[buildingID].quarryStockpileID = (short)this->placedBuildingID;
        int campIndex = 0;
        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                campIndex, DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight);
            int const tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(tile);
            this->HeightLayer[tile] = (byte)averageHeight;
            this->BuildingLayer[tile] = placedID;
            this->BuildingWasLayer[tile] = (uchar)buildingType;
            this->ChangedLayer[tile] = 2;
            campIndex++;
            if (campIndex >= this->constructionTileCount) {
                break;
            }
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(8, x, y);
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupTunnelersGuildCampgroundPositions,
            DAT_BuildingsState::ptr)(playerID);
    }

}
}
