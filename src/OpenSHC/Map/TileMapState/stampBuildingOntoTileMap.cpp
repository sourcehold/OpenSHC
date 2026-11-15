#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;

    // FUNCTION: STRONGHOLDCRUSADER 0x00507060
    void TileMapState::stampBuildingOntoTileMap(int playerID, uint x, uint y, undefined4 buildingType,
        undefined4 variation, uint buildingSize, undefined4 orientation, undefined4 averageHeight)
    {
        int index = 0;
        int const buildingID = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            playerID, x, y, averageHeight, (BuildingType)(short)buildingType, buildingSize, playerID, (short)variation);
        this->placedBuildingID = buildingID;
        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                index, buildingSize);
            int const tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            if (index < countof(DAT_BuildingsState::instance.buildings[buildingID].tileRefs)) {
                DAT_BuildingsState::instance.buildings[buildingID].tileRefs[index] = tile;
            }
            this->HeightLayer[tile] = (byte)averageHeight;
            this->LogicLayer[tile] |= L_BUILDING;
            this->BuildingLayer[tile] = (short)buildingID;
            index++;
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
