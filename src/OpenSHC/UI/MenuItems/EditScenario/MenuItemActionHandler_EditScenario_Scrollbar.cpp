#include "../EditScenario.func.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004B8A50
        void EditScenario::MenuItemActionHandler_EditScenario_Scrollbar(
            int unused, int scrollbarEvent, int* minValue, int* maxValue, int* currentValue)
        {
            switch (scrollbarEvent) {
            case 1:
                *minValue = 0;
                *maxValue = DAT_MapPropertiesState::instance.eventsCount - 20;
                *currentValue = 0;
                return;
            case 2:
            case 3:
                if (*currentValue < 0) {
                    *currentValue = 0;
                }
                DAT_MapPropertiesState::instance.eventListScrollOffset = *currentValue;
                return;
            case 4:
                *currentValue = DAT_MapPropertiesState::instance.eventListScrollOffset;
                *maxValue = DAT_MapPropertiesState::instance.eventsCount - 20;
                return;
            case 5:
                if (0 < DAT_MapPropertiesState::instance.eventListScrollOffset) {
                    DAT_MapPropertiesState::instance.eventListScrollOffset
                        = DAT_MapPropertiesState::instance.eventListScrollOffset - 1;
                    *currentValue = DAT_MapPropertiesState::instance.eventListScrollOffset;
                    return;
                }
                break;
            case 6:
                if (DAT_MapPropertiesState::instance.eventListScrollOffset
                    < DAT_MapPropertiesState::instance.eventsCount - 20) {
                    DAT_MapPropertiesState::instance.eventListScrollOffset
                        = DAT_MapPropertiesState::instance.eventListScrollOffset + 1;
                }
                break;
            default:
                return;
            }
            *currentValue = DAT_MapPropertiesState::instance.eventListScrollOffset;
        }

    }
}
}
