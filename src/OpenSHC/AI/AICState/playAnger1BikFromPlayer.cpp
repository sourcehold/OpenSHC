#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00eb0af0.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D0830
    void AICState::playAnger1BikFromPlayer(int playerID)
    {
        if (MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(playerID) == 0) {
            return;
        }

        int aicIndex = DAT_GameState::instance.playerDataArray[playerID].aiType - 1;
        if (DAT_GameState::instance.mapAndTime.playerTeams[playerID]
            == DAT_GameState::instance.mapAndTime.playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]) {
            return;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID
            != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
            return;
        }

        DWORD now = timeGetTime();
        if (INT_ARRAY_00eb0af0::instance[playerID] != 0 && now - INT_ARRAY_00eb0af0::instance[playerID] < 600000) {
            return;
        }

        INT_ARRAY_00eb0af0::instance[playerID] = now;
        MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(
            playerID, aicIndex, 5);
    }
}
}
