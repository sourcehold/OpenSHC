#include "../TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x00507280
    void TileMapState::upgradeTowerLogicLayer(int buildingID)
    {
        int buildingSizeTileIndex = 0;
        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                buildingSizeTileIndex, DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight);
            int tile = DAT_ViewportRenderState::instance
                           .translationMatrix[DAT_BuildingsState::instance.buildings[buildingID].y + this->buildingY]
                           .addXgetTile
                + DAT_BuildingsState::instance.buildings[buildingID].x + this->buildingX;
            this->LogicLayer[tile] &= ~L_BUILDING;
            if (DAT_TerrainDefinedData::instance
                    .TowerTileOffsetsBySize[DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight][0]
                == buildingSizeTileIndex) {
                this->LogicLayer[tile] |= L_BUILDING;
            } else if (DAT_TerrainDefinedData::instance
                           .TowerTileOffsetsBySize[DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight][1]
                == buildingSizeTileIndex) {
                this->LogicLayer[tile] |= L_BUILDING;
            } else if (DAT_TerrainDefinedData::instance
                           .TowerTileOffsetsBySize[DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight][2]
                == buildingSizeTileIndex) {
                this->LogicLayer[tile] |= L_BUILDING;
            } else if (DAT_TerrainDefinedData::instance
                           .TowerTileOffsetsBySize[DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight][3]
                == buildingSizeTileIndex) {
                this->LogicLayer[tile] |= L_BUILDING;
            } else {
                this->LogicLayer[tile] |= L_KEEP_NON_MANOR_HOUSE;
            }
            buildingSizeTileIndex++;
            if (buildingSizeTileIndex >= this->constructionTileCount) {
                break;
            }
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
    }

}
}
