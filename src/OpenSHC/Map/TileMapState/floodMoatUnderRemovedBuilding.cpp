#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_MOAT;

    // FUNCTION: STRONGHOLDCRUSADER 0x00508910
    void TileMapState::floodMoatUnderRemovedBuilding(int buildingID)
    {
        uint yPosition = DAT_BuildingsState::instance.buildings[buildingID].y;
        uint xPosition = DAT_BuildingsState::instance.buildings[buildingID].x;
        uint widthOrHeight = DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight;
        int variation = DAT_BuildingsState::instance.buildings[buildingID].buildingVariation / 2;
        int buildingSizeTileIndex = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                buildingSizeTileIndex, 5);
            int targetedTile
                = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + yPosition].addXgetTile
                + this->buildingX + xPosition;
            if (DAT_TerrainDefinedData::instance.DrawbridgeOrientationMapping[variation][buildingSizeTileIndex] != 0) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::returnOwnedMoatAtTile, this)(targetedTile)
                    != 0) {
                    this->LogicLayer[targetedTile] |= L_MOAT;
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMoatVisualStateAtTile, this)(targetedTile, 2);
                }
            }
            buildingSizeTileIndex++;
        } while (buildingSizeTileIndex < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(widthOrHeight + 6, xPosition, yPosition);
        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
    }

}
}
