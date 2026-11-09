#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00466730
        void BuildingAndStatusMenu::MenuItemActionHandler_BuildingAndStatusMenu_OutpostSliderSize(
            int unused, int scrollbarEvent, int* minValue, int* maxValue, int* currentValue)
        {
            int const buildingID = DAT_BuildingsState::instance.menuSelectedBuildingID;
            switch (scrollbarEvent) {
            case 1:
                *minValue = 0;
                *maxValue = 5;
                *currentValue = DAT_BuildingsState::instance.buildings[buildingID].outpostRelatedUnk2;
                return;
            case 2:
            case 3:
                DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                    .outpostRelatedUnk2 = (short)*currentValue;
                return;
            case 4:
                *currentValue
                    = DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                          .outpostRelatedUnk2;
                return;
            case 5: {
                short const oldSize
                    = DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                          .outpostRelatedUnk2;
                short* const sizeField
                    = &DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                           .outpostRelatedUnk2;
                if (0 < oldSize) {
                    *sizeField = oldSize - 1;
                }
                *currentValue = *sizeField;
                return;
            }
            case 6: {
                short const oldSize
                    = DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                          .outpostRelatedUnk2;
                short* const sizeField
                    = &DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                           .outpostRelatedUnk2;
                if (oldSize < 5) {
                    *sizeField = oldSize + 1;
                }
                *currentValue = *sizeField;
            }
            }
        }

    }
}
}
