#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0047D0E0
void UI::MenuItemActionHandler_ChooseNetworkServiceProvider_ModemTableRows(int param_1, ...)
{
    if (DAT_GameSynchronyState::instance.modemScrollBarOffset + param_1
        < DAT_GameSynchronyState::instance.modemScrollbarCount) {
        DAT_GameSynchronyState::instance.modemScrollbarIndex = param_1;
    }
}

}
