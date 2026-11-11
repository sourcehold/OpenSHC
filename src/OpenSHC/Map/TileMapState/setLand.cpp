#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L2_PLATEAU_HIGH;
    using OpenSHC::Map::LogicHelpers::L2_PLATEAU_MEDIUM;
    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;
    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_CLIMBABLE;
    using OpenSHC::Map::LogicHelpers::L_DEFAULT_EARTH_OR_TEXTURE;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_APPLE;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_DAIRY;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_HOP;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_WHEAT;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
    using OpenSHC::Map::LogicHelpers::L_MOAT;
    using OpenSHC::Map::LogicHelpers::L_MOAT_DUG_OR_PLANNED;
    using OpenSHC::Map::LogicHelpers::L_PLAIN1_AND_FARM;
    using OpenSHC::Map::LogicHelpers::L_ROCKY;
    using OpenSHC::Map::LogicHelpers::L_STOCKPILEUnk;
    using OpenSHC::Map::LogicHelpers::L_TREE;
    using OpenSHC::Map::LogicHelpers::L_UNKNOWN_WALL_RELATED;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x00502390
    void TileMapState::setLand(int tile, uint y, uint brushType)
    {
        int const brushSize = DAT_TerrainDefinedData::instance.BrushSizeArray[brushType];
        int const baseTile = tile;
        uint const baseY = y;
        for (int index = 0; index < brushSize; index++) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(
                1, index, &tile, (int*)&y, baseTile, baseY);
            int const brushTile = *(int volatile*)&tile;
            if ((this->LogicLayer[brushTile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                continue;
            }
            if ((this->LogicLayer[brushTile] & (L_WALL_OR_GATEHOUSE | L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0) {
                continue;
            }
            if (this->BuildingLayer[brushTile] != 0) {
                continue;
            }
            if ((this->LogicLayer[brushTile] & L_TREE) != 0) {
                continue;
            }
            if ((this->LogicLayer[brushTile] & L_ROCKY) != 0 && this->OrganismLayer[brushTile] != 0) {
                continue;
            }
            if (this->DefaultHeightLayer[brushTile] < 8) {
                this->DefaultHeightLayer[brushTile] = 8;
            }
            this->HeightLayer[brushTile] = this->DefaultHeightLayer[brushTile];
            this->MiscDisplayLayer[brushTile] &= 0xffdf;
            if ((this->LogicLayer[brushTile] & (L_MOAT | L_MOAT_DUG_OR_PLANNED)) != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearMoatDataAtTile, this)(brushTile
                        - DAT_ViewportRenderState::instance
                            .translationMatrix[DAT_ViewportRenderState::instance
                                    .tileTranslationMatrix_YComponent[brushTile]]
                            .addXgetTile,
                    DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[brushTile]);
                this->LogicLayer[brushTile] &= ~(L_MOAT | L_MOAT_DUG_OR_PLANNED);
            }
            this->LogicLayer[brushTile]
                &= (L_STOCKPILEUnk | L_PLAIN1_AND_FARM | L_BORDER | L_BORDER_EDGE | L_BUILDING | L_MOAT_DUG_OR_PLANNED
                    | L_DEFAULT_EARTH_OR_TEXTURE | L_UNKNOWN_WALL_RELATED | L_CLIMBABLE | L_FARM_FIELD_WHEAT
                    | L_FARM_FIELD_HOP | L_FARM_FIELD_APPLE | L_FARM_FIELD_DAIRY | L_KEEP_NON_MANOR_HOUSE | L_MOAT);
            this->MiscDisplayLayer[brushTile] &= 0xf83f;
            this->Logic2Layer[brushTile] = 0;
            if (DAT_TileMapState::instance.HeightLayer[brushTile] == 80) {
                this->Logic2Layer[brushTile] = L2_PLATEAU_MEDIUM;
            } else if (DAT_TileMapState::instance.HeightLayer[brushTile] == 130) {
                this->Logic2Layer[brushTile] = L2_PLATEAU_HIGH;
            }
            this->WallOwnerLayer[brushTile] = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                DAT_PathFindingState::ptr)(y, brushTile);
        }
    }

}
}
