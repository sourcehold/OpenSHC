#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_CRENEL;
    using OpenSHC::Map::LogicHelpers::L_CRENEL_VARIATIONUnk;
    using OpenSHC::Map::LogicHelpers::L_STAIRS;
    using OpenSHC::Map::LogicHelpers::L_UNKNOWN_WALL_RELATED;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F81D0
    void TileMapState::resetTileToDefaultState(int tile, uint x, uint y)
    {
        this->LogicLayer[tile]
            &= ~(L_WALL_OR_GATEHOUSE | L_CRENEL | L_STAIRS | L_UNKNOWN_WALL_RELATED | L_CRENEL_VARIATIONUnk);
        this->HeightLayer[tile] = this->DefaultHeightLayer[tile];
        MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::destroyEntitiesOnTile, DAT_EntityState::ptr)(tile);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(5, x, y);
    }

}
}
