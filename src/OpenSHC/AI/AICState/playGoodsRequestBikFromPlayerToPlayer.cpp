#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D0A20
    void AICState::playGoodsRequestBikFromPlayerToPlayer(int playerID, int targetPlayerID)
    {
        int iVar1 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(playerID);
        if (((iVar1 != 0) && (targetPlayerID == DAT_GameSynchronyState::instance.currentPlayerSlotID)) && (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].lordKilledByPlayerID == 0)) {
            MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(playerID, (int)DAT_GameState::instance.playerDataArray[playerID].aiType - 1, 0xe);
        }
    }
}
}
