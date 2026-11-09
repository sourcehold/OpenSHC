#include "../ChooseNetworkServiceProvider.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047CA80
        void ChooseNetworkServiceProvider::MenuItemActionHandler_ChooseNetworkServiceProvider_ProviderScrollbarUnk(
            int unused, int scrollbarEvent, int* minValue, int* maxValue, int* currentValue)
        {
            // four providers fit in the list
            switch (scrollbarEvent) {
            case 1:
                *minValue = 0;
                *maxValue = DAT_GameSynchronyState::instance.scrollBarItemCount - 4;
                *currentValue = DAT_GameSynchronyState::instance.scrollBarItemOffset;
                return;
            case 2:
            case 3:
                DAT_GameSynchronyState::instance.scrollBarItemOffset = *currentValue;
                return;
            case 4:
                *currentValue = DAT_GameSynchronyState::instance.scrollBarItemOffset;
                return;
            case 5:
                if (DAT_GameSynchronyState::instance.scrollBarItemOffset > 0) {
                    --DAT_GameSynchronyState::instance.scrollBarItemOffset;
                    *currentValue = DAT_GameSynchronyState::instance.scrollBarItemOffset;
                    return;
                }
                break;
            case 6:
                if (DAT_GameSynchronyState::instance.scrollBarItemOffset
                    < DAT_GameSynchronyState::instance.scrollBarItemCount - 4) {
                    ++DAT_GameSynchronyState::instance.scrollBarItemOffset;
                }
                break;
            default:
                return;
            }
            *currentValue = DAT_GameSynchronyState::instance.scrollBarItemOffset;
        }

    }
}
}
