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
        int _tribeID;
        /* bug: only sends 0xf, while 0xf+1 could also be send if defined by 'AIC: AttUnitPatrolGroupsCount' */
        if ((DAT_GameState::instance.playerDataArray[playerID].aiType != AITA_NULL)
            && (_tribeID = (int)DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[0xf], _tribeID != 0)) {
            if ((DAT_TribesState::instance.tribes[_tribeID].uid
                    == DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[0xf])
                && (DAT_TribesState::instance.tribes[_tribeID].selectionTargetUnitID != 0)) {
                DAT_TribesState::instance.tribes[_tribeID].unitStance = Map::Units::Behavior::USE_DEFENSIVE;
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::sendAttackingPatrolTribeToComputedDestination,
                    DAT_TroopValueState::ptr)(_tribeID);
                return;
            }
        }
    }
}
}
