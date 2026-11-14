#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x00507560
    void TileMapState::placeGatehouseLarge(int playerID, uint x, uint y, undefined4 buildingType, uint buildingSize,
        int variation, undefined4 averageHeight)
    {
        int uniqueID = DAT_GameCore::instance.uniqueGameObjectTracker;
        int index = 0;
        int buildingID = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            playerID, x, y, averageHeight, (BuildingType)(short)buildingType, buildingSize, playerID, variation);
        this->placedBuildingID = buildingID;
        DAT_BuildingsState::instance.buildings[buildingID].uidWhenPlaced = uniqueID;
        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                index, buildingSize);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile + x
                + this->buildingX;
            if (index < countof(DAT_BuildingsState::instance.buildings[buildingID].tileRefs)) {
                DAT_BuildingsState::instance.buildings[buildingID].tileRefs[index] = tile;
            }
            this->HeightLayer[tile] = (char)averageHeight + 90;
            this->LogicLayer[tile] |= L_WALL_OR_GATEHOUSE;
            this->WallOwnerLayer[tile] = this->WallOwnerLayer[tile] & 0xf8 | (char)playerID - 1U;
            this->MiscDisplayLayer[tile] |= 0x20;
            this->BuildingLayer[tile] = (short)buildingID;
            index++;
            this->BuildingWasLayer[tile] = (uchar)buildingType;
            this->ChangedLayer[tile] = 2;
            if (index >= this->constructionTileCount) {
                break;
            }
        }

        if (variation == 80) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::createClimbData,
                DAT_PathFindingState::ptr)(3, buildingID, 0, 2, 0);
        } else {
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::createClimbData,
                DAT_PathFindingState::ptr)(3, buildingID, 0, 0, 0);
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
    }

}
}
