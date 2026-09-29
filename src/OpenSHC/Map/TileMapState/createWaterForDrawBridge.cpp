
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_MOAT;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00515C80
    void TileMapState::createWaterForDrawBridge(int buildingID)
    {
        uint xPosition = DAT_BuildingsState::instance.buildings[buildingID].x;
        uint widthOrHeight = DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight;
        uint yPosition = DAT_BuildingsState::instance.buildings[buildingID].y;
        int variation = DAT_BuildingsState::instance.buildings[buildingID].buildingVariation / 2;
        int buildingSizeTileIndex = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                buildingSizeTileIndex, 5);
            uint footprintY = yPosition + this->buildingY;
            int tile = DAT_ViewportRenderState::instance.translationMatrix[footprintY].addXgetTile + this->buildingX
                + xPosition;
            if (DAT_TerrainDefinedData::instance.DrawbridgeOrientationMapping[variation][buildingSizeTileIndex] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::createMoatData, this)(
                    DAT_BuildingsState::instance.buildings[buildingID].owner, this->buildingX + xPosition, footprintY,
                    1);
                this->LogicLayer[tile] = this->LogicLayer[tile] & ~L_MOAT;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMoatVisualStateAtTile, this)(tile, 0);
                this->HeightLayer[tile] = 0;
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
