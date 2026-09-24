#include "OpenSHC/UI/MenuItems/Chat.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace Chat {

            // FUNCTION: STRONGHOLDCRUSADER 0x0047FFA0
            void MenuItemActionHandler_Chat_SendMessageToPlayer(int receiver, ...)
            {
                if (receiver < 0) {
                    unsigned int const playerID = -receiver;
                    DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[playerID] ^= 1;
                }
                DAT_GameSynchronyState::instance
                    .DAT_ChatMessageReceiverArray[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 1;
            }

        }
    }
}
}
