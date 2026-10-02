#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00466810
        void BuildingAndStatusMenu::MenuItemActionHandler_BuildingAndStatusMenu_OutpostSliderDelay(
            int param_1, int param_2, int* minValue, int* maxValue, int* currentValue)
        {
            short* psVar1;
            short sVar2;
            int _selectedBuildingID;
            _selectedBuildingID = DAT_BuildingsState::instance.menuSelectedBuildingID;
            switch (param_2) {
            case 1:
                *minValue = 0;
                *maxValue = 24000;
                *currentValue = (int)DAT_BuildingsState::instance.buildings[_selectedBuildingID].outpostRelatedUnk3;
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
            case 5:
                sVar2 = DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                            .outpostRelatedUnk3;
                psVar1 = &DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                              .outpostRelatedUnk3;
                if (0 < sVar2) {
                    *psVar1 = sVar2 + -1;
                }
                *currentValue = (int)*psVar1;
                return;
            case 6:
                sVar2 = DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                            .outpostRelatedUnk3;
                psVar1 = &DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                              .outpostRelatedUnk3;
                if (sVar2 < 24000) {
                    *psVar1 = sVar2 + 1;
                }
                *currentValue = (int)*psVar1;
            }
        }

    }
}
}
