
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
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

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      related to setting oasis type   decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00502390
    void TileMapState::setLand(int tile, uint y, uint brushType)
    {
        int baseTile = tile;
        int brushSize = DAT_TerrainDefinedData::instance.BrushSizeArray[brushType];
        uint baseY = y;
        int index = 0;
        if (brushSize > 0) {
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(
                    1, index, &tile, (int*)&y, baseTile, baseY);
                if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) == 0
                    && (this->LogicLayer[tile] & (L_WALL_OR_GATEHOUSE | L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) == 0
                    && this->BuildingLayer[tile] == 0 && (this->LogicLayer[tile] & L_TREE) == 0
                    && ((this->LogicLayer[tile] & L_ROCKY) == 0 || this->OrganismLayer[tile] == 0)) {
                    if (this->DefaultHeightLayer[tile] < 8) {
                        this->DefaultHeightLayer[tile] = 8;
                    }
                    this->HeightLayer[tile] = this->DefaultHeightLayer[tile];
                    this->MiscDisplayLayer[tile] = this->MiscDisplayLayer[tile] & 0xffdf;
                    if ((this->LogicLayer[tile] & (L_MOAT | L_MOAT_DUG_OR_PLANNED)) != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearMoatDataAtTile, this)(tile
                                - DAT_ViewportRenderState::instance
                                    .translationMatrix[DAT_ViewportRenderState::instance
                                            .tileTranslationMatrix_YComponent[tile]]
                                    .addXgetTile,
                            DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile]);
                        this->LogicLayer[tile] = this->LogicLayer[tile] & ~(L_MOAT | L_MOAT_DUG_OR_PLANNED);
                    }
                    this->LogicLayer[tile] = this->LogicLayer[tile]
                        & (L_STOCKPILEUnk | L_PLAIN1_AND_FARM | L_BORDER | L_BORDER_EDGE | L_BUILDING
                            | L_MOAT_DUG_OR_PLANNED | L_DEFAULT_EARTH_OR_TEXTURE | L_UNKNOWN_WALL_RELATED | L_CLIMBABLE
                            | L_FARM_FIELD_WHEAT | L_FARM_FIELD_HOP | L_FARM_FIELD_APPLE | L_FARM_FIELD_DAIRY
                            | L_KEEP_NON_MANOR_HOUSE | L_MOAT);
                    this->MiscDisplayLayer[tile] = this->MiscDisplayLayer[tile] & 0xf83f;
                    this->Logic2Layer[tile] = 0;
                    if (this->HeightLayer[tile] == 80) {
                        this->Logic2Layer[tile] = L2_PLATEAU_MEDIUM;
                    } else if (this->HeightLayer[tile] == 130) {
                        this->Logic2Layer[tile] = L2_PLATEAU_HIGH;
                    }
                    this->WallOwnerLayer[tile] = 0;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                        DAT_PathFindingState::ptr)(y, tile);
                }
                index++;
            } while (index < brushSize);
        }
    }

}
}
