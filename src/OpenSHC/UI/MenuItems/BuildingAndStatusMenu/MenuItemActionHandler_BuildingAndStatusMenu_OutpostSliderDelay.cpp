#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00466810
        void BuildingAndStatusMenu::MenuItemActionHandler_BuildingAndStatusMenu_OutpostSliderDelay(
            int param_1, int param_2, int* minValue, int* maxValue, int* currentValue)
        {
            int const selectedBuildingID = DAT_BuildingsState::instance.menuSelectedBuildingID;
            switch (param_2) {
            case 1:
                *minValue = 0;
                *maxValue = 24000;
                *currentValue = (int)DAT_BuildingsState::instance.buildings[selectedBuildingID].outpostRelatedUnk3;
                return;
            case 2:
            case 3:
                DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                    .outpostRelatedUnk3 = (short)*currentValue;
                return;
            case 4:
                *currentValue
                    = (int)DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                          .outpostRelatedUnk3;
                return;
            case 5: {
                short const delay
                    = DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                          .outpostRelatedUnk3;
                short* const delayField
                    = &DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                           .outpostRelatedUnk3;
                if (0 < delay) {
                    *delayField = delay - 1;
                }
                *currentValue = (int)*delayField;
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
                *currentValue = (int)*delayField;
            }
            }
        }

    }
}
}
