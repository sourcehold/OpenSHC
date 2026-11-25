#include "../NewEvent.func.hpp"

#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

#include <stdlib.h>

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace NewEvent {

            // FUNCTION: STRONGHOLDCRUSADER 0x004C0040
            void MenuItemActionHandler_NewEvent_Main(int button, ...)
            {
                switch (button) {
                case 19:
                    // Delete the event, then close the dialog as OK does.
                    MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::removeEventAtIndex,
                        DAT_MapPropertiesState::ptr)(DAT_MapPropertiesState::instance.currentEventID);
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::MapPropertiesState_Func::sortEventsByDate, DAT_MapPropertiesState::ptr)();
                    MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex,
                        DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_UNKNOWN_15);
                    return;
                case 37:
                    // OK: take the year typed in, close the dialog and keep the events in date order.
                    DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .header.year = atol(MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                        DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_UNKNOWN_11));
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::MapPropertiesState_Func::sortEventsByDate, DAT_MapPropertiesState::ptr)();
                    MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex,
                        DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_UNKNOWN_15);
                    return;
                case -1:
                    // The month button, from December back to January.
                    ++DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                          .header.month;
                    if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .header.month
                        >= 12) {
                        DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .header.month = 0;
                    }
                    return;
                case 100:
                    // "Edit Conditions"
                    DAT_MapPropertiesState::instance.invasionTroopIndex = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NEW_EVENT_CONDITION, FALSE);
                    return;
                case 101:
                    // "Edit Actions"
                    DAT_MapPropertiesState::instance.sliderPopupDelay = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NEW_EVENT_ACTION, FALSE);
                    return;
                }
            }

        }
    }
}
}
