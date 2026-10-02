#include "../General.func.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004BAD70
        void General::MenuItemActionHandler_General_MessageScrollbar(
            int param_1, int param_2, int* minValue, int* maxValue, int* currentValue)
        {
            switch (param_2) {
            case 1:
                *minValue = 0;
                *maxValue = DAT_MapPropertiesState::instance.total - DAT_MapPropertiesState::instance.visibleRowCount;
                *currentValue = 0;
                return;
            case 2:
            case 3:
                DAT_MapPropertiesState::instance.offset = *currentValue;
                return;
            case 4:
                *currentValue = DAT_MapPropertiesState::instance.offset;
                *maxValue = DAT_MapPropertiesState::instance.total - DAT_MapPropertiesState::instance.visibleRowCount;
                return;
            case 5:
                if (0 < DAT_MapPropertiesState::instance.offset) {
                    DAT_MapPropertiesState::instance.offset = DAT_MapPropertiesState::instance.offset + -1;
                    *currentValue = DAT_MapPropertiesState::instance.offset;
                }
                break;
            case 6:
                if (DAT_MapPropertiesState::instance.offset
                    < DAT_MapPropertiesState::instance.total - DAT_MapPropertiesState::instance.visibleRowCount) {
                    DAT_MapPropertiesState::instance.offset = DAT_MapPropertiesState::instance.offset + 1;
                }
                break;
            default:
                return;
            }
            *currentValue = DAT_MapPropertiesState::instance.offset;
        }

    }
}
}
