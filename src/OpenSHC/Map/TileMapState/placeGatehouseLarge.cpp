
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00507560
    void TileMapState::placeGatehouseLarge(
        int param_1, uint param_2, uint param_3, undefined4 param_4, uint param_5, int param_6, undefined4 param_7)
    {
        int uniqueID = DAT_GameCore::instance.uniqueGameObjectTracker;
        int buildingSizeTileIndex = 0;
        int buildingID = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            param_1, param_2, param_3, param_7, (BuildingType)(short)param_4, param_5, param_1, param_6);
        this->placedBuildingID = buildingID;
        DAT_BuildingsState::instance.buildings[buildingID].uidWhenPlaced = uniqueID;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                buildingSizeTileIndex, param_5);
            int tileUnk = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + param_3].addXgetTile
                + param_2 + this->buildingX;
            if (buildingSizeTileIndex < 36) {
                DAT_BuildingsState::instance.buildings[buildingID].tileRefs[buildingSizeTileIndex] = tileUnk;
            }
            this->HeightLayer[tileUnk] = (char)param_7 + 0x5a;
            this->LogicLayer[tileUnk] = this->LogicLayer[tileUnk] | L_WALL_OR_GATEHOUSE;
            this->WallOwnerLayer[tileUnk] = this->WallOwnerLayer[tileUnk] & 0xf8 | (char)param_1 - 1U;
            this->MiscDisplayLayer[tileUnk] = this->MiscDisplayLayer[tileUnk] | 0x20;
            this->BuildingLayer[tileUnk] = (short)buildingID;
            buildingSizeTileIndex++;
            this->BuildingWasLayer[tileUnk] = (uchar)param_4;
            this->ChangedLayer[tileUnk] = 2;
        } while (buildingSizeTileIndex < this->constructionTileCount);

        if (param_6 == 0x50) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::createClimbData, DAT_PathFindingState::ptr)(
                3, buildingID, 0, 2, 0);
        } else {
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::createClimbData, DAT_PathFindingState::ptr)(
                3, buildingID, 0, 0, 0);
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
    }

}
}
