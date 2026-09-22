#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D0B10
    void AICState::playNervous2BikFromPlayer(int playerID)
    {
        if (MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(playerID) == 0) {
            return;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].nervousBikCountdown != 0) {
            return;
        }

        int aicIndex = DAT_GameState::instance.playerDataArray[playerID].aiType - 1;
        int currentPlayerID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        DAT_GameState::instance.playerDataArray[playerID].nervousBikCountdown = 48;
        if (DAT_GameState::instance.mapAndTime.playerTeams[playerID]
            == DAT_GameState::instance.mapAndTime.playerTeams[currentPlayerID]) {
            return;
        }

        MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(
            playerID, aicIndex, 9);
    }
}
}
