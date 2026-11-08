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

        // FUNCTION: STRONGHOLDCRUSADER 0x00430050
        void Unused::MenuItemActionHandler_UnusedChooseAvailableKeeps_Main(int button, ...)
        {
            if (DAT_MenuTextInputState::instance.currentModalDialog != OpenSHC::UI::Enums::MMT_NO_MENU
                || DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_NONE) {
                return;
            }
            switch (button) {
            case -5:
            case -4:
            case -3:
            case -2:
            case -1:
                // buttons -1 to -5 toggle the five keep flags
                DAT_GameCore::instance.mapU2MiddleBytes[-button - 1] ^= 1;
                return;
            case 7:
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_NEW_MAP_MAPSIZE, 0);
                return;
            case 11:
                // on to the map properties once at least one keep is available; a loop loses the match
                if (DAT_GameCore::instance.mapU2MiddleBytes[0] + DAT_GameCore::instance.mapU2MiddleBytes[1]
                        + DAT_GameCore::instance.mapU2MiddleBytes[2] + DAT_GameCore::instance.mapU2MiddleBytes[3]
                        + DAT_GameCore::instance.mapU2MiddleBytes[4]
                    == 0) {
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_MAP_EDITOR_PROPERTIES, 0);
                DAT_GameCore::instance.mapLoadedForEditor = 1;
                return;
            }
        }

    }
}
}
