#include "../General.func.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004B9E50
        void General::MenuItemActionHandler_General_EventSlider(
            int param_1, int param_2, int* minValue, int* maxValue, int* currentValue)
        {
            int iVar1;
            iVar1 = 0;
            switch (param_1) {
            case 5:
                iVar1 = 10;
                break;
            case 0xc:
            case 0x12:
                iVar1 = 5;
                break;
            case 0x13:
            case 0x15:
                iVar1 = 0x14;
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
            case 0xb:
            case 0xd:
            case 0xe:
            case 0xf:
            case 0x10:
            case 0x11:
            case 0x14:
                break;
            default:
                break;
            }
            switch (param_1) {
            case 5:
            case 0xc:
            case 0x12:
            case 0x13:
            case 0x15:
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.ScenarioEventType
                    == param_1 + -1) {
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
                        if (0 < iVar1) {
                            DAT_MapPropertiesState::instance
                                .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                .data.scenario.actionData = iVar1 + -1;
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
                    *currentValue = DAT_MapPropertiesState::instance.invasionEventContent.field49_0xa8;
                    return;
                case 2:
                case 3:
                    *minValue = 1;
                    DAT_MapPropertiesState::instance.invasionEventContent.field49_0xa8 = *currentValue;
                    return;
                case 4:
                    *currentValue = DAT_MapPropertiesState::instance.invasionEventContent.field49_0xa8;
                    *minValue = 1;
                    *maxValue = iVar1;
                    if (iVar1 < *currentValue) {
                        *currentValue = iVar1;
                        DAT_MapPropertiesState::instance.invasionEventContent.field49_0xa8 = *maxValue;
                    }
                    if (*currentValue < *minValue) {
                        *currentValue = *minValue;
                        DAT_MapPropertiesState::instance.invasionEventContent.field49_0xa8 = *minValue;
                    }
                    break;
                case 5:
                    if (DAT_MapPropertiesState::instance.invasionEventContent.field49_0xa8 < *maxValue) {
                        DAT_MapPropertiesState::instance.invasionEventContent.field49_0xa8
                            = DAT_MapPropertiesState::instance.invasionEventContent.field49_0xa8 + 1;
                    }
                    *currentValue = DAT_MapPropertiesState::instance.invasionEventContent.field49_0xa8;
                    return;
                case 6:
                    if (0 < DAT_MapPropertiesState::instance.invasionEventContent.field49_0xa8) {
                        DAT_MapPropertiesState::instance.invasionEventContent.field49_0xa8
                            = DAT_MapPropertiesState::instance.invasionEventContent.field49_0xa8 + -1;
                    }
                    *currentValue = DAT_MapPropertiesState::instance.invasionEventContent.field49_0xa8;
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
            case 0xb:
            case 0xd:
            case 0xe:
            case 0xf:
            case 0x10:
            case 0x11:
            case 0x14:
                break;
            case -2:
                switch (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.ScenarioEventType) {
                case 5:
                case 0xb:
                case 0xc:
                case 0xd:
                case 0xe:
                case 0xf:
                case 0x10:
                case 0x11:
                case 0x12:
                case 0x13:
                case 0x14:
                case 0x1d:
                case 0x1e:
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
                    case 4:
                        *currentValue = (uint)DAT_MapPropertiesState::instance
                                            .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                            .data.scenario.repeatMonths;
                        *minValue = 1;
                        *maxValue = 10;
                        if (10 < *currentValue) {
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
                    case 7:
                    switchD_004b9fd6_caseD_7:
                        *currentValue = 1;
                    }
                }
                break;
            case -1:
                switch (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.ScenarioEventType) {
                case 5:
                case 0xb:
                case 0xc:
                case 0xd:
                case 0xe:
                case 0xf:
                case 0x10:
                case 0x11:
                case 0x12:
                case 0x13:
                case 0x14:
                case 0x1d:
                case 0x1e:
                    switch (param_2) {
                    case 1:
                        *minValue = 0;
                        *maxValue = 0x3c;
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
                        *maxValue = 0x3c;
                        if (0x3c < *currentValue) {
                            *currentValue = 0x3c;
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
                        goto switchD_004b9fd6_caseD_7;
                    }
                }
                break;
            default:
                break;
            }
        }

    }
}
}
