#include "../EditScenario.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using UI::Enums::MenuModalType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004B8B10
        void EditScenario::MenuItemActionHandler_EditScenario_EventAndInvasionList(int param_1, ...)
        {
            MenuModalType menuModalID;
            char local_10[12];
            uint local_4 = MSVC_SecurityCookie::instance ^ (uint)local_10;
            if (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_NONE) {
                int iVar1 = DAT_MapPropertiesState::instance.eventListScrollOffset + param_1;
                if (iVar1 < DAT_MapPropertiesState::instance.eventsCount) {
                    DAT_MapPropertiesState::instance.eventListSelection = param_1;
                    DAT_MapPropertiesState::instance.editedEventType
                        = DAT_MapPropertiesState::instance.scenarioEvents[iVar1].header.tl_type;
                    DAT_MapPropertiesState::instance.currentEventID = iVar1;
                    MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(0xb);
                    MACRO_CALL(OS_Func::_sprintf)(local_10, "%d",
                        DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .header.year);
                    MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
                        local_10);
                    if (DAT_MapPropertiesState::instance.editedEventType == 1) {
                        MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                            0xb);
                        DAT_MapPropertiesState::instance.field_0x1356c = 0;
                        DAT_MapPropertiesState::instance.offset = 0;
                        DAT_MapPropertiesState::instance.indexStored = 0;
                        menuModalID = UI::Enums::MMT_NEW_INVASION;
                    } else {
                        if (DAT_MapPropertiesState::instance.editedEventType != 3)
                            goto LAB_004b8bdc;
                        menuModalID = UI::Enums::MMT_NEW_EVENT;
                    }
                    MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(menuModalID, FALSE);
                }
            }
        LAB_004b8bdc:;
        }

    }
}
}
