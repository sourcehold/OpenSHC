#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MenuItems/Chat.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace Chat {

            using OpenSHC::Commands::GameCommandType;

            // FUNCTION: STRONGHOLDCRUSADER 0x0048F850
            void MenuItemActionHandler_Chat_TauntButtons(int tauntOrMessage, ...)
            {
                DAT_GameSynchronyState::instance.DAT_ChatTauntOrMessage = tauntOrMessage;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_TAUNT_OR_CHAT);
            }

        }
    }
}
}
