#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_CRENEL;
    using OpenSHC::Map::LogicHelpers::L_CRENEL_VARIATIONUnk;
    using OpenSHC::Map::LogicHelpers::L_STAIRS;
    using OpenSHC::Map::LogicHelpers::L_UNKNOWN_WALL_RELATED;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    using OpenSHC::Map::LogicHelpers::L_CRENEL;
    using OpenSHC::Map::LogicHelpers::L_CRENEL_VARIATIONUnk;
    using OpenSHC::Map::LogicHelpers::L_STAIRS;
    using OpenSHC::Map::LogicHelpers::L_UNKNOWN_WALL_RELATED;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F93E0
    void TileMapState::destroyWallsOfPlayer(int playerID)
    {
        for (int tile = 0; tile < 80400; tile++) {
            if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) == 0) {
                continue;
            }
            if ((this->WallOwnerLayer[tile] & 7) + 1 != playerID) {
                continue;
            }

            MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::destroyEntitiesOnTile, DAT_EntityState::ptr)(
                tile);
            this->LogicLayer[tile] = this->LogicLayer[tile]
                & ~(L_WALL_OR_GATEHOUSE | L_CRENEL | L_STAIRS | L_UNKNOWN_WALL_RELATED | L_CRENEL_VARIATIONUnk);
            this->HeightLayer[tile] = this->DefaultHeightLayer[tile];
            this->DamageLayer[tile] = 0;
            uint y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
            DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
            DAT_TileMapState::instance.field204_0x554a30 = 1;
            int x = tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                DAT_PathFindingState::ptr)(y, tile);
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
                DAT_PathFindingState::ptr)(7, x, y);
        }
    }

}
}
