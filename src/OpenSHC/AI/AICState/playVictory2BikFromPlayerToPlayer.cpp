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

    // FUNCTION: STRONGHOLDCRUSADER 0x004D0C70
    void AICState::playVictory2BikFromPlayerToPlayer(int playerID, int targetPlayerID)
    {
        if (DAT_GameState::instance.playerDataArray[targetPlayerID].aiType == AITA_NULL) {
            return;
        }
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1) {
            return;
        }
        if (MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(targetPlayerID)
            == 0) {
            return;
        }
        if (MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(playerID) == 0) {
            return;
        }
        if (DAT_GameState::instance.playerDataArray[targetPlayerID].someAiCountdown4 != 0) {
            return;
        }

        DAT_GameState::instance.playerDataArray[targetPlayerID].someAiCountdown4 = 48;
        if (playerID != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
            return;
        }

        MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(
            targetPlayerID, DAT_GameState::instance.playerDataArray[targetPlayerID].aiType - 1, 11);
    }
}
}
