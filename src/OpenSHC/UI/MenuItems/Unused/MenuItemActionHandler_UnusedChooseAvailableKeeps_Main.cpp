#include "../Unused.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::UI::Enums::MenuViewType;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00430050
        void Unused::MenuItemActionHandler_UnusedChooseAvailableKeeps_Main(int param_1, ...)
        {
            uint* puVar1;
            if ((DAT_MenuTextInputState::instance.currentModalDialog == OpenSHC::UI::Enums::MMT_NO_MENU)
                && (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE)) {
                switch (param_1) {
                case 7:
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_NEW_MAP_MAPSIZE, 0);
                    return;
                case 0xb:
                    if (DAT_GameCore::instance.mapU2MiddleBytes[4] + DAT_GameCore::instance.mapU2MiddleBytes[3]
                            + DAT_GameCore::instance.mapU2MiddleBytes[2] + DAT_GameCore::instance.mapU2MiddleBytes[1]
                            + DAT_GameCore::instance.mapU2MiddleBytes[0]
                        != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_MAP_EDITOR_PROPERTIES, 0);
                        DAT_GameCore::instance.field115_0x1d98 = 1;
                    }
                    break;
                case -5:
                case -4:
                case -3:
                case -2:
                case -1:
                    puVar1 = (uint*)((int)DAT_GameCore::ptr + param_1 * -4 + 0x1534);
                    *puVar1 = *puVar1 ^ 1;
                }
            }
        }

    }
}
}
