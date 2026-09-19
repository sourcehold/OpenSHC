#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"
#include "OpenSHC/Globals/DWORD_00eb0b18.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D0A80
    void AICState::playThanksBikFromPlayerToPlayer(int playerID, int targetPlayerID)
    {
        DWORD DVar2;
        int iVar1
            = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(playerID);
        if (iVar1 != 0) {
            iVar1 = (int)DAT_GameState::instance.playerDataArray[playerID].aiType - 1;
            DAT_GameState::instance.playerDataArray[playerID].aiRequestDelay = this->aics[iVar1].aiRequestDelay;
            if (((targetPlayerID == DAT_GameSynchronyState::instance.currentPlayerSlotID)
                    && (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .lordKilledByPlayerID
                        == 0))
                && ((DVar2 = timeGetTime(),
                    DWORD_00eb0b18::instance == 0 || (1199999 < DVar2 - DWORD_00eb0b18::instance)))) {
                DWORD_00eb0b18::instance = DVar2;
                MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(
                    playerID, iVar1, 0xf);
            }
        }
    }
}
}
