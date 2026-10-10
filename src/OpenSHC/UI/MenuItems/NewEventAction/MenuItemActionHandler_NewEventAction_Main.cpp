#include "../NewEventAction.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Game/ScenarioEvents/InGameEventUnion.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_StopHandlingMenuItems.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using Game::ScenarioEvents::InGameEventUnion;
        using UI::Enums::MenuModalType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004B9C00
        void NewEventAction::MenuItemActionHandler_NewEventAction_Main(int param_1, ...)
        {
            int* piVar1;
            InGameEventUnion* destination;
            int iVar2;
            DAT_StopHandlingMenuItems::instance = 0;
            iVar2 = param_1;
            switch (param_1) {
            case 0x25:
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
                    UI::Enums::MMT_NEW_EVENT, FALSE);
                return;
            case 0xb1:
            case 0xb2:
            case 0xb3:
            case 0xb4:
            case 0xb5:
            case 0xb6:
            case 0xb7:
            case 0xb8:
            case 0xb9:
            case 0xba:
            case 0xbb:
                iVar2 = param_1 + -0x15;
            case 0x80:
            case 0x81:
            case 0x82:
            case 0x83:
            case 0x84:
            case 0x85:
            case 0x86:
            case 0x87:
            case 0x88:
            case 0x89:
            case 0x8a:
            case 0x8b:
            case 0x8c:
            case 0x8d:
            case 0x8e:
            case 0x8f:
            case 0x90:
            case 0x91:
            case 0x92:
            case 0x93:
            case 0x94:
            case 0x95:
            case 0x96:
            case 0x97:
            case 0x98:
            case 0x99:
            case 0x9a:
            case 0x9b:
                piVar1
                    = &DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                           .data.scenario.ScenarioEventType;
                if (*piVar1 != iVar2 + -0x80) {
                    *piVar1 = iVar2 + -0x80;
                    DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.actionData = 0;
                    DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.repeat = 0;
                    DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.repeatMonths = 10;
                    iVar2 = DAT_MapPropertiesState::instance
                                .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                .data.scenario.ScenarioEventType;
                    if (iVar2 == 2 || iVar2 == 0x1a || iVar2 == 0x1b) {
                        DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .data.scenario.actionData = -1;
                    }
                }
                switch (param_1) {
                case 0x84:
                case 0x8b:
                case 0x91:
                case 0xb3:
                    iVar2 = 10;
                    break;
                default:
                    goto switchD_004b9c26_caseD_26;
                case 0x92:
                case 0x94:
                    iVar2 = 0x32;
                    break;
                case 0xb2:
                    iVar2 = 100;
                }
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.actionData
                    == 0) {
                    DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.actionData = 1;
                }
                destination
                    = &DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                           .data;
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setSliderParameters, DAT_MenuModalComposition2::ptr)(1,
                    iVar2, (destination->scenario).actionData, (undefined*)((int)(destination)),
                    (void*)MACRO_CALL(UI::Helpers_Func::CaptureCurrentTimeToUnknownTime01));
                DAT_MapPropertiesState::instance.sliderPopupX = DAT_ButtonX::instance + 0x3a;
                DAT_MapPropertiesState::instance.sliderPopupY = DAT_ButtonY::instance + 0x1c;
                DAT_MapPropertiesState::instance.sliderPopupDelay = 2;
            }
        switchD_004b9c26_caseD_26:
            return;
        }

    }
}
}
