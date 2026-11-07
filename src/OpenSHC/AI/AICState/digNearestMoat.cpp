#include "../AICState.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CD160
    void AICState::digNearestMoat(int playerID)
    {
        int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[10];
        if (tribeID == 0)
            return;
        if (DAT_TribesState::instance.tribes[tribeID].uid
            != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[10])
            return;
        if (DAT_TribesState::instance.tribes[tribeID].size <= 0)
            return;
        if (DAT_TribesState::instance.tribes[tribeID].percentageSomething > 80)
            return;

        if (MACRO_CALL_MEMBER(Map::TileMapState_Func::countUnfinishedMoatTilesForPlayer, DAT_TileMapState::ptr)(
                playerID)
            <= 0) {
            MACRO_CALL_MEMBER(AICState_Func::sendUnitsToKeep, this)(tribeID, playerID);
            return;
        }

        int targetUnitID = DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID;
        int tile = MACRO_CALL_MEMBER(Map::TileMapState_Func::findNearestFriendlyMoatTileForDigging,
            DAT_TileMapState::ptr)(playerID, targetUnitID, 1);
        if (tile <= -1)
            return;

        MACRO_CALL_MEMBER(Map::TileMapState_Func::setXYBasedOnMoatID, DAT_TileMapState::ptr)(
            tile, 1, DAT_UnitsState::instance.units[targetUnitID].x, DAT_UnitsState::instance.units[targetUnitID].y);
        if (MACRO_CALL_MEMBER(Map::Units::TribesState_Func::updateTribeRallyFlags, DAT_TribesState::ptr)(tribeID) != 0)
            return;

        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(tribeID,
            Map::Units::UIT_DIG_MOAT, DAT_TileMapState::instance.ALG_MoatXResult,
            DAT_TileMapState::instance.ALG_MoatYResult, 0);
        DAT_TribesState::instance.tribes[tribeID].unitStance = Map::Units::Behavior::USE_STAND_GROUND;
    }
}
}
