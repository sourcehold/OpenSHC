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

    using DE::SHCDE::eTextSections;

    // FUNCTION: STRONGHOLDCRUSADER 0x004AD1E0
    void Actions::ProcessAllyDeniesRequest2(int param_1, int param_2)
    {
        char cVar1;
        char* pcVar2;
        char* pcVar3;
        int iVar4;
        iVar4 = DAT_GameState::instance.playerDataArray[param_2].requestStateUnk;
        if (iVar4 == 2) {
            if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[param_1] == -1)
                || (param_1 != DAT_GameSynchronyState::instance.currentPlayerSlotID))
                goto LAB_004ad285;
            /*
              added by script: "Will not come to your aid"
             */
            pcVar2 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ALLIES2, 6);
            pcVar3 = DAT_GameSynchronyState::instance.receivedChatMessage;
            do {
                cVar1 = *pcVar2;
                *pcVar3 = cVar1;
                pcVar2 = pcVar2 + 1;
                pcVar3 = pcVar3 + 1;
            } while (cVar1 != '\0');
            iVar4 = 0;
        } else {
            if (iVar4 != 1 || DAT_GameSynchronyState::instance.currentPlayerFullIDArray[param_1] == -1
                || param_1 != DAT_GameSynchronyState::instance.currentPlayerSlotID)
                goto LAB_004ad285;
            /*
              added by script: "Will not Attack"
             */
            pcVar2 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ALLIES2, 5);
            pcVar3 = DAT_GameSynchronyState::instance.receivedChatMessage;
            do {
                cVar1 = *pcVar2;
                *pcVar3 = cVar1;
                pcVar2 = pcVar2 + 1;
                pcVar3 = pcVar3 + 1;
            } while (cVar1 != '\0');
            iVar4 = DAT_GameState::instance.playerDataArray[param_2].requestedAttackTargetUnk;
        }
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList, DAT_GameSynchronyState::ptr)(
            param_2, iVar4);
    LAB_004ad285:
        DAT_GameState::instance.playerDataArray[param_2].requestStateUnk = 0;
        DAT_GameState::instance.playerDataArray[param_1].isNotNervousByEnemyTroopValue = 0;
    }

}
}
