#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D0C00
    void AICState::playAnger2BikFromPlayerToPlayer(int playerID, int targetPlayerID)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].aiType != AITA_NULL) {
            int iVar1
                = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(playerID);
            bool bVar2;
            if (((iVar1 != 0) && (DAT_GameState::instance.playerDataArray[playerID].someAiCountdown3 == 0))
                && (bVar2 = targetPlayerID == DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    DAT_GameState::instance.playerDataArray[playerID].someAiCountdown3 = 0x60, bVar2)) {
                MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(
                    playerID, (int)DAT_GameState::instance.playerDataArray[playerID].aiType - 1, 6);
            }
        }
    }
}
}
