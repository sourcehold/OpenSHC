
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00514DE0
    void TileMapState::placeDrawbridge(
        int playerID, uint x, uint y, undefined4 buildingType, uint width, int* orientation, undefined4 averageHeight)
    {
        int buildingID;
        int _tileIndex;
        Building* _pTileRef;
        int tile;
        _tileIndex = 0;
        buildingID = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData,
            DAT_BuildingsState::ptr)(playerID, x, y, (undefined4)((int)(averageHeight)),
            (BuildingType)((int)((int)(short)buildingType)), width, playerID, (int)((int)(orientation)));
        orientation = DAT_TerrainDefinedData::instance.DrawbridgeOrientationMapping[(int)orientation / 2];
        _pTileRef = &DAT_BuildingsState::instance.buildings[buildingID];
        this->placedBuildingID = buildingID;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                _tileIndex, (int)((int)(width)));
            /*
              fixme: repurposed parameter
             */
            averageHeight._0_2_ = (short)buildingID;
            tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            _pTileRef->tileRefs[0] = tile;
            this->BuildingLayer[tile] = (short)averageHeight;
            this->BuildingWasLayer[tile] = (uchar)buildingType;
            this->ChangedLayer[tile] = 2;
            if (DAT_TerrainDefinedData::instance.DrawbridgeTileMoatProperty[_tileIndex] != 0) {
                this->LogicLayer[tile] = this->LogicLayer[tile] | 1024;
            }
            if (*orientation == 0) {
                this->LogicLayer[tile] = this->LogicLayer[tile] & ~(L_MOAT);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::createMoatData, this)(
                    playerID, this->buildingX + x, this->buildingY + y, 1);
                this->LogicLayer[tile] = this->LogicLayer[tile] & ~(L_MOAT);
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMoatVisualStateAtTile, this)(tile, 0);
                this->HeightLayer[tile] = 0;
            }
            orientation = orientation + 1;
            _tileIndex = _tileIndex + 1;
            _pTileRef = &_pTileRef->tileRefs[1];
        } while (_tileIndex < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
        return;
    }

}
}
