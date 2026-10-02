#include "../EditScenario.func.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004B8A50
        void EditScenario::MenuItemActionHandler_EditScenario_Scrollbar(
            int param_1, int param_2, int* minValue, int* maxValue, int* currentValue)
        {
            switch (param_2) {
            case 1:
                *minValue = 0;
                *maxValue = DAT_MapPropertiesState::instance.eventsCount + -0x14;
                *currentValue = 0;
                return;
            case 2:
            case 3:
                if (*currentValue < 0) {
                    *currentValue = 0;
                }
                DAT_MapPropertiesState::instance.field47_0x1355c = *currentValue;
                return;
            case 4:
                *currentValue = DAT_MapPropertiesState::instance.field47_0x1355c;
                *maxValue = DAT_MapPropertiesState::instance.eventsCount + -0x14;
                return;
            case 5:
                if (0 < DAT_MapPropertiesState::instance.field47_0x1355c) {
                    DAT_MapPropertiesState::instance.field47_0x1355c
                        = DAT_MapPropertiesState::instance.field47_0x1355c + -1;
                    *currentValue = DAT_MapPropertiesState::instance.field47_0x1355c;
                }
                break;
            case 6:
                if (DAT_MapPropertiesState::instance.field47_0x1355c
                    < DAT_MapPropertiesState::instance.eventsCount + -0x14) {
                    DAT_MapPropertiesState::instance.field47_0x1355c
                        = DAT_MapPropertiesState::instance.field47_0x1355c + 1;
                }
                break;
            default:
                return;
            }
            *currentValue = DAT_MapPropertiesState::instance.field47_0x1355c;
        }

    }
}
}
