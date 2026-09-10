#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x00457B40
    void GameStateStructures::destroyPlayerCompletely(int playerID)
    {
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::killUnits, DAT_UnitsState::ptr)(playerID);
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuildings, DAT_BuildingsState::ptr)(
            playerID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::destroyWallsOfPlayer, DAT_TileMapState::ptr)(playerID);
        MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::destroyEntitiesPart2, DAT_EntityState::ptr)(
            playerID);
    }

}
}
