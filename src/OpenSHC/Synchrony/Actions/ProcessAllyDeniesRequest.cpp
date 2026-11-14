#include "OpenSHC/Synchrony/Actions.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x004AE010
    void Actions::ProcessAllyDeniesRequest(int fromPlayerID, int toPlayerID)
    {
        DAT_GameState::instance.playerDataArray[toPlayerID].requestedGoodsArray1Unk[fromPlayerID] = 0;
        DAT_GameState::instance.playerDataArray[toPlayerID].requestedGoodsArray2Unk[fromPlayerID] = 0;
        if (fromPlayerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
            strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_ALLIES2, 0));
            MACRO_CALL_MEMBER(GameSynchronyState_Func::addChatMessageToDisplayList, DAT_GameSynchronyState::ptr)(
                fromPlayerID, 0);
        }
    }

}
}
