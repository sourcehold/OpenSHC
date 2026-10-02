#include "../../Synchrony.func.hpp"
#include "../Actions.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004AD2F0
    void Actions::ProcessAllyRequestAttackDefense(
        int targetPlayerID, int playerID, int requestedByPlayerID, int param_4)
    {
        char cVar1;
        char* pcVar2;
        BOOLEnum BVar3;
        char* pcVar4;
        if (param_4 == 10) {
            DAT_GameState::instance.playerDataArray[playerID].requestStateUnk = 0;
            DAT_GameState::instance.playerDataArray[requestedByPlayerID].isNotNervousByEnemyTroopValue = 0;
            return;
        }

        if (param_4 == 11) {
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1) {
                if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    /*
                      added by script: "requests you defend him"
                     */
                    pcVar2 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x46);
                    pcVar4 = DAT_GameSynchronyState::instance.receivedChatMessage;
                    do {
                        cVar1 = *pcVar2;
                        *pcVar4 = cVar1;
                        pcVar2 = pcVar2 + 1;
                        pcVar4 = pcVar4 + 1;
                    } while (cVar1 != '\0');
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                        DAT_GameSynchronyState::ptr)(requestedByPlayerID, 0);
                }
                DAT_GameState::instance.playerDataArray[playerID].playerID_askerUnk = requestedByPlayerID;
                DAT_GameState::instance.playerDataArray[playerID].requestStateUnk = 2;
                DAT_GameState::instance.playerDataArray[requestedByPlayerID].isNotNervousByEnemyTroopValue = 1;
                return;
            }

            BVar3 = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::determineAIPlayerHelp, DAT_AICState::ptr)(
                playerID, requestedByPlayerID);
            if (BVar3 != FALSE) {
                DAT_GameState::instance.playerDataArray[playerID].playerID_askerUnk = requestedByPlayerID;
                DAT_GameState::instance.playerDataArray[playerID].requestStateUnk = 2;
            }
            return;
        }

        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1) {
            if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                /*
                  added by script: "request you attack"
                 */
                pcVar2 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x47);
                pcVar4 = DAT_GameSynchronyState::instance.receivedChatMessage;
                do {
                    cVar1 = *pcVar2;
                    *pcVar4 = cVar1;
                    pcVar2 = pcVar2 + 1;
                    pcVar4 = pcVar4 + 1;
                } while (cVar1 != '\0');
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                    DAT_GameSynchronyState::ptr)(requestedByPlayerID, targetPlayerID);
            }
            DAT_GameState::instance.playerDataArray[playerID].playerID_askerUnk = requestedByPlayerID;
            DAT_GameState::instance.playerDataArray[playerID].requestedAttackTargetUnk = targetPlayerID;
            DAT_GameState::instance.playerDataArray[playerID].requestStateUnk = 1;
            DAT_GameState::instance.playerDataArray[requestedByPlayerID].isNotNervousByEnemyTroopValue = 0;
            return;
        }

        BVar3 = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::determineAIPlayerAttackRequestResponse,
            DAT_AICState::ptr)(playerID, (undefined4)((int)(targetPlayerID)), requestedByPlayerID);
        if (BVar3 != FALSE) {
            DAT_GameState::instance.playerDataArray[playerID].requestStateUnk = 1;
            DAT_GameState::instance.playerDataArray[playerID].requestedAttackTargetUnk = targetPlayerID;
            DAT_GameState::instance.playerDataArray[playerID].playerID_askerUnk = requestedByPlayerID;
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::abortAttackAndGoIdle, DAT_AICState::ptr)(playerID);
        }
    }

}
}
