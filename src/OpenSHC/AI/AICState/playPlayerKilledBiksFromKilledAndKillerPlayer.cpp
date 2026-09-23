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

    // FUNCTION: STRONGHOLDCRUSADER 0x004D08B0
    void AICState::playPlayerKilledBiksFromKilledAndKillerPlayer(int killerPlayerID, int killedPlayerID)
    {
        if (MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(killerPlayerID)
            == 0) {
            return;
        }

        if (killedPlayerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
            MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(
                killerPlayerID, DAT_GameState::instance.playerDataArray[killerPlayerID].aiType - 1, 12);
            return;
        }

        if (killerPlayerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
            MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(
                killedPlayerID, DAT_GameState::instance.playerDataArray[killedPlayerID].aiType - 1, 7);

            for (int i = 1; i < 9; i++) {
                if (DAT_GameState::instance.playerDataArray[i].aiType == AITA_NULL) {
                    continue;
                }
                if (DAT_GameState::instance.mapAndTime.playerTeams[i]
                    != DAT_GameState::instance.mapAndTime
                        .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]) {
                    continue;
                }
                if (MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(i)
                    == 0) {
                    continue;
                }
                MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(
                    i, DAT_GameState::instance.playerDataArray[i].aiType - 1, 17);
            }
            return;
        }

        if (DAT_GameState::instance.mapAndTime.playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]
            == DAT_GameState::instance.mapAndTime.playerTeams[killedPlayerID]) {
            MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(
                killedPlayerID, DAT_GameState::instance.playerDataArray[killedPlayerID].aiType - 1, 16);
            return;
        }

        if (DAT_GameState::instance.mapAndTime.playerTeams[killerPlayerID]
            == DAT_GameState::instance.mapAndTime.playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]) {
            MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(
                killedPlayerID, DAT_GameState::instance.playerDataArray[killedPlayerID].aiType - 1, 7);
            MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(
                killerPlayerID, DAT_GameState::instance.playerDataArray[killerPlayerID].aiType - 1, 18);
            return;
        }

        MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(
            killedPlayerID, DAT_GameState::instance.playerDataArray[killedPlayerID].aiType - 1, 7);
        MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(
            killerPlayerID, DAT_GameState::instance.playerDataArray[killerPlayerID].aiType - 1, 13);
    }
}
}
