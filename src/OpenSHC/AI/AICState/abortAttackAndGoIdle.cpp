#include "../AICState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D45E0
    void AICState::abortAttackAndGoIdle(int playerID)
    {
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::removeSiegeBuildings, DAT_BuildingsState::ptr)(
            DAT_GameState::instance.playerDataArray[playerID].currentAttackWave, playerID);
        MACRO_CALL_MEMBER(AICState_Func::disbandAIPlayerSiegeUnits, this)(playerID);
        MACRO_CALL_MEMBER(AICState_Func::addEngineersToTribe, this)(playerID);
        MACRO_CALL_MEMBER(AICState_Func::aiReassignTunnelersToTribe, this)(playerID);
        DAT_GameState::instance.playerDataArray[playerID].aiPlayerState = 0;
    }

}
}
