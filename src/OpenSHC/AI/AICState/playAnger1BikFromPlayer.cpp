#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"

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
        int iVar2 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(playerID);
        if (iVar2 != 0) {
            int AVar1 = DAT_GameState::instance.playerDataArray[playerID].aiType;
            if ((DAT_GameState::instance.mapAndTime.playerTeams[playerID] != DAT_GameState::instance.mapAndTime.playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]) &&
                (DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID == DAT_GameSynchronyState::instance.currentPlayerSlotID)) {
                DWORD DVar3 = timeGetTime();
                if ((INT_ARRAY_00eb0af0::instance[playerID] == 0) || (599999 < DVar3 - INT_ARRAY_00eb0af0::instance[playerID])) {
                    INT_ARRAY_00eb0af0::instance[playerID] = DVar3;
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(playerID, AVar1 - 1, 5);
                }
            }
        }
    }
}
}
