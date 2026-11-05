#include "../EditScenario.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004B8B10
        void EditScenario::MenuItemActionHandler_EditScenario_EventAndInvasionList(int row, ...)
        {
            if (DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_NONE) {
                return;
            }
            int const eventID = DAT_MapPropertiesState::instance.eventListScrollOffset + row;
            if (eventID >= DAT_MapPropertiesState::instance.eventsCount) {
                return;
            }
            DAT_MapPropertiesState::instance.eventListSelection = row;
            DAT_MapPropertiesState::instance.currentEventID = eventID;
            DAT_MapPropertiesState::instance.editedEventType
                = DAT_MapPropertiesState::instance.scenarioEvents[eventID].header.tl_type;
            // text slot 11 is the year box: it gets the event's year
            MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(11);
            char yearText[12];
            // the game reads the year through currentEventID, not eventID
            // "%d"
            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(yearText, s__d_005aa7f0,
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .header.year);
            MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
                yearText);
            switch (DAT_MapPropertiesState::instance.editedEventType) {
            case 1:
                // an invasion
                // the year box
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    11);
                DAT_MapPropertiesState::instance.field_0x1356c = 0;
                DAT_MapPropertiesState::instance.offset = 0;
                DAT_MapPropertiesState::instance.indexStored = 0;
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NEW_INVASION, FALSE);
                break;
            case 3:
                // an event
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NEW_EVENT, FALSE);
                break;
            }
        }

    }
}
}
