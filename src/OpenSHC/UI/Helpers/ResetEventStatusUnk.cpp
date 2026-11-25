#include "../Helpers.func.hpp"

#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Game/ScenarioEvents/InGameEventUnionVersion.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/INT_00ec02e8.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00eb1238.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00ed2630.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00ed2fc8.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00ed3070.hpp"

namespace OpenSHC {
namespace UI {

    using Game::ScenarioEvents::InGameEventUnionVersion;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D7200
    void Helpers::ResetEventStatusUnk()
    {
        for (int condition = 0; condition < 40; ++condition) {
            INT_ARRAY_00eb1238::instance[condition] = 0;
        }
        for (int condition = 0; condition < 40; ++condition) {
            INT_ARRAY_00ed2fc8::instance[condition] = 0;
        }
        for (int condition = 0; condition < 40; ++condition) {
            INT_ARRAY_00ed3070::instance[condition] = 0;
        }
        for (int condition = 0; condition < 40; ++condition) {
            INT_ARRAY_00ed2630::instance[condition] = 0;
        }
        for (int event = 0; event < DAT_MapPropertiesState::instance.eventsCount; ++event) {
            InGameEventUnionVersion const& scenarioEvent = DAT_MapPropertiesState::instance.scenarioEvents[event];
            if (scenarioEvent.header.tl_type == 3
                && (scenarioEvent.data.scenario.ScenarioEventType == 1
                    || scenarioEvent.data.scenario.ScenarioEventType == 27)
                && scenarioEvent.data.scenario.conditions[0].enabled) {
                INT_00ec02e8::instance = 1;
            }
        }
        // The original repeats the first loop's check here, then looks for the first event of type 0 or 26.
        for (int event = 0; event < DAT_MapPropertiesState::instance.eventsCount; ++event) {
            InGameEventUnionVersion const& scenarioEvent = DAT_MapPropertiesState::instance.scenarioEvents[event];
            if (scenarioEvent.header.tl_type == 3
                && (scenarioEvent.data.scenario.ScenarioEventType == 1
                    || scenarioEvent.data.scenario.ScenarioEventType == 27)
                && scenarioEvent.data.scenario.conditions[0].enabled) {
                INT_00ec02e8::instance = 1;
            }
            if (scenarioEvent.header.tl_type != 3
                || (scenarioEvent.data.scenario.ScenarioEventType != 0
                    && scenarioEvent.data.scenario.ScenarioEventType != 26)) {
                continue;
            }
            // While the game is suspended, take the last such event that is not in the future.
            if (DAT_GameCore::instance.gameSuspended == 1) {
                int latest = event;
                // The scan advances event itself: a separate index for it compiles differently.
                for (++event; event < DAT_MapPropertiesState::instance.eventsCount; ++event) {
                    InGameEventUnionVersion const& laterEvent = DAT_MapPropertiesState::instance.scenarioEvents[event];
                    if (laterEvent.header.tl_type == 3
                        && (laterEvent.data.scenario.ScenarioEventType == 0
                            || laterEvent.data.scenario.ScenarioEventType == 26)) {
                        if (laterEvent.header.year > DAT_GameState::instance.mapAndTime.year
                            || (laterEvent.header.year == DAT_GameState::instance.mapAndTime.year
                                && laterEvent.header.month > DAT_GameState::instance.mapAndTime.month)) {
                            break;
                        }
                        latest = event;
                    }
                }
                event = latest;
            }
            for (int condition = 0; condition < 40; ++condition) {
                INT_ARRAY_00ed2630::instance[condition] = DAT_MapPropertiesState::instance.scenarioEvents[event]
                                                              .data.scenario.conditions[condition]
                                                              .enabled;
                INT_ARRAY_00ed3070::instance[condition]
                    = DAT_MapPropertiesState::instance.SEC_EventsExtra[event].conditionIsTrue[condition];
                INT_ARRAY_00ed2fc8::instance[condition]
                    = DAT_MapPropertiesState::instance.scenarioEvents[event].data.scenario.conditions[condition].value;
                if (condition == 4 || condition == 5 || condition == 6 || condition == 17 || condition == 7
                    || condition == 1) {
                    INT_ARRAY_00ed2fc8::instance[condition]
                        = MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::getDifficultyMultipliedValue,
                            DAT_MapPropertiesState::ptr)(DAT_MapPropertiesState::instance.scenarioEvents[event]
                                .data.scenario.conditions[condition]
                                .value);
                }
                INT_ARRAY_00eb1238::instance[condition] = DAT_MapPropertiesState::instance.scenarioEvents[event]
                                                              .data.scenario.conditions[condition]
                                                              .subType;
            }
            return;
        }
    }

}
}
