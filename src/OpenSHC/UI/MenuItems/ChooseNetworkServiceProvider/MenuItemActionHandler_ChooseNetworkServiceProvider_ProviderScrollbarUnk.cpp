#include "../ChooseNetworkServiceProvider.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0047CA80
        void ChooseNetworkServiceProvider::MenuItemActionHandler_ChooseNetworkServiceProvider_ProviderScrollbarUnk(
            int param_1, int param_2, int* minValue, int* maxValue, int* currentValue)
        {
            switch (param_2) {
            case 1:
                *minValue = 0;
                *maxValue = DAT_GameSynchronyState::instance.scrollBarItemCount + -4;
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
                if (0 < DAT_GameSynchronyState::instance.scrollBarItemOffset) {
                    DAT_GameSynchronyState::instance.scrollBarItemOffset
                        = DAT_GameSynchronyState::instance.scrollBarItemOffset + -1;
                    *currentValue = DAT_GameSynchronyState::instance.scrollBarItemOffset;
                }
                break;
            case 6:
                if (DAT_GameSynchronyState::instance.scrollBarItemOffset
                    < DAT_GameSynchronyState::instance.scrollBarItemCount + -4) {
                    DAT_GameSynchronyState::instance.scrollBarItemOffset
                        = DAT_GameSynchronyState::instance.scrollBarItemOffset + 1;
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
