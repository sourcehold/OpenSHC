#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D07C0
    void AICState::playTauntToAttackedPlayerBikFromPlayer(int playerID)
    {
        int iVar1
            = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(playerID);
        if (iVar1 != 0) {
            iVar1 = 0;
            if (DAT_GameState::instance.mapAndTime.playerTeams[playerID]
                == DAT_GameState::instance.mapAndTime
                    .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]) {
                iVar1 = 0x17;
            }
            if (DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID
                == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                if (iVar1 == 0) {
                    iVar1 = ((byte)SEC_RNG::instance.currentNumber2 & 3) + 1;
                }
                MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(
                    playerID, (int)DAT_GameState::instance.playerDataArray[playerID].aiType - 1, iVar1);
            }
        }
    }
}
}
