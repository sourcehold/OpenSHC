#include "../ChooseNetworkServiceProvider.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047D070
        void ChooseNetworkServiceProvider::MenuItemActionHandler_ChooseNetworkServiceProvider_ModemScrollbarUnk(
            int param_1, int param_2, int* minValue, int* maxValue, int* currentValue)
        {
            switch (param_2) {
            case 1:
                *minValue = 0;
                *maxValue = DAT_GameSynchronyState::instance.modemScrollbarCount + -4;
                *currentValue = DAT_GameSynchronyState::instance.modemScrollBarOffset;
                return;
            case 2:
            case 3:
                DAT_GameSynchronyState::instance.modemScrollBarOffset = *currentValue;
                return;
            case 4:
                *currentValue = DAT_GameSynchronyState::instance.modemScrollBarOffset;
                *maxValue = DAT_GameSynchronyState::instance.modemScrollbarCount + -4;
            }
        }

    }
}
}
