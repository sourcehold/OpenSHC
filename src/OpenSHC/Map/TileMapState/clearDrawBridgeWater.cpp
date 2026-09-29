
#include "OpenSHC/Map/TileMapState.func.hpp"

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
    // FUNCTION: STRONGHOLDCRUSADER 0x00508870
    void TileMapState::clearDrawBridgeWater(int x, int y)
    {
        int buildingSizeTileIndex = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                buildingSizeTileIndex, 5);
            int targetedTile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            this->LogicLayer[targetedTile] = this->LogicLayer[targetedTile] & ~L_MOAT;
            this->HeightLayer[targetedTile] = 8;
            uint moatID = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::returnOwnedMoatAtTile, this)(targetedTile);
            if (moatID != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearMoatData, this)(moatID);
                this->LogicLayer[targetedTile] = this->LogicLayer[targetedTile] & ~L_MOAT;
                this->BuildingWasLayer[targetedTile] = 0;
            }
            this->BuildingLayer[targetedTile] = 0;
            buildingSizeTileIndex++;
            this->BuildingWasLayer[targetedTile] = 0;
            this->ChangedLayer[targetedTile] = 2;
        } while (buildingSizeTileIndex < this->constructionTileCount);
    }

}
}
