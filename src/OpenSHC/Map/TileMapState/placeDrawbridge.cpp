#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_MOAT;

    using OpenSHC::Map::Buildings::BuildingType;

    /* orientation is a plain int in the original (cdq; sar at 0x514E1B); the header declares it int*.
       Every footprint tileUnk is stored in tileRefs without a bound check (0x514E78). */
    // FUNCTION: STRONGHOLDCRUSADER 0x00514DE0
    void TileMapState::placeDrawbridge(
        int playerID, uint x, uint y, undefined4 buildingType, uint total, int* orientation, undefined4 averageHeight)
    {
        int tileIndex = 0;
        int buildingID = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            playerID, x, y, averageHeight, (BuildingType)(int)(short)buildingType, total, playerID, (int)orientation);
        int rot = (int)orientation / 2;
        this->placedBuildingID = buildingID;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                tileIndex, total);
            int tileUnk = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            DAT_BuildingsState::instance.buildings[buildingID].tileRefs[tileIndex] = tileUnk;
            this->BuildingLayer[tileUnk] = (short)buildingID;
            this->BuildingWasLayer[tileUnk] = (uchar)buildingType;
            this->ChangedLayer[tileUnk] = 2;
            if (DAT_TerrainDefinedData::instance.DrawbridgeTileMoatProperty[tileIndex] != 0) {
                this->LogicLayer[tileUnk] = this->LogicLayer[tileUnk] | L_BUILDING;
            }
            if (DAT_TerrainDefinedData::instance.DrawbridgeOrientationMapping[rot][tileIndex] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::createMoatData, this)(
                    playerID, this->buildingX + x, this->buildingY + y, 1);
                this->LogicLayer[tileUnk] = this->LogicLayer[tileUnk] & ~L_MOAT;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMoatVisualStateAtTile, this)(tileUnk, 0);
                this->HeightLayer[tileUnk] = 0;
            } else {
                this->LogicLayer[tileUnk] = this->LogicLayer[tileUnk] & ~L_MOAT;
            }
            tileIndex++;
        } while (tileIndex < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
    }

}
}
