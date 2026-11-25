#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00466810
        void BuildingAndStatusMenu::MenuItemActionHandler_BuildingAndStatusMenu_OutpostSliderDelay(
            int unused, int scrollbarEvent, int* minValue, int* maxValue, int* currentValue)
        {
            int const buildingID = DAT_BuildingsState::instance.menuSelectedBuildingID;
            switch (scrollbarEvent) {
            case 1:
                *minValue = 0;
                *maxValue = 24000;
                *currentValue = DAT_BuildingsState::instance.buildings[buildingID].outpostRelatedUnk3;
                return;
            case 2:
            case 3:
                DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                    .outpostRelatedUnk3 = (short)*currentValue;
                return;
            case 4:
                *currentValue
                    = DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                          .outpostRelatedUnk3;
                return;
            case 5: {
                // through a pointer, as the original does (direct field writes: quick_diff 0.8723 -> 0.4719)
                short const delay
                    = DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                          .outpostRelatedUnk3;
                short* const delayField
                    = &DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                           .outpostRelatedUnk3;
                if (delay > 0) {
                    *delayField = delay - 1;
                }
                *currentValue = *delayField;
                return;
            }
            case 6: {
                short const delay
                    = DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                          .outpostRelatedUnk3;
                short* const delayField
                    = &DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                           .outpostRelatedUnk3;
                if (delay < 24000) {
                    *delayField = delay + 1;
                }
                *currentValue = *delayField;
            }
            }
        }

    }
}
}
