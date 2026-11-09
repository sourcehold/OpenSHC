#include "../LobbyMenu.func.hpp"

#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_00b960dc.hpp"
#include "OpenSHC/Globals/DAT_00b960f4.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/INT_00b95b74.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00428980
        void LobbyMenu::MenuItemActionHandler_LobbyMenu_MapDescScrollbar(
            int descBoxIndexUnk, int scrollbarEvent, int* minValue, int* maxValue, int* currentValue)
        {
            if (DAT_00b960dc::instance
                || DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_ROUNDTABLE
                || DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_BASIC_AI_LORD_SELECT
                || DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_EXTENDED_AI_LORD_SELECT) {
                return;
            }
            int visibleHeight = 0;
            if (descBoxIndexUnk == 0) {
                visibleHeight = 204;
            } else if (descBoxIndexUnk == 1) {
                visibleHeight = 110;
            }
            switch (scrollbarEvent) {
            case 1:
                *minValue = -19;
                *maxValue = INT_00b95b74::instance - visibleHeight;
                *currentValue = 0;
                return;
            case 2:
            case 3:
                DAT_00b960f4::instance = *currentValue;
                return;
            case 4:
                *minValue = -19;
                *maxValue = INT_00b95b74::instance - visibleHeight;
                *currentValue = DAT_00b960f4::instance;
                return;
            case 7:
                *currentValue = visibleHeight - 14;
            }
        }

    }
}
}
