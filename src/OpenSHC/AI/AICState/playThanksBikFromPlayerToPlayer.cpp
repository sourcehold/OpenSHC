#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"
#include "OpenSHC/Globals/TIME_LastThanksBikPlaybackTime.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D0A80
    void AICState::playThanksBikFromPlayerToPlayer(int playerID, int targetPlayerID)
    {
        if (MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(playerID) == 0) {
            return;
        }

        int aicIndex = DAT_GameState::instance.playerDataArray[playerID].aiType - 1;
        DAT_GameState::instance.playerDataArray[playerID].aiRequestDelay = this->aics[aicIndex].aiRequestDelay;

        if (targetPlayerID != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
            return;
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .lordKilledByPlayerID
            != 0) {
            return;
        }

        DWORD now = timeGetTime();
        if (TIME_LastThanksBikPlaybackTime::instance != 0 && now - TIME_LastThanksBikPlaybackTime::instance < 1200000) {
            return;
        }

        TIME_LastThanksBikPlaybackTime::instance = now;
        MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(
            playerID, aicIndex, 15);
    }
}
}
