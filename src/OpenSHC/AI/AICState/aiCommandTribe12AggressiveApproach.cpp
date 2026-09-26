#include "../AICState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CF2E0
    void AICState::aiCommandTribe12AggressiveApproach(int playerID)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].aiType == OpenSHC::AI::AIT_NULL)
            return;
        int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[12];
        if (tribeID == 0)
            return;
        if (DAT_TribesState::instance.tribes[tribeID].uid
            != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[12])
            return;
        int targetUnitID = DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID;
        if (targetUnitID == 0)
            return;

        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findLinkageBasedPathOrWalkRadius,
            DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[targetUnitID].x,
            DAT_UnitsState::instance.units[targetUnitID].y, -1, -1, 10000, FALSE);
        int attackedPlayerID = DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID;
        DAT_TribesState::instance.tribes[tribeID].unitStance = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;

        if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findDestinationCostLowerThan6,
                DAT_PathFindingState::ptr)(attackedPlayerID, 200)
                == FALSE
            && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findDestinationCostLowerThan6,
                   DAT_PathFindingState::ptr)(DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID, 150)
                == FALSE
            && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findDestinationCostLowerThan6,
                   DAT_PathFindingState::ptr)(DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID, 100)
                == FALSE
            && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findDestinationCostLowerThan6,
                   DAT_PathFindingState::ptr)(DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID, 50)
                == FALSE)
            return;

        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
            tribeID, DAT_PathFindingState::instance.ALG_ResultX, DAT_PathFindingState::instance.ALG_ResultY, 0, 0,
            OpenSHC::Map::Units::Instructions::UMSE_0);
    }

}
}
