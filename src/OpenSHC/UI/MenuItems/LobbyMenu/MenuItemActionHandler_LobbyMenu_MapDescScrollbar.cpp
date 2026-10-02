#include "../LobbyMenu.func.hpp"

#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_00b95b74.hpp"
#include "OpenSHC/Globals/DAT_00b960dc.hpp"
#include "OpenSHC/Globals/DAT_00b960f4.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::UI::Enums::MenuModalType;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00428980
        void LobbyMenu::MenuItemActionHandler_LobbyMenu_MapDescScrollbar(
            int param_1, int param_2, int* minValue, int* maxValue, int* currentValue)
        {
            int iVar1;
            if ((((DAT_00b960dc::instance == 0)
                     && (DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_ROUNDTABLE))
                    && (DAT_MenuModalComposition1::instance.activeModalDialogID
                        != OpenSHC::UI::Enums::MMT_BASIC_AI_LORD_SELECT))
                && (DAT_MenuModalComposition1::instance.activeModalDialogID
                    != OpenSHC::UI::Enums::MMT_EXTENDED_AI_LORD_SELECT)) {
                iVar1 = 0;
                if (param_1 == 0) {
                    iVar1 = 0xcc;
                } else if (param_1 == 1) {
                    iVar1 = 0x6e;
                }
                switch (param_2) {
                case 1:
                    *minValue = -0x13;
                    *maxValue = DAT_00b95b74::instance - iVar1;
                    *currentValue = 0;
                    return;
                case 2:
                case 3:
                    DAT_00b960f4::instance = *currentValue;
                    return;
                case 4:
                    *minValue = -0x13;
                    *maxValue = DAT_00b95b74::instance - iVar1;
                    *currentValue = DAT_00b960f4::instance;
                    return;
                case 7:
                    *currentValue = iVar1 + -0xe;
                }
            }
        }

    }
}
}
