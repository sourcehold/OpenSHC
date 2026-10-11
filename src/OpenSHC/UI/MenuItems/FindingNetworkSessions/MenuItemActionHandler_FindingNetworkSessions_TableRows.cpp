#include "OpenSHC/UI/MenuItems/FindingNetworkSessions.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace FindingNetworkSessions {

            // FUNCTION: STRONGHOLDCRUSADER 0x0047D3F0
            void MenuItemActionHandler_FindingNetworkSessions_TableRows(int row, ...)
            {
                if (DAT_GameSynchronyState::instance.scrollBarItemOffset + row
                    < DAT_GameSynchronyState::instance.DPLAY_SessionsCount) {
                    DAT_GameSynchronyState::instance.scrollBarIndex = row;
                }
            }

        }
    }
}
}
