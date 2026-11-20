#include "../MapPropertiesState.func.hpp"

#include "OpenSHC/Map/ScenarioEventConditionsCopy.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004C1320
    void MapPropertiesState::removeProcessedInvasionEvents()
    {
        for (int i = 0; i < this->eventsCount; ++i) {
            if (this->scenarioEvents[i].header.tl_type != 3) {
                continue;
            }
            ScenarioEventConditionsCopy copy;
            memcpy(&copy, &this->scenarioEvents[i], sizeof(copy));
            for (int condition = 0; condition < countof(this->scenarioEvents[i].data.scenario.conditions);
                ++condition) {
                this->scenarioEvents[i].data.scenario.conditions[condition].enabled = 0;
                this->scenarioEvents[i].data.scenario.conditions[condition].value = 0;
                this->scenarioEvents[i].data.scenario.conditions[condition].subType = 0;
            }
            for (int condition = 0; condition < 20; ++condition) {
                this->scenarioEvents[i].data.scenario.conditions[condition].enabled
                    = (byte)copy.conditions[condition].value;
                this->scenarioEvents[i].data.scenario.conditions[condition].value
                    = copy.conditions[condition + 20].value;
                this->scenarioEvents[i].data.scenario.conditions[condition].subType
                    = copy.conditions[condition + 20].subType;
            }
        }
        MACRO_CALL_MEMBER(MapPropertiesState_Func::pruneInvalidEventTriggerLinks, this)();
    }

}
}
