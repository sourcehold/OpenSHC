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

    // FUNCTION: STRONGHOLDCRUSADER 0x00507BD0
    void TileMapState::placeEngineersguild(
        int param_1, uint param_2, uint param_3, undefined4 param_4, uint param_5, int param_6, undefined4 param_7)
    {
        int const uniqueID = DAT_GameCore::instance.uniqueGameObjectTracker;
        int index = 0;
        int partIndex;
        if (param_6 == 0xf) {
            partIndex = 0;
        } else {
            partIndex = param_6 / 2;
        }
        ushort const guildID = (ushort)MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            param_1, param_2, param_3, param_7, (BuildingType)(short)param_4, param_5, param_1, 0xf);
        int const buildingID = (short)guildID;
        this->placedBuildingID = buildingID;
        DAT_BuildingsState::instance.buildings[buildingID].uidWhenPlaced = uniqueID;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, param_5);
            int const tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + param_3].addXgetTile
                + this->buildingX + param_2;
            DAT_BuildingsState::instance.buildings[buildingID].tileRefs[index] = tile;
            this->HeightLayer[tile] = (byte)param_7;
            this->LogicLayer[tile] |= 0x400;
            this->BuildingLayer[tile] = guildID;
            index++;
            this->BuildingWasLayer[tile] = (uchar)param_4;
            this->ChangedLayer[tile] = 2;
        } while (index < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
        /* param_2 is the x coordinate; the original moves x and y in place */
        param_2 += DAT_TerrainDefinedData::instance.BuildingPartsOffsets[partIndex][1].x;
        param_3 += DAT_TerrainDefinedData::instance.BuildingPartsOffsets[partIndex][1].y;
        ushort const campID = (ushort)MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            param_1, param_2, param_3, param_7, OpenSHC::Map::Buildings::BT_PARADEGROUND, 5, param_1, 0xf);
        int const campBuildingID = (short)campID;
        DAT_BuildingsState::instance.buildings[campBuildingID].uidWhenPlaced = uniqueID;
        DAT_BuildingsState::instance.buildings[campBuildingID].quarryStockpileID = (short)this->placedBuildingID;
        int campIndex = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                campIndex, DAT_BuildingsState::instance.buildings[campBuildingID].widthOrHeight);
            int const tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + param_3].addXgetTile
                + this->buildingX + param_2;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(tile);
            this->HeightLayer[tile] = (byte)param_7;
            this->BuildingLayer[tile] = campID;
            campIndex++;
            this->BuildingWasLayer[tile] = (uchar)param_4;
            this->ChangedLayer[tile] = 2;
        } while (campIndex < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(campBuildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(campBuildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(8, param_2, param_3);
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupEngineersGuildParagroundPositions,
            DAT_BuildingsState::ptr)(param_1);
    }

}
}
