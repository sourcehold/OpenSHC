#include "OpenSHC/Synchrony/Actions.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x004AD1E0
    void Actions::ProcessAllyDeniesRequest2(int receiverID, int requesterID)
    {
        if (DAT_GameState::instance.playerDataArray[requesterID].requestStateUnk == 2) {
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[receiverID] != -1
                && receiverID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                    MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        DE::SHCDE::TEXT_ALLIES2, 6));
                MACRO_CALL_MEMBER(GameSynchronyState_Func::addChatMessageToDisplayList, DAT_GameSynchronyState::ptr)(
                    requesterID, 0);
            }
        } else if (DAT_GameState::instance.playerDataArray[requesterID].requestStateUnk == 1) {
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[receiverID] != -1
                && receiverID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                    MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        DE::SHCDE::TEXT_ALLIES2, 5));
                MACRO_CALL_MEMBER(GameSynchronyState_Func::addChatMessageToDisplayList, DAT_GameSynchronyState::ptr)(
                    requesterID, DAT_GameState::instance.playerDataArray[requesterID].requestedAttackTargetUnk);
            }
        }
        DAT_GameState::instance.playerDataArray[requesterID].requestStateUnk = 0;
        DAT_GameState::instance.playerDataArray[receiverID].isNotNervousByEnemyTroopValue = FALSE;
    }

}
}
