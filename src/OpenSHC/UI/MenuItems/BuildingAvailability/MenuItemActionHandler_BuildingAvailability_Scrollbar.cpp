#include "../BuildingAvailability.func.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildingAvailability {

            // FUNCTION: STRONGHOLDCRUSADER 0x004BB480
            void MenuItemActionHandler_BuildingAvailability_Scrollbar(
                int param_1, int action, int* minValue, int* maxValue, int* currentValue)
            {
                // The list shows 19 rows, so the offset goes up to the row count minus 19.
                switch (action) {
                case 1: // set-up: range and position
                    *minValue = 0;
                    *maxValue = DAT_MapPropertiesState::instance.buildingAvailabilityRowCount - 19;
                    *currentValue = DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset;
                    return;
                case 2: // the thumb moved: take its position
                case 3:
                    DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset = *currentValue;
                    return;
                case 4: // refresh: position and range end
                    *currentValue = DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset;
                    *maxValue = DAT_MapPropertiesState::instance.buildingAvailabilityRowCount - 19;
                    return;
                case 5: // one row up
                    // Stores and returns here rather than through the shared store below, as the original does.
                    if (DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset > 0) {
                        --DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset;
                        *currentValue = DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset;
                        return;
                    }
                    break;
                case 6: // one row down
                    if (DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset
                        < (int)DAT_MapPropertiesState::instance.buildingAvailabilityRowCount - 19) {
                        ++DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset;
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
}
