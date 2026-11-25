#include "../TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;

    // FUNCTION: STRONGHOLDCRUSADER 0x005127B0
    void TileMapState::resetAreaBasedOnLogicalLayer()
    {
        for (int tile = 0; tile < countof(this->LogicLayer); tile++) {
            if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) == 0) {
                continue;
            }

            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::useEraserBrush, this)(tile
                    - DAT_ViewportRenderState::instance
                        .translationMatrix[DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile]]
                        .addXgetTile,
                DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile], 1);
            this->GfxLayer[tile] = 0;
            this->AlphaGFXLayer[tile] = 0;
            this->ConstructionGFXLayer[tile] = 0;
            this->PillarGFXLayer[tile] = 1;
            this->WallGFXLayer[tile] = 0;
            this->FloatingLayer[tile] = 0;
            this->UnitLayer[tile] = 0;
            this->EntityLayer[tile] = 0;
            this->EntityLayerLT25[tile] = 0;
            this->BuildingLayer[tile] = 0;
            this->LogicLayer[tile] = 0;
            this->Logic2Layer[tile] = 0;
            this->ChangedLayer[tile] = 0;
            this->OrganismLayer[tile] = 0;
            this->DamageLayer[tile] = 0;
            this->MacroLayer[tile] = 0;
            this->HeightLayer[tile] = 8;
            this->DefaultHeightLayer[tile] = 8;
            this->ShowHiLayer[tile] = 0;
            this->MiscDisplayLayer[tile] = 0;
            this->LuminesenceLayer[tile] = 0;
            this->WallOwnerLayer[tile] = 0;
            this->BuildingWasLayer[tile] = 0;
            this->OccupancyLayer[tile] = 0;
            this->AIZoneLayer[tile] = 0;
            this->AIInfoLayer[tile] = 0;
            this->unitDeathHeatMap[tile] = 0;
            this->SEC_TileMap1104[tile] = 0;
            this->SEC_PathfindingCostTileMap1105[0][tile] = 0;
            this->SEC_PathfindingCostTileMap1105[1][tile] = 0;
            this->SEC_PathfindingCostTileMap1105[2][tile] = 0;
            this->SEC_PathfindingCostTileMap1105[3][tile] = 0;
            this->SEC_PathfindingCostTileMap1105[4][tile] = 0;
            this->SEC_PathfindingCostTileMap1105[5][tile] = 0;
            this->SEC_PathfindingCostTileMap1105[6][tile] = 0;
            this->SEC_PathfindingCostTileMap1105[7][tile] = 0;
            this->SEC_PathfindingCostTileMap1105[8][tile] = 0;
        }
    }

}
}
