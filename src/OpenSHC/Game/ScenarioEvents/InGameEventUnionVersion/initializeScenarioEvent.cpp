#include "../InGameEventUnionVersion.func.hpp"

namespace OpenSHC {
namespace Game {
    namespace ScenarioEvents {

        // FUNCTION: STRONGHOLDCRUSADER 0x004B77A0
        ScenarioEventCondition* InGameEventUnionVersion::initializeScenarioEvent()
        {
            this->header.month = 0;
            this->header.year = 1181;
            this->header.tl_type = 3;
            this->data.scenario.ScenarioEventType = 0;
            this->data.scenario.actionData = 0;
            *(short*)&this->data.scenario.allOrAnyCondition = 1;
            this->data.scenario.repeat = 0;
            ScenarioEventCondition* condition = this->data.scenario.conditions;
            for (int i = 0; i < countof(this->data.scenario.conditions); ++i) {
                condition->enabled = 0;
                condition->value = 0;
                condition->subType = 0;
                ++condition;
            }
            return condition;
        }

    }
}
}
