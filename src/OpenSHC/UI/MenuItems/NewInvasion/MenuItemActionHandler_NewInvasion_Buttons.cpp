#include "../NewInvasion.func.hpp"

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

        // FUNCTION: STRONGHOLDCRUSADER 0x004BF760
        void NewInvasion::MenuItemActionHandler_NewInvasion_Buttons(int button, ...)
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
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    OpenSHC::Text::TAIT_UNKNOWN_15);
                return;
            case 37:
                // OK: take the year typed in, also for the message, count the units, close the dialog and keep the
                // events in date order.
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .header.year = atol(MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                    DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_UNKNOWN_11));
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .data.invasion.messageYear
                    = DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                          .header.year;
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .data.invasion.totalUnitCount = 0;
                // fixme: 25 is one past unitCountsPerUnitType (24), so the sum also adds invasionPoint
                for (int i = 0; i < 25; ++i) {
                    DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.invasion.totalUnitCount
                        += DAT_MapPropertiesState::instance
                               .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                               .data.invasion.unitCountsPerUnitType[i];
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::MapPropertiesState_Func::sortEventsByDate, DAT_MapPropertiesState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    OpenSHC::Text::TAIT_UNKNOWN_15);
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
            case 221:
                // "Crusader."
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .data.invasion.crusaderArabian = 0;
                return;
            case 222:
                // "Arabian."
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .data.invasion.crusaderArabian = 1;
                return;
            case 87:
                // "Other"
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .data.invasion.crusaderArabian = 4;
                return;
            }
        }

    }
}
}
