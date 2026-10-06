#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_CRENEL;
    using OpenSHC::Map::LogicHelpers::L_CRENEL_VARIATIONUnk;
    using OpenSHC::Map::LogicHelpers::L_STAIRS;
    using OpenSHC::Map::LogicHelpers::L_UNKNOWN_WALL_RELATED;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    using OpenSHC::Map::Entities::EntityType;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F9F00
    void TileMapState::spawnEraserTileEffect(undefined4 param_1, int tile)
    {
        uint y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
        int rowTile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
        this->MiscDisplayLayer[tile] = this->MiscDisplayLayer[tile] & 0xfbff;
        if (this->UnitLayer[tile] != 0) {
            return;
        }

        this->HeightLayer[tile] = this->DefaultHeightLayer[tile];
        MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::destroyEntitiesOnTile, DAT_EntityState::ptr)(tile);
        this->LogicLayer[tile] = this->LogicLayer[tile]
            & ~(L_WALL_OR_GATEHOUSE | L_CRENEL | L_BUILDING | L_STAIRS | L_UNKNOWN_WALL_RELATED
                | L_CRENEL_VARIATIONUnk);
        int microY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile] * 8;
        int microX
            = (tile
                  - DAT_ViewportRenderState::instance
                      .translationMatrix[DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile]]
                      .addXgetTile)
            * 8;
        MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(0, 0,
            0, microX, microY, DAT_TileMapState::instance.DefaultHeightLayer[tile], microX + 1, microY + 1,
            DAT_TileMapState::instance.DefaultHeightLayer[tile], (EntityType)0x1e, 0);
        this->BuildingWasLayer[tile] = 0;
        this->DamageLayer[tile] = 0;
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
            DAT_PathFindingState::ptr)(y, tile);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(9, tile - rowTile, y);
        MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::triggerMinimapRedraw, DAT_MinimapViewState::ptr)(1);
        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
        DAT_TileMapState::instance.field204_0x554a30 = 1;
    }

}
}
