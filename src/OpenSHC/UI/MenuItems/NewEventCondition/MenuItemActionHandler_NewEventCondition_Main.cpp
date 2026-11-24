#include "../NewEventCondition.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Game/ScenarioEvents/Enums/ScenarioEventConditionIndex.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnknownTime_01.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004B9620
        void NewEventCondition::MenuItemActionHandler_NewEventCondition_Main(int button, ...)
        {
            // the cases stand in the order of the original's code (in ascending order the match is lost)
            switch (button) {
            // all of the conditions, or any of them
            case 104:
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .data.scenario.allOrAnyCondition ^= 1;
                return;
            // back to the event's dialog; the auto stop does not stay on beside another condition
            case 37:
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.conditions[Game::ScenarioEvents::Enums::SECI_AUTO_STOP]
                        .enabled) {
                    for (int i = 1; i < countof(DAT_MapPropertiesState::instance
                                            .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                            .data.scenario.conditions);
                        ++i) {
                        if (DAT_MapPropertiesState::instance
                                .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                .data.scenario.conditions[i]
                                .enabled) {
                            DAT_MapPropertiesState::instance
                                .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                .data.scenario.conditions[Game::ScenarioEvents::Enums::SECI_AUTO_STOP]
                                .enabled = 0;
                            break;
                        }
                    }
                }
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
                    UI::Enums::MMT_NEW_EVENT, FALSE);
                return;
            // conditions 20 to 39: the button less 64, then the code of 106 to 125
            case 190:
            case 191:
            case 192:
            case 193:
            case 194:
            case 195:
            case 196:
            case 197:
            case 198:
            case 199:
            case 200:
            case 201:
            case 202:
            case 203:
            case 204:
            case 205:
            case 206:
            case 207:
            case 208:
            case 209:
                button -= 64;
            // conditions 0 to 19: selected, switched on, value at least its minimum; a slider if it has a maximum
            case 106:
            case 107:
            case 108:
            case 109:
            case 110:
            case 111:
            case 112:
            case 113:
            case 114:
            case 115:
            case 116:
            case 117:
            case 118:
            case 119:
            case 120:
            case 121:
            case 122:
            case 123:
            case 124:
            case 125:
                DAT_MapPropertiesState::instance.invasionTroopIndex = button - 106;
                // through the stored index (through button - 106 again, the match is lost)
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .data.scenario.conditions[DAT_MapPropertiesState::instance.invasionTroopIndex]
                    .enabled = 1;
                DAT_UnknownTime_01::instance = 0;
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.conditions[DAT_MapPropertiesState::instance.invasionTroopIndex]
                        .value
                    < DAT_MissionAestheticsDefinedData::instance
                        .EventConditionMinValue[DAT_MapPropertiesState::instance.invasionTroopIndex]) {
                    DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.conditions[DAT_MapPropertiesState::instance.invasionTroopIndex]
                        .value = DAT_MissionAestheticsDefinedData::instance
                                     .EventConditionMinValue[DAT_MapPropertiesState::instance.invasionTroopIndex];
                }
                if (DAT_MissionAestheticsDefinedData::instance
                        .EventConditionMaxValue[DAT_MapPropertiesState::instance.invasionTroopIndex]
                    != 0) {
                    MACRO_CALL_MEMBER(
                        UI::MenuModalComposition_Func::setSliderParameters2, DAT_MenuModalComposition2::ptr)(
                        DAT_MissionAestheticsDefinedData::instance
                            .EventConditionMinValue[DAT_MapPropertiesState::instance.invasionTroopIndex],
                        DAT_MissionAestheticsDefinedData::instance
                            .EventConditionMaxValue[DAT_MapPropertiesState::instance.invasionTroopIndex],
                        DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .data.scenario.conditions[DAT_MapPropertiesState::instance.invasionTroopIndex]
                            .value,
                        (dword)&DAT_MapPropertiesState::instance
                            .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .data.scenario.conditions[DAT_MapPropertiesState::instance.invasionTroopIndex]
                            .value,
                        MACRO_CALL(UI::Helpers_Func::CaptureCurrentTimeToUnknownTime01));
                    MACRO_CALL_MEMBER(
                        UI::MenuModalComposition_Func::setExtraActiveModalDialog, DAT_MenuModalComposition2::ptr)(
                        UI::Enums::MMT_OVERLAY_SLIDER, DAT_ButtonX::instance + 58, DAT_ButtonY::instance + 28);
                }
                return;
            // the selected condition off
            case 19:
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .data.scenario.conditions[DAT_MapPropertiesState::instance.invasionTroopIndex]
                    .enabled = 0;
                return;
            // the selected condition's value one down, not below its minimum
            case 1000:
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.conditions[DAT_MapPropertiesState::instance.invasionTroopIndex]
                        .value
                    > DAT_MissionAestheticsDefinedData::instance
                        .EventConditionMinValue[DAT_MapPropertiesState::instance.invasionTroopIndex]) {
                    --DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                          .data.scenario.conditions[DAT_MapPropertiesState::instance.invasionTroopIndex]
                          .value;
                }
                return;
            // the selected condition's previous option
            case 2000: {
                // declared before the kind test (declared at its search loop, the match is lost)
                int optionIndex = 0;
                // option kinds: 0 none, 1 a list of goods (ResourceType ids, ended by -1), 2 an opponent (0 to 4)
                if (DAT_MissionAestheticsDefinedData::instance
                        .EventConditionParamKind[DAT_MapPropertiesState::instance.invasionTroopIndex]
                    == 0) {
                    return;
                }
                if (DAT_MissionAestheticsDefinedData::instance
                        .EventConditionParamKind[DAT_MapPropertiesState::instance.invasionTroopIndex]
                    == 1) {
                    for (; DAT_MissionAestheticsDefinedData::instance
                               .EventConditionOptionValues[DAT_MapPropertiesState::instance.invasionTroopIndex]
                                                          [optionIndex]
                        != DAT_MapPropertiesState::instance
                            .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .data.scenario.conditions[DAT_MapPropertiesState::instance.invasionTroopIndex]
                            .subType;
                        ++optionIndex) {}
                    --optionIndex;
                    if (optionIndex < 0) {
                        // 100 is the original's bound: a row's bytes, not its 25 entries (a while loop loses the match)
                        int last = 0;
                        for (; last < 100; ++last) {
                            if (DAT_MissionAestheticsDefinedData::instance
                                    .EventConditionOptionValues[DAT_MapPropertiesState::instance.invasionTroopIndex]
                                                               [last]
                                == -1) {
                                --last;
                                break;
                            }
                        }
                        DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .data.scenario.conditions[DAT_MapPropertiesState::instance.invasionTroopIndex]
                            .subType
                            = DAT_MissionAestheticsDefinedData::instance
                                  .EventConditionOptionValues[DAT_MapPropertiesState::instance.invasionTroopIndex]
                                                             [last];
                    } else {
                        DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .data.scenario.conditions[DAT_MapPropertiesState::instance.invasionTroopIndex]
                            .subType
                            = DAT_MissionAestheticsDefinedData::instance
                                  .EventConditionOptionValues[DAT_MapPropertiesState::instance.invasionTroopIndex]
                                                             [optionIndex];
                    }
                }
                if (DAT_MissionAestheticsDefinedData::instance
                        .EventConditionParamKind[DAT_MapPropertiesState::instance.invasionTroopIndex]
                    == 2) {
                    --DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                          .data.scenario.conditions[DAT_MapPropertiesState::instance.invasionTroopIndex]
                          .subType;
                    if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .data.scenario.conditions[DAT_MapPropertiesState::instance.invasionTroopIndex]
                            .subType
                        < 0) {
                        DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .data.scenario.conditions[DAT_MapPropertiesState::instance.invasionTroopIndex]
                            .subType = 4;
                    }
                }
                return;
            }
            // the selected condition's value one up, not above its maximum
            case 1001:
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.conditions[DAT_MapPropertiesState::instance.invasionTroopIndex]
                        .value
                    < DAT_MissionAestheticsDefinedData::instance
                        .EventConditionMaxValue[DAT_MapPropertiesState::instance.invasionTroopIndex]) {
                    ++DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                          .data.scenario.conditions[DAT_MapPropertiesState::instance.invasionTroopIndex]
                          .value;
                }
                return;
            // the selected condition's next option
            case 2001:
            case 2002: {
                // declared before the kind test (declared at its search loop, the match is lost)
                int optionIndex = 0;
                if (DAT_MissionAestheticsDefinedData::instance
                        .EventConditionParamKind[DAT_MapPropertiesState::instance.invasionTroopIndex]
                    == 0) {
                    return;
                }
                if (DAT_MissionAestheticsDefinedData::instance
                        .EventConditionParamKind[DAT_MapPropertiesState::instance.invasionTroopIndex]
                    == 1) {
                    // a local for the option (compared from the field, the search loses the match)
                    int option = DAT_MapPropertiesState::instance
                                     .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                     .data.scenario.conditions[DAT_MapPropertiesState::instance.invasionTroopIndex]
                                     .subType;
                    // an option of 0 is taken as bread, the first entry of every goods list
                    if (option == 0) {
                        DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .data.scenario.conditions[DAT_MapPropertiesState::instance.invasionTroopIndex]
                            .subType = Game::Resources::RT_BREAD;
                        option = Game::Resources::RT_BREAD;
                    }
                    for (; DAT_MissionAestheticsDefinedData::instance
                               .EventConditionOptionValues[DAT_MapPropertiesState::instance.invasionTroopIndex]
                                                          [optionIndex]
                        != option;
                        ++optionIndex) {}
                    ++optionIndex;
                    if (DAT_MissionAestheticsDefinedData::instance
                            .EventConditionOptionValues[DAT_MapPropertiesState::instance.invasionTroopIndex]
                                                       [optionIndex]
                        == -1) {
                        DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .data.scenario.conditions[DAT_MapPropertiesState::instance.invasionTroopIndex]
                            .subType
                            = DAT_MissionAestheticsDefinedData::instance
                                  .EventConditionOptionValues[DAT_MapPropertiesState::instance.invasionTroopIndex][0];
                    } else {
                        DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .data.scenario.conditions[DAT_MapPropertiesState::instance.invasionTroopIndex]
                            .subType
                            = DAT_MissionAestheticsDefinedData::instance
                                  .EventConditionOptionValues[DAT_MapPropertiesState::instance.invasionTroopIndex]
                                                             [optionIndex];
                    }
                }
                if (DAT_MissionAestheticsDefinedData::instance
                        .EventConditionParamKind[DAT_MapPropertiesState::instance.invasionTroopIndex]
                    == 2) {
                    ++DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                          .data.scenario.conditions[DAT_MapPropertiesState::instance.invasionTroopIndex]
                          .subType;
                    if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .data.scenario.conditions[DAT_MapPropertiesState::instance.invasionTroopIndex]
                            .subType
                        > 4) {
                        DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .data.scenario.conditions[DAT_MapPropertiesState::instance.invasionTroopIndex]
                            .subType = 0;
                    }
                }
                return;
            }
            // conditions 20 to 39 off: the button less 64, then the code of 5106 to 5125
            case 5190:
            case 5191:
            case 5192:
            case 5193:
            case 5194:
            case 5195:
            case 5196:
            case 5197:
            case 5198:
            case 5199:
            case 5200:
            case 5201:
            case 5202:
            case 5203:
            case 5204:
            case 5205:
            case 5206:
            case 5207:
            case 5208:
            case 5209:
                button -= 64;
            // conditions 0 to 19 off, unless a dialog is open or the slider's callback ran within the last second
            case 5106:
            case 5107:
            case 5108:
            case 5109:
            case 5110:
            case 5111:
            case 5112:
            case 5113:
            case 5114:
            case 5115:
            case 5116:
            case 5117:
            case 5118:
            case 5119:
            case 5120:
            case 5121:
            case 5122:
            case 5123:
            case 5124:
            case 5125:
                if (DAT_MenuModalComposition2::instance.activeModalDialogID != UI::Enums::MMT_NONE) {
                    return;
                }
                if (timeGetTime() - DAT_UnknownTime_01::instance <= 1000 && DAT_UnknownTime_01::instance != 0) {
                    return;
                }
                DAT_UnknownTime_01::instance = 0;
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .data.scenario.conditions[button - 5106]
                    .enabled = 0;
                return;
            }
        }

    }
}
}
