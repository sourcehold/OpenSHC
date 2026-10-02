#include "../RankingGames.func.hpp"

#include "OpenSHC/Globals/DAT_00eb9b60.hpp"
#include "OpenSHC/Globals/DAT_00ed3120.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004D9B30
        void RankingGames::MenuItemActionHandler_RankingGames_Scrollbar(
            int param_1, int param_2, int* minValue, int* maxValue, int* currentValue)
        {
            int iVar1;
            switch (param_2) {
            case 1:
                *minValue = 0;
                *maxValue = 1;
                *currentValue = 0;
                return;
            case 2:
            case 3:
                if (*currentValue != DAT_00ed3120::instance) {
                    DAT_00ed3120::instance = *currentValue;
                }
                break;
            case 4:
                *minValue = 0;
                iVar1 = DAT_00eb9b60::instance + -8;
                *maxValue = iVar1;
                if (iVar1 < 0) {
                    *maxValue = 0;
                }
                if (*currentValue != DAT_00ed3120::instance) {
                    *currentValue = DAT_00ed3120::instance;
                }
                break;
            case 5:
                if (0 < DAT_00ed3120::instance) {
                    DAT_00ed3120::instance = DAT_00ed3120::instance + -1;
                    *currentValue = DAT_00ed3120::instance;
                }
                goto LAB_004d9be7;
            case 6:
                if (DAT_00ed3120::instance < DAT_00eb9b60::instance + -8) {
                    DAT_00ed3120::instance = DAT_00ed3120::instance + 1;
                }
            LAB_004d9be7:
                *currentValue = DAT_00ed3120::instance;
                break;
            case 7:
                *currentValue = 6;
            }
        }

    }
}
}
