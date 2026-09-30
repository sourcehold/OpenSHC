#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Game {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00457A70
    void GameStateStructures::changePlayerOwnership(int fromPlayer, int toPlayer)
    {
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::transferNonCourtUnitsToPlayer, DAT_UnitsState::ptr)(
            fromPlayer, toPlayer);
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::copyPlayerDataArrayValues,
            DAT_BuildingsState::ptr)(fromPlayer, toPlayer);
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::reassignOwnerForTribesOfBehaviorType2,
            DAT_TribesState::ptr)(fromPlayer, toPlayer);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::reassignWallOwnershipForPlayer, DAT_TileMapState::ptr)(
            fromPlayer, toPlayer);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMoatOwnerForAllMatching, DAT_TileMapState::ptr)(
            fromPlayer, toPlayer);
        MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::reassignEntitiesOwner, DAT_EntityState::ptr)(
            fromPlayer, toPlayer);
    }
}
}
