#include "OpenSHC/AI/AICState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CD160
    void AICState::digNearestMoat(int playerID)
    {
        int iVar1;
        BOOLEnum tile;
        int tribeID = (int)DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[10];
        if ((((tribeID != 0) &&
            (DAT_TribesState::instance.tribes[tribeID].uid == DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[10])) &&
            (0 < DAT_TribesState::instance.tribes[tribeID].size)) &&
            (DAT_TribesState::instance.tribes[tribeID].percentageSomething < 0x51)) {
            iVar1 = MACRO_CALL_MEMBER(Map::TileMapState_Func::countUnfinishedMoatTilesForPlayer, DAT_TileMapState::ptr)(playerID);
            if (iVar1 < 1) {
                MACRO_CALL_MEMBER(AICState_Func::sendUnitsToKeep, this)(tribeID, playerID);
                return;
            }
            iVar1 = (int)DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID;
            tile = MACRO_CALL_MEMBER(Map::TileMapState_Func::findNearestFriendlyMoatTileForDigging, DAT_TileMapState::ptr)(playerID, iVar1, 1);
            if (-1 < (int)tile) {
                MACRO_CALL_MEMBER(Map::TileMapState_Func::setXYBasedOnMoatID, DAT_TileMapState::ptr)(tile, 1, (int)DAT_UnitsState::instance.units[iVar1].x, (int)DAT_UnitsState::instance.units[iVar1].y);
                iVar1 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::updateTribeRallyFlags, DAT_TribesState::ptr)(tribeID);
                if (iVar1 == 0) {
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(tribeID, Map::Units::UIT_DIG_MOAT, DAT_TileMapState::instance.ALG_MoatXResult, DAT_TileMapState::instance.ALG_MoatYResult, 0);
                    DAT_TribesState::instance.tribes[tribeID].unitStance = Map::Units::Behavior::USE_STAND_GROUND;
                }
            }
        }
    }
}
}
