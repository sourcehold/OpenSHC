#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D0D40
    void AICState::playRequestHelpBikFromPlayer(int playerID)
    {
        int iVar2 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(playerID);
        int iVar1 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        if ((iVar2 != 0) && (DAT_GameState::instance.playerDataArray[playerID].someAiCountdown6 == 0)) {
            DAT_GameState::instance.playerDataArray[playerID].someAiCountdown6 = 0x30;
            if ((DAT_GameState::instance.mapAndTime.playerTeams[playerID] == DAT_GameState::instance.mapAndTime.playerTeams[iVar1]) && (DAT_GameState::instance.playerDataArray[iVar1].lordKilledByPlayerID == 0)) {
                MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(playerID, (int)DAT_GameState::instance.playerDataArray[playerID].aiType - 1, 0x13);
            }
        }
    }
}
}
