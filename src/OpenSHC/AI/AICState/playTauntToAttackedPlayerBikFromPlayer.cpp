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
        if (MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(playerID) == 0) {
            return;
        }

        int bik = 0;
        int aicIndex = DAT_GameState::instance.playerDataArray[playerID].aiType - 1;
        if (DAT_GameState::instance.mapAndTime.playerTeams[playerID]
            == DAT_GameState::instance.mapAndTime.playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]) {
            bik = 23;
        }

        if (DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID
            != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
            return;
        }

        if (bik == 0) {
            bik = (SEC_RNG::instance.currentNumber2 & 3) + 1;
        }

        MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(
            playerID, aicIndex, bik);
    }
}
}
