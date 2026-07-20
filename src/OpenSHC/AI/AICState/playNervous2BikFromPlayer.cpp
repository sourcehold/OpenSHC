#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D0B10
    void AICState::playNervous2BikFromPlayer(int playerID)
    {
        int iVar3 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(playerID);
        int iVar2 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        if ((iVar3 != 0) && (DAT_GameState::instance.playerDataArray[playerID].nervousBikCountdown == 0)) {
            int AVar1 = DAT_GameState::instance.playerDataArray[playerID].aiType;
            DAT_GameState::instance.playerDataArray[playerID].nervousBikCountdown = 48;
            if (DAT_GameState::instance.mapAndTime.playerTeams[playerID] != DAT_GameState::instance.mapAndTime.playerTeams[iVar2]) {
                MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(playerID, AVar1 - 1, 9);
            }
        }
    }
}
}
