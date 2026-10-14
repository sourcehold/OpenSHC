#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D0CF0
    void AICState::playNervous1BikFromPlayer(int playerID)
    {
        if (MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(playerID) == 0) {
            return;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].someAiCountdown5 != 0) {
            return;
        }

        DAT_GameState::instance.playerDataArray[playerID].someAiCountdown5 = 48;
        MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(
            playerID, DAT_GameState::instance.playerDataArray[playerID].aiType - 1, 8);
    }
}
}
