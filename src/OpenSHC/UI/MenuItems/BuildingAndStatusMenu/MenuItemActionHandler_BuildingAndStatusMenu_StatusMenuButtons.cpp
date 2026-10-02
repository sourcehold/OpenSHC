#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/INT_00b96120.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Game::GameMode2;
        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::UI::Enums::MenuViewType;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0043E490
        void BuildingAndStatusMenu::MenuItemActionHandler_BuildingAndStatusMenu_StatusMenuButtons(int param_1, ...)
        {
            if (((param_1 == 0x47) && (DAT_GameCore::instance.buildingandstatusmenuMenuTabToSwitchTo == 0x4b))
                && (INT_00b96120::instance == 4)) {
                param_1 = OpenSHC::Map::Buildings::BT_OXTETHER;
            }
            DAT_GameCore::instance.buildingandstatusmenuMenuTabToSwitchTo = param_1;
            MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU, 0);
            if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL)
                && (param_1 != OpenSHC::Map::Buildings::BT_KEEPDOOR_LEFT)) {
                MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTutorialBuildingActionState)(
                    0xf, (BuildingType)((int)(param_1)));
            }
        }

    }
}
}
