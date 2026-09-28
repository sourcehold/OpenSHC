
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L2_EARTH_AND_STONES;
    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_MOAT;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00508760
    void TileMapState::clearSizeFiveBuildingFootprintAndMoats(int x, int y)
    {
        int buildingSizeTileIndex = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                buildingSizeTileIndex, 5);
            int targetedTile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            short buildingID = this->BuildingLayer[targetedTile];
            short variation = DAT_BuildingsState::instance.buildings[buildingID].buildingVariation;
            this->LogicLayer[targetedTile] = this->LogicLayer[targetedTile] & ~L_BUILDING;
            if (DAT_TerrainDefinedData::instance.DrawbridgeOrientationMapping[variation / 2][buildingSizeTileIndex]
                != 0) {
                uint moatID
                    = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::returnOwnedMoatAtTile, this)(targetedTile);
                if (moatID != 0) {
                    if (DAT_BuildingsState::instance.buildings[buildingID].noRubble == 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearMoatData, this)(moatID);
                        this->LogicLayer[targetedTile] = this->LogicLayer[targetedTile] & ~L_MOAT;
                        this->Logic2Layer[targetedTile] = this->Logic2Layer[targetedTile] | L2_EARTH_AND_STONES;
                        this->BuildingWasLayer[targetedTile] = 0;
                        this->HeightLayer[targetedTile] = 8;
                    } else {
                        this->LogicLayer[targetedTile] = this->LogicLayer[targetedTile] | L_MOAT;
                    }
                }
            }
            if ((this->LogicLayer[targetedTile] & L_MOAT) == 0) {
                this->Logic2Layer[targetedTile] = this->Logic2Layer[targetedTile] | L2_EARTH_AND_STONES;
                this->BuildingWasLayer[targetedTile] = 0;
            }
            this->BuildingLayer[targetedTile] = 0;
            buildingSizeTileIndex++;
            this->ChangedLayer[targetedTile] = 2;
        } while (buildingSizeTileIndex < this->constructionTileCount);
    }

}
}
