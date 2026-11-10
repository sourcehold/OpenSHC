#include "../FindingNetworkSessions.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace FindingNetworkSessions {

            // FUNCTION: STRONGHOLDCRUSADER 0x0047D330
            void MenuItemActionHandler_FindingNetworkSessions_Scrollbar(
                int unused, int scrollbarEvent, int* minValue, int* maxValue, int* currentValue)
            {
                // ten sessions fit in the list
                switch (scrollbarEvent) {
                case 1:
                    *minValue = 0;
                    *maxValue = DAT_GameSynchronyState::instance.DPLAY_SessionsCount - 10;
                    *currentValue = DAT_GameSynchronyState::instance.scrollBarItemOffset;
                    return;
                case 2:
                case 3:
                    DAT_GameSynchronyState::instance.scrollBarItemOffset = *currentValue;
                    return;
                case 4:
                    *currentValue = DAT_GameSynchronyState::instance.scrollBarItemOffset;
                    *maxValue = DAT_GameSynchronyState::instance.DPLAY_SessionsCount - 10;
                    return;
                case 5:
                    if (DAT_GameSynchronyState::instance.scrollBarItemOffset > 0) {
                        --DAT_GameSynchronyState::instance.scrollBarItemOffset;
                    }
                    *currentValue = DAT_GameSynchronyState::instance.scrollBarItemOffset;
                    return;
                case 6:
                    if (DAT_GameSynchronyState::instance.scrollBarItemOffset
                        < DAT_GameSynchronyState::instance.DPLAY_SessionsCount - 10) {
                        ++DAT_GameSynchronyState::instance.scrollBarItemOffset;
                    }
                    *currentValue = DAT_GameSynchronyState::instance.scrollBarItemOffset;
                    return;
                }
            }

        }
    }
}
}
