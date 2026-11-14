#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_MOAT;

    // FUNCTION: STRONGHOLDCRUSADER 0x00515C80
    void TileMapState::createWaterForDrawBridge(int buildingID)
    {
        Buildings::Building const& building = DAT_BuildingsState::instance.buildings[buildingID];
        int const xPosition = building.x;
        int const variation = building.buildingVariation / 2;
        int const yPosition = building.y;
        uint const widthOrHeight = building.widthOrHeight;
        int buildingSizeTileIndex = 0;
        int const* drawbridgeMapping = DAT_TerrainDefinedData::instance.DrawbridgeOrientationMapping[variation];
        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                buildingSizeTileIndex, 5);
            int const tile
                = DAT_ViewportRenderState::instance.translationMatrix[yPosition + this->buildingY].addXgetTile
                + this->buildingX + xPosition;
            if (*drawbridgeMapping != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::createMoatData, this)(
                    DAT_BuildingsState::instance.buildings[buildingID].owner, this->buildingX + xPosition,
                    yPosition + this->buildingY, 1);
                this->LogicLayer[tile] &= ~L_MOAT;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMoatVisualStateAtTile, this)(tile, 0);
                this->HeightLayer[tile] = 0;
            }
            buildingSizeTileIndex++;
            drawbridgeMapping++;
            if (buildingSizeTileIndex >= this->constructionTileCount) {
                break;
            }
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(widthOrHeight + 6, xPosition, yPosition);
        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
    }

}
}
