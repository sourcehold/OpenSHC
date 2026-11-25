#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/LogicHelpers/MiscDisplay.hpp"
#include "OpenSHC/Map/LogicHelpers/WallOwner.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;
    using OpenSHC::Map::LogicHelpers::MD_GATEHOUSE_RAISED;
    using OpenSHC::Map::LogicHelpers::WO_OWNER_MASK;

    // FUNCTION: STRONGHOLDCRUSADER 0x00507420
    void TileMapState::placeGatehouseSmall(int playerID, uint x, uint y, undefined4 buildingType, uint buildingSize,
        int variation, undefined4 averageHeight)
    {
        int uniqueID = DAT_GameCore::instance.uniqueGameObjectTracker;
        int index = 0;
        int buildingID = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            playerID, x, y, averageHeight, (BuildingType)(short)buildingType, buildingSize, playerID, variation);
        this->placedBuildingID = buildingID;
        DAT_BuildingsState::instance.buildings[buildingID].uidWhenPlaced = uniqueID;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                index, buildingSize);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile + x
                + this->buildingX;
            if (index < countof(DAT_BuildingsState::instance.buildings[buildingID].tileRefs)) {
                DAT_BuildingsState::instance.buildings[buildingID].tileRefs[index] = tile;
            }
            this->HeightLayer[tile] = averageHeight + 90;
            this->LogicLayer[tile] |= L_WALL_OR_GATEHOUSE;
            this->WallOwnerLayer[tile] = this->WallOwnerLayer[tile] & ~WO_OWNER_MASK | playerID - 1U;
            this->MiscDisplayLayer[tile] |= MD_GATEHOUSE_RAISED;
            this->BuildingLayer[tile] = buildingID;
            index++;
            this->BuildingWasLayer[tile] = buildingType;
            this->ChangedLayer[tile] = 2;
        } while (index < this->constructionTileCount);

        if (variation == 80) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::createClimbData,
                DAT_PathFindingState::ptr)(4, buildingID, 0, 2, 0);
        } else {
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::createClimbData,
                DAT_PathFindingState::ptr)(4, buildingID, 0, 0, 0);
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
    }

}
}
