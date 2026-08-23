#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {

using OpenSHC::Commands::GameCommandType;

// FUNCTION: STRONGHOLDCRUSADER 0x0048F850
void UI::MenuItemActionHandler_Chat_TauntButtons(int param_1, va_list args)
{
    DAT_GameSynchronyState::instance.DAT_ChatTauntOrMessage = param_1;
    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
        OpenSHC::Commands::GCT_TAUNT_OR_CHAT);
}

}
