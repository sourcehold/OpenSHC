#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D08B0
    void AICState::playPlayerKilledBiksFromKilledAndKillerPlayer(int killerPlayerID, int killedPlayerID)
    {
        int iVar1 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(killerPlayerID);
        if (iVar1 != 0) {
            if (killedPlayerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                iVar1 = 0xc;
            }
            else {
                if (killerPlayerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(killedPlayerID, (int)DAT_GameState::instance.playerDataArray[killedPlayerID].aiType - 1, 7);
                    int i = 1;
                    do {
                        if ((DAT_GameState::instance.playerDataArray[i].aiType != AITA_NULL) &&
                            (DAT_GameState::instance.mapAndTime.playerTeams[i] == DAT_GameState::instance.mapAndTime.playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID])) {
                            int iVar2 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(i);
                            if (iVar2 != 0) {
                                MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(i, (int)DAT_GameState::instance.playerDataArray[i].aiType - 1, 0x11);
                            }
                        }
                        i = i + 1;
                    } while (i < 9);
                    return;
                }
                iVar1 = DAT_GameState::instance.mapAndTime.playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID];
                if (iVar1 == DAT_GameState::instance.mapAndTime.playerTeams[killedPlayerID]) {
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(killedPlayerID, (int)DAT_GameState::instance.playerDataArray[killedPlayerID].aiType - 1, 0x10);
                    return;
                }
                if (DAT_GameState::instance.mapAndTime.playerTeams[killerPlayerID] == iVar1) {
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(killedPlayerID, (int)DAT_GameState::instance.playerDataArray[killedPlayerID].aiType - 1, 7);
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(killerPlayerID, (int)DAT_GameState::instance.playerDataArray[killerPlayerID].aiType - 1, 0x12);
                    return;
                }
                MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(killedPlayerID, (int)DAT_GameState::instance.playerDataArray[killedPlayerID].aiType - 1, 7);
                iVar1 = 0xd;
            }
            MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(killerPlayerID, (int)DAT_GameState::instance.playerDataArray[killerPlayerID].aiType - 1, iVar1);
        }
    }
}
}
