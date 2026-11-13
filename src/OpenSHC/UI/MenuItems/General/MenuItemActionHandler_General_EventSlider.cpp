#include "../General.func.hpp"

#include "OpenSHC/Game/ScenarioEvents/Enums/ScenarioEventType.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004B9E50
        void General::MenuItemActionHandler_General_EventSlider(
            int param_1, int param_2, int* minValue, int* maxValue, int* currentValue)
        {
            int iVar1 = 0;
            switch (param_1) {
            case 5:
                iVar1 = 10;
                break;
            case 12:
            case 18:
                iVar1 = 5;
                break;
            case 19:
            case 21:
                iVar1 = 20;
                break;
            case -10:
                iVar1 = (*(int*)&DAT_MapPropertiesState::instance.invasionEventContent.padding_0xa4[0]);
                break;
            case -9:
            case -8:
            case -7:
            case -6:
            case -5:
            case -4:
            case -3:
            case -2:
            case -1:
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
            case 20:
                break;
            default:
                break;
            }
            switch (param_1) {
            case -1:
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
                    switch (param_2) {
                    case 1:
                        *minValue = 0;
                        *maxValue = 60;
                        *currentValue = (uint)DAT_MapPropertiesState::instance
                                            .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                            .data.scenario.repeat;
                        return;
                    case 2:
                    case 3:
                        *minValue = 0;
                        DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .data.scenario.repeat = (byte)*currentValue;
                        return;
                    case 4:
                        *currentValue = (uint)DAT_MapPropertiesState::instance
                                            .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                            .data.scenario.repeat;
                        *minValue = 0;
                        *maxValue = 60;
                        if (*currentValue > 60) {
                            *currentValue = 60;
                            DAT_MapPropertiesState::instance
                                .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                .data.scenario.repeat = (byte)*maxValue;
                        }
                        if (*currentValue < *minValue) {
                            *currentValue = *minValue;
                            DAT_MapPropertiesState::instance
                                .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                .data.scenario.repeat = (byte)*minValue;
                        }
                        break;
                    case 7:
                        *currentValue = 1;
                        break;
                    }
                }
                break;
            case -2:
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
                    switch (param_2) {
                    case 1:
                        *minValue = 1;
                        *maxValue = 10;
                        *currentValue = (uint)DAT_MapPropertiesState::instance
                                            .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                            .data.scenario.repeatMonths;
                        return;
                    case 2:
                    case 3:
                        *minValue = 1;
                        DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .data.scenario.repeatMonths = (byte)*currentValue;
                        return;
                    case 7:
                        *currentValue = 1;
                        break;
                    case 4:
                        *currentValue = (uint)DAT_MapPropertiesState::instance
                                            .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                            .data.scenario.repeatMonths;
                        *minValue = 1;
                        *maxValue = 10;
                        if (*currentValue > 10) {
                            *currentValue = 10;
                            DAT_MapPropertiesState::instance
                                .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                .data.scenario.repeatMonths = (byte)*maxValue;
                        }
                        if (*currentValue < *minValue) {
                            *currentValue = *minValue;
                            DAT_MapPropertiesState::instance
                                .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                .data.scenario.repeatMonths = (byte)*minValue;
                        }
                        break;
                    }
                }
                break;
            case 5:
            case 12:
            case 18:
            case 19:
            case 21:
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.ScenarioEventType
                    == param_1 - 1) {
                    switch (param_2) {
                    case 1:
                        *minValue = 1;
                        *maxValue = iVar1;
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
                        *maxValue = iVar1;
                        if (iVar1 < *currentValue) {
                            *currentValue = iVar1;
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
                        iVar1 = DAT_MapPropertiesState::instance
                                    .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                    .data.scenario.actionData;
                        if (iVar1 < *maxValue) {
                            DAT_MapPropertiesState::instance
                                .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                .data.scenario.actionData = iVar1 + 1;
                        }
                        *currentValue = DAT_MapPropertiesState::instance
                                            .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                            .data.scenario.actionData;
                        return;
                    case 6:
                        iVar1 = DAT_MapPropertiesState::instance
                                    .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                    .data.scenario.actionData;
                        if (iVar1 > 0) {
                            DAT_MapPropertiesState::instance
                                .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                .data.scenario.actionData = iVar1 - 1;
                        }
                        *currentValue = DAT_MapPropertiesState::instance
                                            .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                            .data.scenario.actionData;
                    }
                }
                break;
            case -10:
                switch (param_2) {
                case 1:
                    *minValue = 1;
                    *maxValue = iVar1;
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
                    *maxValue = iVar1;
                    if (iVar1 < *currentValue) {
                        *currentValue = iVar1;
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
            case -9:
            case -8:
            case -7:
            case -6:
            case -5:
            case -4:
            case -3:
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
            case 20:
                break;
            default:
                break;
            }
        }

    }
}
}
