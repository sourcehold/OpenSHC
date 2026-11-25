#include "../Actions.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x004AD2F0
    void Actions::ProcessAllyRequestAttackDefense(
        int targetPlayerID, int playerID, int requestedByPlayerID, int param_4)
    {
        if (param_4 == 10) {
            DAT_GameState::instance.playerDataArray[playerID].requestStateUnk = 0;
            DAT_GameState::instance.playerDataArray[requestedByPlayerID].isNotNervousByEnemyTroopValue = FALSE;
            return;
        }
        if (param_4 == 11) {
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1) {
                if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 70));
                    MACRO_CALL_MEMBER(GameSynchronyState_Func::addChatMessageToDisplayList,
                        DAT_GameSynchronyState::ptr)(requestedByPlayerID, 0);
                }
                DAT_GameState::instance.playerDataArray[playerID].playerID_askerUnk = requestedByPlayerID;
                DAT_GameState::instance.playerDataArray[playerID].requestStateUnk = 2;
                DAT_GameState::instance.playerDataArray[requestedByPlayerID].isNotNervousByEnemyTroopValue = TRUE;
                return;
            }
            if (MACRO_CALL_MEMBER(AI::AICState_Func::determineAIPlayerHelp, DAT_AICState::ptr)(
                    playerID, requestedByPlayerID)) {
                DAT_GameState::instance.playerDataArray[playerID].playerID_askerUnk = requestedByPlayerID;
                DAT_GameState::instance.playerDataArray[playerID].requestStateUnk = 2;
            }
            return;
        }
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1) {
            if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                    MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 71));
                MACRO_CALL_MEMBER(GameSynchronyState_Func::addChatMessageToDisplayList, DAT_GameSynchronyState::ptr)(
                    requestedByPlayerID, targetPlayerID);
            }
            DAT_GameState::instance.playerDataArray[playerID].playerID_askerUnk = requestedByPlayerID;
            DAT_GameState::instance.playerDataArray[playerID].requestedAttackTargetUnk = targetPlayerID;
            DAT_GameState::instance.playerDataArray[playerID].requestStateUnk = 1;
            DAT_GameState::instance.playerDataArray[requestedByPlayerID].isNotNervousByEnemyTroopValue = FALSE;
            return;
        }
        if (MACRO_CALL_MEMBER(AI::AICState_Func::determineAIPlayerAttackRequestResponse, DAT_AICState::ptr)(
                playerID, targetPlayerID, requestedByPlayerID)) {
            DAT_GameState::instance.playerDataArray[playerID].requestStateUnk = 1;
            DAT_GameState::instance.playerDataArray[playerID].requestedAttackTargetUnk = targetPlayerID;
            DAT_GameState::instance.playerDataArray[playerID].playerID_askerUnk = requestedByPlayerID;
            MACRO_CALL_MEMBER(AI::AICState_Func::abortAttackAndGoIdle, DAT_AICState::ptr)(playerID);
        }
    }

}
}
