#include "OpenSHC/Map/MapPropertiesState.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B78D0
    int MapPropertiesState::getEventIDForTimeUntilDefeatEventType()
    {
        if (DAT_GameCore::instance.gameMode_2 != 0 && DAT_GameCore::instance.gameMode_2 != 5
            && DAT_GameCore::instance.gameMode_2 != 2) {
            return -1;
        }
        for (int i = 0; i < DAT_MapPropertiesState::instance.eventsCount; ++i) {
            if (DAT_MapPropertiesState::instance.scenarioEvents[i].header.tl_type == 3
                && (DAT_MapPropertiesState::instance.scenarioEvents[i].data.scenario.ScenarioEventType == 1
                    || DAT_MapPropertiesState::instance.scenarioEvents[i].data.scenario.ScenarioEventType == 27)
                && DAT_MapPropertiesState::instance.scenarioEvents[i].data.scenario.conditions[0].enabled != 0) {
                return i;
            }
        }
        return -1;
    }

}
}
