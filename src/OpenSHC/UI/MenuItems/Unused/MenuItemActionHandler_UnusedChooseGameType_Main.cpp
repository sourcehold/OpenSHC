#include "../Unused.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Map::MapType2;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::UI::Enums::MenuViewType;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004305D0
        void Unused::MenuItemActionHandler_UnusedChooseGameType_Main(int param_1, ...)
        {
            if (DAT_MenuTextInputState::instance.currentModalDialog != OpenSHC::UI::Enums::MMT_NO_MENU) {}
            if (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE) {
                switch (param_1) {
                case 7:
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_NEW_MAP_MAPSIZE, 0);
                default:
                    return;
                case 0x1c:
                    DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 = OpenSHC::Map::MT_SIEGE;
                    break;
                case 0x1d:
                    DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 = OpenSHC::Map::MT_INVASION;
                    break;
                case 0x1e:
                    DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 = OpenSHC::Map::MT_ECONOMIC;
                    break;
                case 0x21:
                    DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 = OpenSHC::Map::MT_JUST_BUILD;
                }
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_MAP_EDITOR_PROPERTIES, 0);
                DAT_GameCore::instance.field115_0x1d98 = 1;
            }
        }

    }
}
}
