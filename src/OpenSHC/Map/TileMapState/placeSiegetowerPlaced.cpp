#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;

    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x00506D40
    void TileMapState::placeSiegetowerPlaced(
        int param_1, uint param_2, uint param_3, short buildingType, uint param_5, int param_6, undefined4 param_7)
    {
        int buildingSizeTileIndex = 0;
        int buildingID = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            param_1, param_2, param_3, param_7, (BuildingType)buildingType, param_5, param_1, param_6);
        this->placedBuildingID = buildingID;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                buildingSizeTileIndex, param_5);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + param_3].addXgetTile
                + this->buildingX + param_2;
            if (buildingSizeTileIndex < 36) {
                DAT_BuildingsState::instance.buildings[buildingID].tileRefs[buildingSizeTileIndex] = tile;
            }
            this->HeightLayer[tile] = (byte)param_7;
            this->LogicLayer[tile] |= L_KEEP_NON_MANOR_HOUSE;
            this->BuildingLayer[tile] = (short)buildingID;
            buildingSizeTileIndex++;
            this->BuildingWasLayer[tile] = (uchar)buildingType;
            this->ChangedLayer[tile] = 2;
        } while (buildingSizeTileIndex < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
    }

}
}
