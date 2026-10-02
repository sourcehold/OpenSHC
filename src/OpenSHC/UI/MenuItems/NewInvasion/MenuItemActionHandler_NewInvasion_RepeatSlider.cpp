#include "../NewInvasion.func.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004B94A0
        void NewInvasion::MenuItemActionHandler_NewInvasion_RepeatSlider(
            int param_1, int param_2, int* minValue, int* maxValue, int* currentValue)
        {
            switch (param_2) {
            case 1:
                *minValue = 0;
                *maxValue = 120;
                /*
                  repeatMonths
                 */
                *currentValue
                    = DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                          .data.invasion.repeatMonths;
                return;
            case 2:
            case 3:
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .data.invasion.repeatMonths = *currentValue;
                return;
            case 4:
                *currentValue
                    = DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                          .data.invasion.repeatMonths;
                *maxValue = 120;
            }
        }

    }
}
}
