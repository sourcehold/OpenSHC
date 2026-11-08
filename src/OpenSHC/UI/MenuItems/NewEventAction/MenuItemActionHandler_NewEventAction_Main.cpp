#include "../NewEventAction.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Game/ScenarioEvents/Enums/ScenarioEventType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_StopHandlingMenuItems.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004B9C00
        void NewEventAction::MenuItemActionHandler_NewEventAction_Main(int param_1, ...)
        {
            int const pressed = param_1;
            DAT_StopHandlingMenuItems::instance = 0;
            switch (param_1) {
            case 37:
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
                    UI::Enums::MMT_NEW_EVENT, FALSE);
                return;
            case 177:
            case 178:
            case 179:
            case 180:
            case 181:
            case 182:
            case 183:
            case 184:
            case 185:
            case 186:
            case 187:
                // the second column continues the first one's event types
                param_1 -= 21;
            case 128:
            case 129:
            case 130:
            case 131:
            case 132:
            case 133:
            case 134:
            case 135:
            case 136:
            case 137:
            case 138:
            case 139:
            case 140:
            case 141:
            case 142:
            case 143:
            case 144:
            case 145:
            case 146:
            case 147:
            case 148:
            case 149:
            case 150:
            case 151:
            case 152:
            case 153:
            case 154:
            case 155: {
                // the original takes the field's address once and reads and writes through it
                int* const eventType
                    = &DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                           .data.scenario.ScenarioEventType;
                if (*eventType != param_1 - 128) {
                    *eventType = param_1 - 128;
                    DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.actionData = 0;
                    DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.repeat = 0;
                    DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.repeatMonths = 10;
                    int const newType = DAT_MapPropertiesState::instance
                                            .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                            .data.scenario.ScenarioEventType;
                    if (newType == OpenSHC::Game::ScenarioEvents::Enums::SET_MESSAGE
                        || newType == OpenSHC::Game::ScenarioEvents::Enums::SET_WIN_AND_MESSAGE
                        || newType == OpenSHC::Game::ScenarioEvents::Enums::SET_LOSE_AND_MESSAGE) {
                        DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .data.scenario.actionData = -1;
                    }
                }
                int maximum;
                switch (pressed) {
                case 146:
                case 148:
                    maximum = 50;
                    break;
                case 178:
                    maximum = 100;
                    break;
                case 132:
                case 139:
                case 145:
                case 179:
                    maximum = 10;
                    break;
                default:
                    return;
                }
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.actionData
                    == 0) {
                    DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.actionData = 1;
                }
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setSliderParameters, DAT_MenuModalComposition2::ptr)(1,
                    maximum,
                    DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.actionData,
                    (undefined*)&DAT_MapPropertiesState::instance
                        .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data,
                    (void*)MACRO_CALL(UI::Helpers_Func::CaptureCurrentTimeToUnknownTime01));
                DAT_MapPropertiesState::instance.sliderPopupDelay = 2;
                DAT_MapPropertiesState::instance.sliderPopupX = DAT_ButtonX::instance + 58;
                DAT_MapPropertiesState::instance.sliderPopupY = DAT_ButtonY::instance + 28;
            }
            }
        }

    }
}
}
