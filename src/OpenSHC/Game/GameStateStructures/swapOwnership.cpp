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

    // FUNCTION: STRONGHOLDCRUSADER 0x00457AD0
    void GameStateStructures::swapOwnership(int playerID_1, int playerID_2)
    {
        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::makeCourtMemberUnitsDisappearAndSwapAllOtherUnitsOwnership,
            DAT_UnitsState::ptr)(playerID_1, playerID_2);
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::swapOwnersOfCastle, DAT_BuildingsState::ptr)(
            playerID_1, playerID_2);
        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::swapTribeOwnership, DAT_TribesState::ptr)(
            playerID_1, playerID_2);
        MACRO_CALL_MEMBER(Map::TileMapState_Func::swapWallOwnership, DAT_TileMapState::ptr)(playerID_1, playerID_2);
        MACRO_CALL_MEMBER(Map::TileMapState_Func::swapMoatOwnership, DAT_TileMapState::ptr)(playerID_1, playerID_2);
        MACRO_CALL_MEMBER(Map::TileMapState_Func::swapPitchOwnership, DAT_TileMapState::ptr)(playerID_1, playerID_2);
        MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::swapEntityOwnership, DAT_EntityState::ptr)(
            playerID_1, playerID_2);
    }

}
}
