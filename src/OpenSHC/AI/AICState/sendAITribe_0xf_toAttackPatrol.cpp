#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CF4F0
    void AICState::sendAITribe_0xf_toAttackPatrol(int playerID)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].aiType == AITA_NULL) {
            return;
        }

        // Bug: only tribe 15 is sent, although tribe 16 can also exist if 'AIC: AttUnitPatrolGroupsCount' is 2
        int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[15];
        if (tribeID == 0) {
            return;
        }
        if (DAT_TribesState::instance.tribes[tribeID].uid
            != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[15]) {
            return;
        }
        if (DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID == 0) {
            return;
        }

        DAT_TribesState::instance.tribes[tribeID].unitStance = Map::Units::Behavior::USE_DEFENSIVE;
        MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sendAttackingPatrolTribeToComputedDestination,
            DAT_TroopValueState::ptr)(tribeID);
    }
}
}
