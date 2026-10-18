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

    // FUNCTION: STRONGHOLDCRUSADER 0x00457A70
    void GameStateStructures::changePlayerOwnership(int fromPlayer, int toPlayer)
    {
        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::transferNonCourtUnitsToPlayer, DAT_UnitsState::ptr)(
            fromPlayer, toPlayer);
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::copyPlayerDataArrayValues, DAT_BuildingsState::ptr)(
            fromPlayer, toPlayer);
        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::reassignOwnerForTribesOfBehaviorType2, DAT_TribesState::ptr)(
            fromPlayer, toPlayer);
        MACRO_CALL_MEMBER(Map::TileMapState_Func::reassignWallOwnershipForPlayer, DAT_TileMapState::ptr)(
            fromPlayer, toPlayer);
        MACRO_CALL_MEMBER(Map::TileMapState_Func::setMoatOwnerForAllMatching, DAT_TileMapState::ptr)(
            fromPlayer, toPlayer);
        MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::reassignEntitiesOwner, DAT_EntityState::ptr)(
            fromPlayer, toPlayer);
    }

}
}
