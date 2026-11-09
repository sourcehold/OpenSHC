#include "../Unused.func.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004BA560
        void Unused::MenuItemActionHandler_UnusedCreateMessageEvent_Unknown(int index, ...)
        {
            if (DAT_MapPropertiesState::instance.offset + index >= (int)DAT_MapPropertiesState::instance.total) {
                return;
            }
            DAT_MapPropertiesState::instance.indexStored = index;
            if (index == -1) {
                return;
            }
            DAT_MapPropertiesState::instance.value
                = DAT_MapPropertiesState::instance.unknownArray_01[DAT_MapPropertiesState::instance.offset + index];
            if (!DAT_MapPropertiesState::instance.flag) {
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .data.scenario.actionData = DAT_MapPropertiesState::instance.value;
                return;
            }
            DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                .data.scenario.actionData = DAT_MapPropertiesState::instance.value;
        }

    }
}
}
