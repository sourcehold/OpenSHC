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
    // FUNCTION: STRONGHOLDCRUSADER 0x004AE010
    void Actions::ProcessAllyDeniesRequest(int param_1, int param_2)
    {
        char cVar1;
        char* pcVar2;
        char* pcVar3;
        bool bVar4;
        bVar4 = param_1 == DAT_GameSynchronyState::instance.currentPlayerSlotID;
        DAT_GameState::instance.playerDataArray[param_2].requestedGoodsArray1Unk[param_1] = 0;
        DAT_GameState::instance.playerDataArray[param_2].requestedGoodsArray2Unk[param_1] = 0;
        if (bVar4) {
            /*
              added by script: "Ally Denies Request"
             */
            pcVar2 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_ALLIES2, 0);
            pcVar3 = DAT_GameSynchronyState::instance.receivedChatMessage;
            do {
                cVar1 = *pcVar2;
                *pcVar3 = cVar1;
                pcVar2 = pcVar2 + 1;
                pcVar3 = pcVar3 + 1;
            } while (cVar1 != '\0');
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                DAT_GameSynchronyState::ptr)(param_1, 0);
        }
    }

}
}
