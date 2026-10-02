#include "../BuildingAvailability.func.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004BB480
        void BuildingAvailability::MenuItemActionHandler_BuildingAvailability_Scrollbar(
            int param_1, int param_2, int* minValue, int* maxValue, int* currentValue)
        {
            switch (param_2) {
            case 1:
                *minValue = 0;
                *maxValue = DAT_MapPropertiesState::instance.field8_0x224 + -0x13;
                *currentValue = DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset;
                return;
            case 2:
            case 3:
                DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset = *currentValue;
                return;
            case 4:
                *currentValue = DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset;
                *maxValue = DAT_MapPropertiesState::instance.field8_0x224 + -0x13;
                return;
            case 5:
                if (0 < DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset) {
                    DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset
                        = DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset + -1;
                    *currentValue = DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset;
                }
                break;
            case 6:
                if (DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset
                    < DAT_MapPropertiesState::instance.field8_0x224 + -0x13) {
                    DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset
                        = DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset + 1;
                }
                break;
            default:
                return;
            }
            *currentValue = DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset;
        }

    }
}
}
