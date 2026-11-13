#include "OpenSHC/Map/MapPropertiesState.func.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B7930
    void MapPropertiesState::activateScenarioTypeEvents()
    {
        for (int i = 0; i < DAT_MapPropertiesState::instance.eventsCount; ++i) {
            if (DAT_MapPropertiesState::instance.scenarioEvents[i].header.tl_type == 3) {
                int const eventType
                    = DAT_MapPropertiesState::instance.scenarioEvents[i].data.scenario.ScenarioEventType;
                if (eventType == 1 || eventType == 27 || eventType == 0 || eventType == 26) {
                    DAT_MapPropertiesState::instance.scenarioEvents[i].header.done = 1;
                }
            }
        }
    }

}
}
