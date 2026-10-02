#include "../../Synchrony.func.hpp"
#include "../Actions.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::DE::SHCDE::eTextSections;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004AD110
    void Actions::ProcessAllyAcceptsRequest(int param_1, int param_2)
    {
        char cVar1;
        char* pcVar2;
        char* pcVar3;
        if (DAT_GameState::instance.playerDataArray[param_2].requestStateUnk == 2) {
            if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[param_1] != -1)
                && (param_1 == DAT_GameSynchronyState::instance.currentPlayerSlotID)) {
                /*
                  added by script: "Will come you your aid"
                 */
                pcVar2 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_ALLIES2, 4);
                pcVar3 = DAT_GameSynchronyState::instance.receivedChatMessage;
                do {
                    cVar1 = *pcVar2;
                    *pcVar3 = cVar1;
                    pcVar2 = pcVar2 + 1;
                    pcVar3 = pcVar3 + 1;
                } while (cVar1 != '\0');
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                    DAT_GameSynchronyState::ptr)(param_2, 0);
            }
        } else if (DAT_GameState::instance.playerDataArray[param_2].requestStateUnk == 1) {
            if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[param_1] != -1)
                && (param_1 == DAT_GameSynchronyState::instance.currentPlayerSlotID)) {
                /*
                  added by script: "Will Attack"
                 */
                pcVar2 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_ALLIES2, 3);
                pcVar3 = DAT_GameSynchronyState::instance.receivedChatMessage;
                do {
                    cVar1 = *pcVar2;
                    *pcVar3 = cVar1;
                    pcVar2 = pcVar2 + 1;
                    pcVar3 = pcVar3 + 1;
                } while (cVar1 != '\0');
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                    DAT_GameSynchronyState::ptr)(
                    param_2, DAT_GameState::instance.playerDataArray[param_2].requestedAttackTargetUnk);
            }
        }

        DAT_GameState::instance.playerDataArray[param_2].requestStateUnk = 0;
        DAT_GameState::instance.playerDataArray[param_1].isNotNervousByEnemyTroopValue = 0;
    }

}
}
