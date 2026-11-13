#include "OpenSHC/Map/MapPropertiesState.func.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004BB990
    void MapPropertiesState::pruneInvalidEventTriggerLinks()
    {
        for (int i = 0; i < this->eventsCount; ++i) {
            if (this->scenarioEvents[i].header.tl_type == 3
                && DAT_MapPropertiesState::instance.scenarioEvents[i].data.scenario.conditions[0].enabled != 0) {
                for (int condition = 1; condition < 40; ++condition) {
                    if (DAT_MapPropertiesState::instance.scenarioEvents[i].data.scenario.conditions[condition].enabled
                        != 0) {
                        DAT_MapPropertiesState::instance.scenarioEvents[i].data.scenario.conditions[0].enabled = 0;
                        break;
                    }
                }
            }
        }
    }

}
}
