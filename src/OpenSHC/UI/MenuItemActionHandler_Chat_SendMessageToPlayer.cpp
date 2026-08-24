#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {

/*
  WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
 */

/*
  WARNING: Enum "DPERRInt": Some values do not have unique names
 */

/*
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */

// FUNCTION: STRONGHOLDCRUSADER 0x0047FFA0
void UI::MenuItemActionHandler_Chat_SendMessageToPlayer(int param_1, ...)

{
    uint* puVar1;

    if (param_1 < 0) {
        puVar1 = (uint*)((int)DAT_GameSynchronyState::ptr + param_1 * -4 + 0x109264);
        *puVar1 = *puVar1 ^ 1;
        DAT_GameSynchronyState::instance
            .DAT_ChatMessageReceiverArray[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 1;
        return;
    }
    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
        = 1;
    return;
}

}
