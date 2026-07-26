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
    void AICState ::aiCommandTribe12AggressiveApproach(int param_1)

    {

        int iVar1;

        BOOLEnum BVar2;

        int tribeID;

        if ((((DAT_GameState::instance.playerDataArray[param_1].aiType != OpenSHC::AI::AIT_NULL)
                 && (tribeID = (int)DAT_GameState::instance.playerDataArray[param_1].aiTribeIDs[0xc], tribeID != 0))
                && (DAT_TribesState::instance.tribes[tribeID].uid
                    == DAT_GameState::instance.playerDataArray[param_1].aiTribeUIDs[0xc]))
            && (iVar1 = (int)DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID, iVar1 != 0)) {

            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findLinkageBasedPathOrWalkRadius,
                DAT_PathFindingState::ptr)((int)DAT_UnitsState::instance.units[iVar1].x,
                (uint)((int)((int)DAT_UnitsState::instance.units[iVar1].y)), -1, -1, 10000, FALSE);

            iVar1 = DAT_GameState::instance.playerDataArray[param_1].attackedPlayerID;

            DAT_TribesState::instance.tribes[tribeID].unitStance = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;

            BVar2 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findDestinationCostLowerThan6,
                DAT_PathFindingState::ptr)(iVar1, 200);

            if (((BVar2 != FALSE)
                    || (BVar2 = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Navigation::PathFindingState_Func::findDestinationCostLowerThan6,
                            DAT_PathFindingState::ptr)(
                            DAT_GameState::instance.playerDataArray[param_1].attackedPlayerID, (int)((int)(150))),
                        BVar2 != FALSE))
                || ((BVar2
                    = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findDestinationCostLowerThan6,
                        DAT_PathFindingState::ptr)(
                        DAT_GameState::instance.playerDataArray[param_1].attackedPlayerID, 100),
                    BVar2 != FALSE
                        || (BVar2 = MACRO_CALL_MEMBER(
                                OpenSHC::Map::Navigation::PathFindingState_Func::findDestinationCostLowerThan6,
                                DAT_PathFindingState::ptr)(
                                DAT_GameState::instance.playerDataArray[param_1].attackedPlayerID, (int)((int)(50))),
                            BVar2 != FALSE)))) {

                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction,
                    DAT_TribesState::ptr)(tribeID, (uint)((int)(DAT_PathFindingState::instance.ALG_ResultX)),
                    (uint)((int)(DAT_PathFindingState::instance.ALG_ResultY)), 0, 0,
                    OpenSHC::Map::Units::Instructions::UMSE_0);
            }
        }

        return;
    }

}
}
