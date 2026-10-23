
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Buildings::BuildingType;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00506AD0
    void TileMapState::updatePathLinkagesForBuilding(int buildingID)
    {
        int buildingSizeTileIndex = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                buildingSizeTileIndex, DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight);
            int y = DAT_BuildingsState::instance.buildings[buildingID].y + this->buildingY;
            int tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile
                + DAT_BuildingsState::instance.buildings[buildingID].x + this->buildingX;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                DAT_PathFindingState::ptr)(y, tile);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearMoat, this)(tile);
            buildingSizeTileIndex++;
        } while (buildingSizeTileIndex < this->constructionTileCount);

        short buildingType = DAT_BuildingsState::instance.buildings[buildingID].buildingType;
        if (buildingType == OpenSHC::Map::Buildings::BT_GATEHOUSELARGE) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToGates,
                DAT_PathFindingState::ptr)(buildingID);
            return;
        }
        if (buildingType == OpenSHC::Map::Buildings::BT_GATEHOUSESMALL) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToGates,
                DAT_PathFindingState::ptr)(buildingID);
            return;
        }
        if (buildingType == OpenSHC::Map::Buildings::BT_WOODGATE1) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToGates,
                DAT_PathFindingState::ptr)(buildingID);
            return;
        }
        if (buildingType == OpenSHC::Map::Buildings::BT_STONEKEEP) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToKeeps,
                DAT_PathFindingState::ptr)(buildingID);
            return;
        }
        if (buildingType == OpenSHC::Map::Buildings::BT_STRONGHOLD) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToKeeps,
                DAT_PathFindingState::ptr)(buildingID);
            return;
        }
        if (buildingType == OpenSHC::Map::Buildings::BT_KEEPFOUR) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToKeeps,
                DAT_PathFindingState::ptr)(buildingID);
            return;
        }
        if (buildingType == OpenSHC::Map::Buildings::BT_KEEPFIVE) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToKeeps,
                DAT_PathFindingState::ptr)(buildingID);
            return;
        }
        if (buildingType == OpenSHC::Map::Buildings::BT_SIEGETOWER_PLACED) {
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToSiegeTower,
                DAT_PathFindingState::ptr)(buildingID);
        }
    }

}
}
