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

        // FUNCTION: STRONGHOLDCRUSADER 0x004305D0
        void Unused::MenuItemActionHandler_UnusedChooseGameType_Main(int button, ...)
        {
            // nothing while a dialog is open
            if (DAT_MenuTextInputState::instance.currentModalDialog != OpenSHC::UI::Enums::MMT_NO_MENU
                || DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_NONE) {
                return;
            }
            // "Siege", "Invasion", "Economic" and "Landscape" set the map type and go on to the map properties.
            // each with its own tail, which MSVC merges into case 28's (one tail after the switch: 100.0% -> 85.9%)
            switch (button) {
            case 28:
                DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 = OpenSHC::Map::MT_SIEGE;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_MAP_EDITOR_PROPERTIES, 0);
                DAT_GameCore::instance.mapLoadedForEditor = 1;
                return;
            case 29:
                DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 = OpenSHC::Map::MT_INVASION;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_MAP_EDITOR_PROPERTIES, 0);
                DAT_GameCore::instance.mapLoadedForEditor = 1;
                return;
            case 30:
                DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 = OpenSHC::Map::MT_ECONOMIC;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_MAP_EDITOR_PROPERTIES, 0);
                DAT_GameCore::instance.mapLoadedForEditor = 1;
                return;
            case 33:
                DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 = OpenSHC::Map::MT_JUST_BUILD;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_MAP_EDITOR_PROPERTIES, 0);
                DAT_GameCore::instance.mapLoadedForEditor = 1;
                return;
            case 7:
                // "Back"
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_NEW_MAP_MAPSIZE, 0);
                return;
            }
        }

    }
}
}
