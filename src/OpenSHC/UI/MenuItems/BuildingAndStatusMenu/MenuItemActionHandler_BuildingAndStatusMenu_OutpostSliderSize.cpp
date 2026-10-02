#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00466730
        void BuildingAndStatusMenu::MenuItemActionHandler_BuildingAndStatusMenu_OutpostSliderSize(
            int param_1, int param_2, int* minValue, int* maxValue, int* currentValue)
        {
            short* psVar1;
            short sVar2;
            int iVar3;
            iVar3 = DAT_BuildingsState::instance.menuSelectedBuildingID;
            switch (param_2) {
            case 1:
                *minValue = 0;
                *maxValue = 5;
                *currentValue = (int)DAT_BuildingsState::instance.buildings[iVar3].outpostRelatedUnk2;
                return;
            case 2:
            case 3:
                DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                    .outpostRelatedUnk2 = (short)*currentValue;
                return;
            case 4:
                *currentValue
                    = (int)DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                          .outpostRelatedUnk2;
                return;
            case 5:
                sVar2 = DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                            .outpostRelatedUnk2;
                psVar1 = &DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                              .outpostRelatedUnk2;
                if (0 < sVar2) {
                    *psVar1 = sVar2 + -1;
                }
                *currentValue = (int)*psVar1;
                return;
            case 6:
                sVar2 = DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                            .outpostRelatedUnk2;
                psVar1 = &DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                              .outpostRelatedUnk2;
                if (sVar2 < 5) {
                    *psVar1 = sVar2 + 1;
                }
                *currentValue = (int)*psVar1;
            }
        }

    }
}
}
