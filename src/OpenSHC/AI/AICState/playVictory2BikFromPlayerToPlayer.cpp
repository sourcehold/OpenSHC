#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D0C70
    void AICState::playVictory2BikFromPlayerToPlayer(int playerID, int targetPlayerID)
    {
        int iVar1;
        bool bVar2;
        if ((((DAT_GameState::instance.playerDataArray[targetPlayerID].aiType != AITA_NULL) &&
            (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1)) &&
            (iVar1 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(targetPlayerID), iVar1 != 0)) &&
            (((iVar1 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(playerID), iVar1 != 0 &&
            (DAT_GameState::instance.playerDataArray[targetPlayerID].someAiCountdown4 == 0)) &&
            (bVar2 = playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID,
             DAT_GameState::instance.playerDataArray[targetPlayerID].someAiCountdown4 = 0x30, bVar2)))) {
            MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(targetPlayerID, (int)DAT_GameState::instance.playerDataArray[targetPlayerID].aiType - 1, 0xb);
        }
    }
}
}
