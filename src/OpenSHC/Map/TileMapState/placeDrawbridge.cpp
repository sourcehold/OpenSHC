#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_MOAT;

    // FUNCTION: STRONGHOLDCRUSADER 0x00514DE0
    void TileMapState::placeDrawbridge(
        int playerID, uint x, uint y, undefined4 buildingType, uint width, int orientation, undefined4 averageHeight)
    {
        int index = 0;
        int buildingID = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            playerID, x, y, averageHeight, (BuildingType)(short)buildingType, width, playerID, orientation);
        int rot = orientation / 2;
        this->placedBuildingID = buildingID;
        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, width);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            DAT_BuildingsState::instance.buildings[buildingID].tileRefs[index] = tile;
            this->BuildingLayer[tile] = (short)buildingID;
            this->BuildingWasLayer[tile] = (uchar)buildingType;
            this->ChangedLayer[tile] = 2;
            if (DAT_TerrainDefinedData::instance.DrawbridgeTileMoatProperty[index] != 0) {
                this->LogicLayer[tile] |= L_BUILDING;
            }
            if (DAT_TerrainDefinedData::instance.DrawbridgeOrientationMapping[rot][index] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::createMoatData, this)(
                    playerID, this->buildingX + x, this->buildingY + y, 1);
                this->LogicLayer[tile] &= ~L_MOAT;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMoatVisualStateAtTile, this)(tile, 0);
                this->HeightLayer[tile] = 0;
            } else {
                this->LogicLayer[tile] &= ~L_MOAT;
            }
            index++;
            if (index >= this->constructionTileCount) {
                break;
            }
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
    }

}
}
