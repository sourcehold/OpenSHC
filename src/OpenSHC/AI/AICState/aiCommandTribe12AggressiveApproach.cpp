#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::Map::Units::Behavior::UnitStanceEnum;
    using OpenSHC::Map::Units::Instructions::UnitMatchSpeedEnum;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CF2E0
    void AICState ::aiCommandTribe12AggressiveApproach(int playerID)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].aiType == OpenSHC::AI::AIT_NULL) {
            return;
        }

        int tribeID = (int)DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[0xc];

        if (tribeID == 0) {
            return;
        }

        if (DAT_TribesState::instance.tribes[tribeID].uid
            != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[0xc]) {
            return;
        }

        int targetUnitID = (int)DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID;

        if (targetUnitID == 0) {
            return;
        }

        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findLinkageBasedPathOrWalkRadius,
            DAT_PathFindingState::ptr)((int)DAT_UnitsState::instance.units[targetUnitID].x,
            (uint)((int)((int)DAT_UnitsState::instance.units[targetUnitID].y)), -1, -1, 10000, FALSE);

        int attackedPlayerID = DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID;

        DAT_TribesState::instance.tribes[tribeID].unitStance = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;

        // Try progressively smaller search costs; stop at the first one that finds a destination.
        // The later probes deliberately re-read attackedPlayerID, as the calls may update it.
        if ((MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findDestinationCostLowerThan6,
                 DAT_PathFindingState::ptr)(attackedPlayerID, 200)
                != FALSE)
            || (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findDestinationCostLowerThan6,
                    DAT_PathFindingState::ptr)(
                    DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID, 150)
                != FALSE)
            || (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findDestinationCostLowerThan6,
                    DAT_PathFindingState::ptr)(
                    DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID, 100)
                != FALSE)
            || (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findDestinationCostLowerThan6,
                    DAT_PathFindingState::ptr)(
                    DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID, 50)
                != FALSE)) {

            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                tribeID, (uint)((int)(DAT_PathFindingState::instance.ALG_ResultX)),
                (uint)((int)(DAT_PathFindingState::instance.ALG_ResultY)), 0, 0,
                OpenSHC::Map::Units::Instructions::UMSE_0);
        }

        return;
    }

}
}
