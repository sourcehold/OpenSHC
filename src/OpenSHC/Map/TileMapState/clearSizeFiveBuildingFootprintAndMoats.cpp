#include "../TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L2_EARTH_AND_STONES;
    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_MOAT;

    // FUNCTION: STRONGHOLDCRUSADER 0x00508760
    void TileMapState::clearSizeFiveBuildingFootprintAndMoats(int x, int y)
    {
        int buildingSizeTileIndex = 0;
        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                buildingSizeTileIndex, 5);
            int const tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            int const buildingID = this->BuildingLayer[tile];
            int const variation = DAT_BuildingsState::instance.buildings[buildingID].buildingVariation;
            this->LogicLayer[tile] &= ~L_BUILDING;
            if (DAT_TerrainDefinedData::instance.DrawbridgeOrientationMapping[variation / 2][buildingSizeTileIndex]
                != 0) {
                uint const moatID
                    = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::returnOwnedMoatAtTile, this)(tile);
                if (moatID != 0) {
                    if (DAT_BuildingsState::instance.buildings[buildingID].noRubble == 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearMoatData, this)(moatID);
                        this->LogicLayer[tile] &= ~L_MOAT;
                        this->Logic2Layer[tile] |= L2_EARTH_AND_STONES;
                        this->BuildingWasLayer[tile] = 0;
                        this->HeightLayer[tile] = 8;
                    } else {
                        this->LogicLayer[tile] |= L_MOAT;
                    }
                }
            }
            if ((this->LogicLayer[tile] & L_MOAT) == 0) {
                this->Logic2Layer[tile] |= L2_EARTH_AND_STONES;
                this->BuildingWasLayer[tile] = 0;
            }
            this->BuildingLayer[tile] = 0;
            buildingSizeTileIndex++;
            this->ChangedLayer[tile] = 2;
            if (buildingSizeTileIndex >= this->constructionTileCount) {
                break;
            }
        }
    }

}
}
