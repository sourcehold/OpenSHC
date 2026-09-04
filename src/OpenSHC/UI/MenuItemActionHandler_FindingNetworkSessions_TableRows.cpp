#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0047D3F0
void UI::MenuItemActionHandler_FindingNetworkSessions_TableRows(int param_1, ...)
{
    if (DAT_GameSynchronyState::instance.scrollBarItemOffset + param_1
        < DAT_GameSynchronyState::instance.DPLAY_SessionsCount) {
        DAT_GameSynchronyState::instance.scrollBarIndex = param_1;
    }
}

}
