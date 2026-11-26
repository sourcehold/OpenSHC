#include "../General.func.hpp"

#include "OpenSHC/Game/ScenarioEvents/Enums/ScenarioEventType.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004B9E50
        void General::MenuItemActionHandler_General_EventSlider(
            int slider, int scrollbarEvent, int* minValue, int* maxValue, int* currentValue)
        {
            // the highest amount: by event type for the amount sliders, whose number is the type plus one
            int limit = 0;
            switch (slider) {
            case OpenSHC::Game::ScenarioEvents::Enums::SET_LION_AWAKES + 1:
                limit = 10;
                break;
            case OpenSHC::Game::ScenarioEvents::Enums::SET_PLAGUE + 1:
            case OpenSHC::Game::ScenarioEvents::Enums::SET_LION_ATTACK + 1:
                limit = 5;
                break;
            case OpenSHC::Game::ScenarioEvents::Enums::SET_BANDITS + 1:
            case OpenSHC::Game::ScenarioEvents::Enums::SET_ARCHERS + 1:
                limit = 20;
                break;
            case -10:
                limit = DAT_MapPropertiesState::instance.invasionEventContent.field_0xa4;
                break;
            }
            // scrollbarEvent 1 sets a slider up, 2 and 3 store its value, 4 brings the stored value into range,
            // 5 and 6 step it, and 7 sets the two repeat sliders to 1
            switch (slider) {
            case -1:
                // how often the event repeats, 0 to 60, for the events that can repeat
                switch (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.ScenarioEventType) {
                case OpenSHC::Game::ScenarioEvents::Enums::SET_TRAVELING_FAIR:
                case OpenSHC::Game::ScenarioEvents::Enums::SET_PLAGUE:
                case OpenSHC::Game::ScenarioEvents::Enums::SET_WHEAT_DISEASE:
                case OpenSHC::Game::ScenarioEvents::Enums::SET_HOPS_WEEVIL:
                case OpenSHC::Game::ScenarioEvents::Enums::SET_APPLE_BLIGHT:
                case OpenSHC::Game::ScenarioEvents::Enums::SET_TREE_FUNGUS:
                case OpenSHC::Game::ScenarioEvents::Enums::SET_RABBIT_EXPLOSION:
                case OpenSHC::Game::ScenarioEvents::Enums::SET_LION_ATTACK:
                case OpenSHC::Game::ScenarioEvents::Enums::SET_BANDITS:
                case OpenSHC::Game::ScenarioEvents::Enums::SET_MAD_COWS:
                case OpenSHC::Game::ScenarioEvents::Enums::SET_ARCHERS:
                case OpenSHC::Game::ScenarioEvents::Enums::SET_THEFT_FROM_GRANARY:
                case OpenSHC::Game::ScenarioEvents::Enums::SET_FIRE:
                    switch (scrollbarEvent) {
                    case 1:
                        *minValue = 0;
                        *maxValue = 60;
                        *currentValue = DAT_MapPropertiesState::instance
                                            .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                            .data.scenario.repeat;
                        return;
                    case 2:
                    case 3:
                        *minValue = 0;
                        DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .data.scenario.repeat = *currentValue;
                        return;
                    case 7:
                        *currentValue = 1;
                        break;
                    case 4:
                        *currentValue = DAT_MapPropertiesState::instance
                                            .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                            .data.scenario.repeat;
                        *minValue = 0;
                        *maxValue = 60;
                        if (*currentValue > 60) {
                            *currentValue = 60;
                            DAT_MapPropertiesState::instance
                                .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                .data.scenario.repeat = *maxValue;
                        }
                        if (*currentValue < *minValue) {
                            *currentValue = *minValue;
                            DAT_MapPropertiesState::instance
                                .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                .data.scenario.repeat = *minValue;
                        }
                        break;
                    }
                }
                break;
            case -2:
                // the months between two repeats, 1 to 10
                switch (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.ScenarioEventType) {
                case OpenSHC::Game::ScenarioEvents::Enums::SET_TRAVELING_FAIR:
                case OpenSHC::Game::ScenarioEvents::Enums::SET_PLAGUE:
                case OpenSHC::Game::ScenarioEvents::Enums::SET_WHEAT_DISEASE:
                case OpenSHC::Game::ScenarioEvents::Enums::SET_HOPS_WEEVIL:
                case OpenSHC::Game::ScenarioEvents::Enums::SET_APPLE_BLIGHT:
                case OpenSHC::Game::ScenarioEvents::Enums::SET_TREE_FUNGUS:
                case OpenSHC::Game::ScenarioEvents::Enums::SET_RABBIT_EXPLOSION:
                case OpenSHC::Game::ScenarioEvents::Enums::SET_LION_ATTACK:
                case OpenSHC::Game::ScenarioEvents::Enums::SET_BANDITS:
                case OpenSHC::Game::ScenarioEvents::Enums::SET_MAD_COWS:
                case OpenSHC::Game::ScenarioEvents::Enums::SET_ARCHERS:
                case OpenSHC::Game::ScenarioEvents::Enums::SET_THEFT_FROM_GRANARY:
                case OpenSHC::Game::ScenarioEvents::Enums::SET_FIRE:
                    switch (scrollbarEvent) {
                    case 1:
                        *minValue = 1;
                        *maxValue = 10;
                        *currentValue = DAT_MapPropertiesState::instance
                                            .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                            .data.scenario.repeatMonths;
                        return;
                    case 2:
                    case 3:
                        *minValue = 1;
                        DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .data.scenario.repeatMonths = *currentValue;
                        return;
                    case 7:
                        *currentValue = 1;
                        break;
                    case 4:
                        *currentValue = DAT_MapPropertiesState::instance
                                            .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                            .data.scenario.repeatMonths;
                        *minValue = 1;
                        *maxValue = 10;
                        if (*currentValue > 10) {
                            *currentValue = 10;
                            DAT_MapPropertiesState::instance
                                .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                .data.scenario.repeatMonths = *maxValue;
                        }
                        if (*currentValue < *minValue) {
                            *currentValue = *minValue;
                            DAT_MapPropertiesState::instance
                                .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                .data.scenario.repeatMonths = *minValue;
                        }
                        break;
                    }
                }
                break;
            case OpenSHC::Game::ScenarioEvents::Enums::SET_LION_AWAKES + 1:
            case OpenSHC::Game::ScenarioEvents::Enums::SET_PLAGUE + 1:
            case OpenSHC::Game::ScenarioEvents::Enums::SET_LION_ATTACK + 1:
            case OpenSHC::Game::ScenarioEvents::Enums::SET_BANDITS + 1:
            case OpenSHC::Game::ScenarioEvents::Enums::SET_ARCHERS + 1:
                // the amount of the event that this slider belongs to
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.ScenarioEventType
                    == slider - 1) {
                    switch (scrollbarEvent) {
                    case 1:
                        *minValue = 1;
                        *maxValue = limit;
                        *currentValue = DAT_MapPropertiesState::instance
                                            .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                            .data.scenario.actionData;
                        return;
                    case 2:
                    case 3:
                        *minValue = 1;
                        DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .data.scenario.actionData = *currentValue;
                        return;
                    case 4:
                        *currentValue = DAT_MapPropertiesState::instance
                                            .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                            .data.scenario.actionData;
                        *minValue = 1;
                        *maxValue = limit;
                        if (*currentValue > limit) {
                            *currentValue = limit;
                            DAT_MapPropertiesState::instance
                                .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                .data.scenario.actionData = *maxValue;
                        }
                        if (*currentValue < *minValue) {
                            *currentValue = *minValue;
                            DAT_MapPropertiesState::instance
                                .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                .data.scenario.actionData = *minValue;
                        }
                        break;
                    case 5:
                        if (DAT_MapPropertiesState::instance
                                .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                .data.scenario.actionData
                            < *maxValue) {
                            ++DAT_MapPropertiesState::instance
                                  .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                  .data.scenario.actionData;
                        }
                        *currentValue = DAT_MapPropertiesState::instance
                                            .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                            .data.scenario.actionData;
                        return;
                    case 6:
                        if (DAT_MapPropertiesState::instance
                                .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                .data.scenario.actionData
                            > 0) {
                            --DAT_MapPropertiesState::instance
                                  .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                  .data.scenario.actionData;
                        }
                        *currentValue = DAT_MapPropertiesState::instance
                                            .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                            .data.scenario.actionData;
                        break;
                    }
                }
                break;
            case -10:
                // the invasion's amount
                switch (scrollbarEvent) {
                case 1:
                    *minValue = 1;
                    *maxValue = limit;
                    *currentValue = DAT_MapPropertiesState::instance.invasionEventContent.field_0xa8;
                    return;
                case 2:
                case 3:
                    *minValue = 1;
                    DAT_MapPropertiesState::instance.invasionEventContent.field_0xa8 = *currentValue;
                    return;
                case 4:
                    *currentValue = DAT_MapPropertiesState::instance.invasionEventContent.field_0xa8;
                    *minValue = 1;
                    *maxValue = limit;
                    if (*currentValue > limit) {
                        *currentValue = limit;
                        DAT_MapPropertiesState::instance.invasionEventContent.field_0xa8 = *maxValue;
                    }
                    if (*currentValue < *minValue) {
                        *currentValue = *minValue;
                        DAT_MapPropertiesState::instance.invasionEventContent.field_0xa8 = *minValue;
                    }
                    break;
                case 5:
                    if (DAT_MapPropertiesState::instance.invasionEventContent.field_0xa8 < *maxValue) {
                        ++DAT_MapPropertiesState::instance.invasionEventContent.field_0xa8;
                    }
                    *currentValue = DAT_MapPropertiesState::instance.invasionEventContent.field_0xa8;
                    return;
                case 6:
                    if (DAT_MapPropertiesState::instance.invasionEventContent.field_0xa8 > 0) {
                        --DAT_MapPropertiesState::instance.invasionEventContent.field_0xa8;
                    }
                    *currentValue = DAT_MapPropertiesState::instance.invasionEventContent.field_0xa8;
                }
                break;
            }
        }

    }
}
}
