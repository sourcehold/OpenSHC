#include "OpenSHC/Map/MapPropertiesState.func.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::ScenarioEvents::ScenarioEventCondition;

    namespace {

        // the part of a scenario event up to the end of its condition list
        struct ScenarioEventConditionsCopy {
            IngameEventHeader header;
            int actionData;
            int scenarioEventType;
            byte allOrAnyCondition;
            byte magic;
            byte repeat;
            byte repeatMonths;
            ScenarioEventCondition conditions[40];
        };

    }

    // FUNCTION: STRONGHOLDCRUSADER 0x004C1320
    void MapPropertiesState::removeProcessedInvasionEvents()
    {
        for (int i = 0; i < this->eventsCount; ++i) {
            if (this->scenarioEvents[i].header.tl_type != 3) {
                continue;
            }
            ScenarioEventConditionsCopy copy;
            memcpy(&copy, &this->scenarioEvents[i], sizeof(copy));
            for (int condition = 0; condition < 40; ++condition) {
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
