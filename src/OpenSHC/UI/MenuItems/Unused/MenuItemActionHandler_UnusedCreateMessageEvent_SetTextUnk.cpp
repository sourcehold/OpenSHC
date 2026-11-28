#include "../Unused.func.hpp"

#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuView_TriggerPrepare.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

#include "stdlib.h"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using UI::Enums::MenuModalType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004BFE20
        void Unused::MenuItemActionHandler_UnusedCreateMessageEvent_SetTextUnk(int param_1, ...)
        {
            switch (param_1) {
            case 0x25:
                if (!DAT_MapPropertiesState::instance.flag) {
                    if (DAT_MapPropertiesState::instance.value == 0xffffffff) {
                        MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::removeEventAtIndex,
                            DAT_MapPropertiesState::ptr)(DAT_MapPropertiesState::instance.currentEventID);
                    } else {
                        DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .header.year = atol(MACRO_CALL_MEMBER(
                            Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(0xb));
                    }
                    MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NONE, FALSE);
                    MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::sortEventsByDate, DAT_MapPropertiesState::ptr)();
                    MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(0xf);
                    return;
                }
                if (DAT_MapPropertiesState::instance.flag == 1) {
                    if (DAT_MapPropertiesState::instance.value == 0xffffffff) {
                        DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .data.scenario.actionData = -1;
                    }
                    MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NEW_EVENT_ACTION, FALSE);
                    MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(0xf);
                    return;
                }
                DAT_GameCore::instance.descriptionStringTableIndex = DAT_MapPropertiesState::instance.value;
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
                    UI::Enums::MMT_NONE, FALSE);
                DAT_MenuView_TriggerPrepare::instance = TRUE;
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(0xf);
                return;
            case 0x13:
                if (DAT_MapPropertiesState::instance.flag) {
                    return;
                }
                MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::removeEventAtIndex, DAT_MapPropertiesState::ptr)(
                    DAT_MapPropertiesState::instance.currentEventID);
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
                    UI::Enums::MMT_NONE, FALSE);
                MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::sortEventsByDate, DAT_MapPropertiesState::ptr)();
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(0xf);
                return;
            case -1:
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .header.month
                    = DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                          .header.month
                    + 1;
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .header.month
                    >= 12) {
                    DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .header.month = 0;
                }
                return;
            }
        }

    }
}
}
