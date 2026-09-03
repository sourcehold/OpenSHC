#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0047FFA0
void UI::MenuItemActionHandler_Chat_SendMessageToPlayer(int param_1, ...)
{
    if (param_1 < 0) {
        unsigned int param = -param_1;
        DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[param] ^= 1;
    }
    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
        = 1;
}

}
